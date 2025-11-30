#include "cooperativas.hpp"
#include "material.hpp"
#include "Catador.hpp"
#include "colaborador.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>  // ADICIONADO para std::setprecision

Cooperativas::Cooperativas() {
    preco = 0;
    cnpj = "";
    endereco = "";
    material = nullptr;
}

Cooperativas::Cooperativas(float preco, std::string cnpj, std::string endereco, Material* material) {
    this->preco = preco;
    this->cnpj = cnpj;
    this->endereco = endereco;
    this->material = material;
}

float Cooperativas::getPreco() { return this->preco; }
std::string Cooperativas::getCnpj() { return this->cnpj; }
std::string Cooperativas::getEndereco() { return this->endereco; }
Material* Cooperativas::getMaterial() { return this->material; }

void Cooperativas::setPreco(float preco) { this->preco = preco; }
void Cooperativas::setCnpj(std::string cnpj) { this->cnpj = cnpj; }
void Cooperativas::setEndereco(std::string endereco) { this->endereco = endereco; }
void Cooperativas::setMaterial(Material* material) { this->material = material; }

Cooperativas::~Cooperativas() {}

void Cooperativas::calcularPreco(float peso, float precoPorKg) {
    float total = peso * precoPorKg;
    std::cout << "Total a pagar: R$ " << total << std::endl;
}

void Cooperativas::comprarMaterial(Catador& catador, float peso, float precoPorKg) {
    if (catador.getEndereco() == this->endereco) {
        float valor = peso * precoPorKg;
        catador.setSaldo(catador.getSaldo() + valor);
        std::cout << "Compra realizada! Catador " << catador.getNome() 
                  << " recebeu R$ " << valor << std::endl;
    } else {
        std::cout << "Endereço do catador diferente da cooperativa. Compra não realizada." << std::endl;
    }
}

void Cooperativas::consultarPrecoCooperativa() {
    std::cout << "Preço base da cooperativa: R$ " << preco << " por kg" << std::endl;
}

void Cooperativas::relatorio() {
    std::cout << "=== RELATÓRIO COOPERATIVA ===" << std::endl;
    std::cout << "CNPJ: " << cnpj << std::endl;
    std::cout << "Endereço: " << endereco << std::endl;
    std::cout << "Preço base: R$ " << preco << std::endl;
    if (material) {
        std::cout << "Material em estoque: " << material->getPeso() 
                  << "kg, tipo " << material->getTipo() << std::endl;
    } else {
        std::cout << "Nenhum material em estoque." << std::endl;
    }
}

void Cooperativas::cadastro(float preco, std::string endereco, std::string cnpj, Material* material) {
    this->preco = preco;
    this->endereco = endereco;
    this->cnpj = cnpj;
    this->material = material;
    
    std::ofstream arquivo("cadastro_cooperativa.txt", std::ios::app);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de cadastro." << std::endl;
        return;
    }

    arquivo << "CNPJ: " << cnpj << ", Endereço: " << endereco << ", Preço: R$ " << preco;
    if (material) {
        arquivo << ", Material: " << material->getPeso() << "kg tipo " << material->getTipo();
    }
    arquivo << std::endl;
    arquivo.close();
    
    std::cout << "Cooperativa cadastrada com sucesso!" << std::endl;
}

void Cooperativas::relatorioMaterialComprado() {
    std::cout << "\n=== RELATÓRIO DE MATERIAL COMPRADO ===\n";
    std::ifstream arquivo("historico_compras.txt");
    std::string linha;
    
    if (!arquivo.is_open()) {
        std::cout << "Nenhuma compra registrada.\n";
        return;
    }
    
    float totalComprado = 0;
    while (std::getline(arquivo, linha)) {
        std::cout << linha << std::endl;
        
        // Extrair peso da linha
        size_t posKg = linha.find("kg");
        if (posKg != std::string::npos) {
            // Encontrar início do número
            size_t start = linha.find("comprou ") + 8;
            if (start != std::string::npos) {
                std::string pesoStr = linha.substr(start, posKg - start);
                try {
                    float peso = std::stof(pesoStr);
                    totalComprado += peso;
                } catch (...) {
                    // Ignora erro de conversão
                }
            }
        }
    }
    arquivo.close();
    
    std::cout << "\nTotal comprado: " << totalComprado << " kg\n";
}

void Cooperativas::registrarCompra(const std::string& nomeCatador, float peso, float precoKg) {
    std::ofstream arquivo("historico_compras.txt", std::ios::app);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao registrar compra.\n";
        return;
    }
    
    float valorTotal = peso * precoKg;
    arquivo << "Cooperativa " << this->cnpj << " comprou " << peso << "kg de " << nomeCatador 
            << " por R$ " << std::fixed << std::setprecision(2) << valorTotal << std::endl;
    arquivo.close();
    
    std::cout << "Compra registrada no histórico!\n";
}

void Cooperativas::visualizarCooperativas() {
    std::cout << "\n=== COOPERATIVAS DISPONÍVEIS ===\n";
    std::ifstream arquivo("cadastro_cooperativa.txt");
    std::string linha;
    
    if (!arquivo.is_open()) {
        std::cout << "Nenhuma cooperativa cadastrada.\n";
        return;
    }
    
    while (std::getline(arquivo, linha)) {
        std::cout << linha << std::endl;
    }
    arquivo.close();
}