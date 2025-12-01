#include "cooperativas.hpp"
#include "material.hpp"
#include "Catador.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

// Construtores
Cooperativas::Cooperativas() 
    : precoPlastico(0), precoPapel(0), precoMetal(0), cnpj(""), endereco(""), material(nullptr) {}

Cooperativas::Cooperativas(float pPlastico, float pPapel, float pMetal, std::string c, std::string e, Material* m) 
    : precoPlastico(pPlastico), precoPapel(pPapel), precoMetal(pMetal), cnpj(c), endereco(e), material(m) {}

Cooperativas::~Cooperativas() {
    if (material != nullptr) {
        delete material;
        material = nullptr;
    }
}

// Getters
float Cooperativas::getPrecoPlastico() { return precoPlastico; }
float Cooperativas::getPrecoPapel() { return precoPapel; }
float Cooperativas::getPrecoMetal() { return precoMetal; }
std::string Cooperativas::getCnpj() { return cnpj; }
std::string Cooperativas::getEndereco() { return endereco; }
Material* Cooperativas::getMaterial() { return material; }

// Setters
void Cooperativas::setPrecos(float plastico, float papel, float metal) {
    this->precoPlastico = plastico;
    this->precoPapel = papel;
    this->precoMetal = metal;
}
void Cooperativas::setCnpj(std::string c) { cnpj = c; }
void Cooperativas::setEndereco(std::string e) { endereco = e; }
void Cooperativas::setMaterial(Material* m) { 
    if (material) delete material;
    material = m; 
}

// Lógica de Compra
void Cooperativas::comprarMaterial(Catador& catador, float peso) {
    if (catador.getEndereco() != this->endereco) {
        std::cout << "Erro: O catador nao esta no mesmo endereco da cooperativa.\n";
        return;
    }
    if (!catador.getMaterial()) {
        std::cout << "Erro: Catador nao tem material.\n";
        return;
    }

    float precoAplicado = 0;
    int tipo = catador.getMaterial()->getTipo();
    
    if (tipo == 1) precoAplicado = this->precoPlastico;
    else if (tipo == 2) precoAplicado = this->precoPapel;
    else if (tipo == 3) precoAplicado = this->precoMetal;

    if (precoAplicado <= 0) {
        std::cout << "Erro: Preco nao definido para este tipo de material.\n";
        return;
    }

    float valorTotal = peso * precoAplicado;
    catador.setSaldo(catador.getSaldo() + valorTotal);
    
    std::cout << "=== COMPRA REALIZADA ===\n";
    std::cout << "Material: " << catador.getMaterial()->getNomeTipo() << "\n";
    std::cout << "Peso: " << peso << "kg\n";
    std::cout << "Valor total pago: R$ " << valorTotal << "\n";
}

// Cadastro
void Cooperativas::cadastro(float pPlastico, float pPapel, float pMetal, std::string endereco, std::string cnpj, Material* material) {
    this->precoPlastico = pPlastico;
    this->precoPapel = pPapel;
    this->precoMetal = pMetal;
    this->endereco = endereco;
    this->cnpj = cnpj;
    this->setMaterial(material);
    
    std::ofstream arquivo("cadastro_cooperativa.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "CNPJ: " << cnpj << "\n";
        arquivo << "Endereco: " << endereco << "\n";
        arquivo << "Precos - Plastico: R$" << pPlastico << " | Papel: R$" << pPapel << " | Metal: R$" << pMetal << "\n";
        arquivo << "------------------------\n";
        arquivo.close();
        std::cout << "Cooperativa cadastrada com sucesso!\n";
    }
}

// === [MODIFICADO] RELATÓRIO EXCLUSIVO (FILTRA POR CNPJ) ===
void Cooperativas::relatorioMaterialComprado() {
    std::cout << "\n=== HISTORICO DE COMPRAS (CNPJ: " << this->cnpj << ") ===\n";
    std::ifstream arquivo("historico_compras.txt");
    std::string linha;
    bool encontrouAlguma = false;

    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            // Só imprime se a linha contiver o CNPJ desta cooperativa
            if (linha.find("Coop " + this->cnpj) != std::string::npos) {
                std::cout << linha << "\n";
                encontrouAlguma = true;
            }
        }
        arquivo.close();
        
        if (!encontrouAlguma) {
            std::cout << "Nenhuma compra registrada para este CNPJ.\n";
        }
    } else {
        std::cout << "Arquivo de historico ainda nao existe.\n";
    }
}

// Registrar Compra
void Cooperativas::registrarCompra(const std::string& cpfCatador, float peso, float valorTotal, std::string nomeMaterial) {
    std::ofstream arquivo("historico_compras.txt", std::ios::app);
    if (arquivo.is_open()) {
        // Agora salva o CPF em vez do nome
        arquivo << "Coop " << this->cnpj << " pagou R$ " << std::fixed << std::setprecision(2) 
                << valorTotal << " por " << peso << "kg de " << nomeMaterial 
                << " ao CPF " << cpfCatador << "\n";
        arquivo.close();
    }
}

// Gerar Relatório Estatístico (Já estava filtrado, mantemos igual)
void Cooperativas::gerarRelatorioEstatistico() {
    std::ifstream arquivo("historico_compras.txt");
    if (!arquivo.is_open()) { std::cout << "Sem dados.\n"; return; }

    std::string linha;
    float tPlastico = 0, tPapel = 0, tMetal = 0;
    
    std::cout << "\n>> Calculando estatisticas para CNPJ " << this->cnpj << "...\n";

    while (std::getline(arquivo, linha)) {
        if (linha.find("Coop " + this->cnpj) != std::string::npos) {
            float pesoLinha = 0;
            try {
                size_t posPor = linha.find(" por ");
                size_t posKg = linha.find("kg de ");
                if (posPor != std::string::npos && posKg != std::string::npos) {
                    pesoLinha = std::stof(linha.substr(posPor + 5, posKg - (posPor + 5)));
                }
            } catch (...) { continue; }

            if (linha.find("Plastico") != std::string::npos) tPlastico += pesoLinha;
            else if (linha.find("Papel") != std::string::npos) tPapel += pesoLinha;
            else if (linha.find("Metal") != std::string::npos) tMetal += pesoLinha;
        }
    }
    arquivo.close();

    std::string nomeArq = "estatisticas_" + this->cnpj + ".txt";
    std::ofstream saida(nomeArq);
    if (saida.is_open()) {
        saida << "=== RELATORIO DE COMPRAS ===\nCNPJ: " << cnpj << "\n";
        saida << "Plastico: " << tPlastico << "kg\nPapel: " << tPapel << "kg\nMetal: " << tMetal << "kg\n";
        saida.close();
        std::cout << "Relatorio salvo em '" << nomeArq << "'.\n";
    }
}

void Cooperativas::visualizarCooperativas() {
    std::cout << "\n=== COOPERATIVAS DISPONIVEIS ===\n";
    std::ifstream arquivo("cadastro_cooperativa.txt");
    std::string linha;
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) std::cout << linha << "\n";
        arquivo.close();
    }
}