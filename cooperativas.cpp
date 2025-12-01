#include "cooperativas.hpp"
#include "material.hpp"
#include "Catador.hpp"
#include <iostream>
#include <fstream>
#include <iomanip> // [Stream] Necessário para formatar saída (setprecision)

// ==================================================================================
// CONSTRUTOR PADRÃO
// ==================================================================================
Cooperativas::Cooperativas() 
    : precoPlastico(0), precoPapel(0), precoMetal(0), cnpj(""), endereco(""), material(nullptr) {}

// ==================================================================================
// CONSTRUTOR PARAMETRIZADO
// ==================================================================================
Cooperativas::Cooperativas(float pPlastico, float pPapel, float pMetal, std::string c, std::string e, Material* m) 
    : precoPlastico(pPlastico), precoPapel(pPapel), precoMetal(pMetal), cnpj(c), endereco(e), material(m) {}

// ==================================================================================
// DESTRUTOR (Gerenciamento de Memória)
// ==================================================================================
Cooperativas::~Cooperativas() {
    if (material != nullptr) {
        delete material; // Libera a memória RAM
        material = nullptr; // Zera o ponteiro por segurança
    }
}

// ==================================================================================
// GETTERS E SETTERS
// ==================================================================================
float Cooperativas::getPrecoPlastico() { return precoPlastico; }
float Cooperativas::getPrecoPapel() { return precoPapel; }
float Cooperativas::getPrecoMetal() { return precoMetal; }

void Cooperativas::setPrecos(float plastico, float papel, float metal) {
    this->precoPlastico = plastico;
    this->precoPapel = papel;
    this->precoMetal = metal;
}

std::string Cooperativas::getCnpj() { return cnpj; }
std::string Cooperativas::getEndereco() { return endereco; }
Material* Cooperativas::getMaterial() { return material; }

void Cooperativas::setCnpj(std::string c) { cnpj = c; }
void Cooperativas::setEndereco(std::string e) { endereco = e; }

// [Memória] Setter seguro: Deleta o material antigo antes de apontar para o novo.
void Cooperativas::setMaterial(Material* m) { 
    if (material) delete material;
    material = m; 
}

// ==================================================================================
// MÉTODO DE NEGÓCIO: COMPRAR MATERIAL
// ----------------------------------------------------------------------------------
// Este método recebe um objeto 'Catador' por referência (&).
// Isso permite que a Cooperativa altere diretamente o objeto catador original
// (especificamente, aumentando o saldo dele).
//
// Lógica:
// 1. Verifica compatibilidade de endereço (Regra de Negócio).
// 2. Identifica o tipo de material e seleciona o preço correto.
// 3. Calcula o total e deposita no saldo do Catador (em memória RAM).
//    Nota: A persistência no arquivo é feita separadamente pelo Controller.
// ==================================================================================
void Cooperativas::comprarMaterial(Catador& catador, float peso) {
    // Validação de Regra de Negócio
    if (catador.getEndereco() != this->endereco) {
        std::cout << "Erro: O catador nao esta no mesmo endereco da cooperativa.\n";
        return;
    }
    if (!catador.getMaterial()) {
        std::cout << "Erro: Catador nao tem material.\n";
        return;
    }

    // Seleção de Preço 
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
    
    // Modificação do estado do objeto colaborador
    catador.setSaldo(catador.getSaldo() + valorTotal);
    
    std::cout << "=== COMPRA REALIZADA ===\n";
    std::cout << "Material: " << catador.getMaterial()->getNomeTipo() << "\n";
    std::cout << "Peso: " << peso << "kg\n";
    std::cout << "Valor total pago: R$ " << valorTotal << "\n";
}

// ==================================================================================
// CADASTRO
// ----------------------------------------------------------------------------------
// Salva os dados da cooperativa no arquivo de texto.
// ==================================================================================
void Cooperativas::cadastro(float pPlastico, float pPapel, float pMetal, std::string endereco, std::string cnpj, Material* material) {
    this->precoPlastico = pPlastico;
    this->precoPapel = pPapel;
    this->precoMetal = pMetal;
    this->endereco = endereco;
    this->cnpj = cnpj;
    this->setMaterial(material);
    
    // [File I/O] std::ios::app garante que adicionamos ao final do arquivo sem apagar o que já existe
    std::ofstream arquivo("cadastro_cooperativa.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "CNPJ: " << cnpj << "\n";
        arquivo << "Endereco: " << endereco << "\n";
        arquivo << "Precos - Plastico: R$" << pPlastico 
                << " | Papel: R$" << pPapel 
                << " | Metal: R$" << pMetal << "\n";
        arquivo << "------------------------\n";
        arquivo.close();
        std::cout << "Cooperativa cadastrada com sucesso!\n";
    }
}

// ==================================================================================
// PERSISTÊNCIA: RELATÓRIO COM FILTRO
// ----------------------------------------------------------------------------------
// [Lógica de Filtro]
// Lê o arquivo 'historico_compras.txt' linha por linha, mas imprime na tela apenas
// as linhas que contêm o CNPJ desta cooperativa específica.
// Isso garante a privacidade dos dados entre diferentes empresas.
// ==================================================================================
void Cooperativas::relatorioMaterialComprado() {
    std::cout << "\n=== HISTORICO DE COMPRAS (CNPJ: " << this->cnpj << ") ===\n";
    std::ifstream arquivo("historico_compras.txt");
    std::string linha;
    bool encontrouAlguma = false;

    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
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

// ==================================================================================
// PERSISTÊNCIA: REGISTRAR TRANSAÇÃO
// ----------------------------------------------------------------------------------
// Adiciona uma nova linha ao log de transações.
// ==================================================================================
void Cooperativas::registrarCompra(const std::string& cpfCatador, float peso, float valorTotal, std::string nomeMaterial) {
    std::ofstream arquivo("historico_compras.txt", std::ios::app);
    if (arquivo.is_open()) {
        // Formato padronizado: "Coop [CNPJ] pagou R$ [$$] por [peso]kg de [tipo] ao CPF [cpf]"
        arquivo << "Coop " << this->cnpj << " pagou R$ " << std::fixed << std::setprecision(2) 
                << valorTotal << " por " << peso << "kg de " << nomeMaterial 
                << " ao CPF " << cpfCatador << "\n";
        arquivo.close();
    }
}

// ==================================================================================
// RELATÓRIO ESTATÍSTICO (Parser e Agregação)
// ----------------------------------------------------------------------------------
// [Lógica Avançada]
// 1. Lê o arquivo de histórico.
// 2. Filtra pelo CNPJ.
// 3. Faz a extração dos números de peso de dentro do texto.
// 4. Soma os totais por categoria.
// 5. Gera um novo arquivo .txt exclusivo com o resumo.
// ==================================================================================
void Cooperativas::gerarRelatorioEstatistico() {
    std::ifstream arquivo("historico_compras.txt");
    if (!arquivo.is_open()) {
        std::cout << "Nenhum historico encontrado para gerar relatorio.\n";
        return;
    }

    std::string linha;
    float totalPlastico = 0;
    float totalPapel = 0;
    float totalMetal = 0;
    
    std::cout << "\n>> Calculando estatisticas para CNPJ " << this->cnpj << "...\n";

    while (std::getline(arquivo, linha)) {
        // Filtro de Segurança
        if (linha.find("Coop " + this->cnpj) != std::string::npos) {
            
            float pesoLinha = 0;
            
            // [Tratamento de Exceção] Tenta converter string para float
            try {
                // Procura os marcadores de texto " por " e "kg de " para isolar o número
                size_t posPor = linha.find(" por ");
                size_t posKg = linha.find("kg de ");
                
                if (posPor != std::string::npos && posKg != std::string::npos) {
                    size_t inicioNumero = posPor + 5; // Pula " por "
                    // substr(posicao_inicial, tamanho)
                    std::string pesoStr = linha.substr(inicioNumero, posKg - inicioNumero);
                    pesoLinha = std::stof(pesoStr);
                }
            } catch (...) {
                continue; // Se falhar na conversão, ignora esta linha e segue
            }

            // Agregação de Dados
            if (linha.find("Plastico") != std::string::npos) totalPlastico += pesoLinha;
            else if (linha.find("Papel") != std::string::npos) totalPapel += pesoLinha;
            else if (linha.find("Metal") != std::string::npos) totalMetal += pesoLinha;
        }
    }
    arquivo.close();

    // Geração de Arquivo de Saída
    std::string nomeArquivoSaida = "estatisticas_" + this->cnpj + ".txt";
    std::ofstream saida(nomeArquivoSaida);

    if (saida.is_open()) {
        saida << "=== RELATORIO ESTATISTICO DE COMPRAS ===\n";
        saida << "CNPJ: " << this->cnpj << "\n";
        saida << "--------------------------------------\n";
        saida << "MATERIAL    | QUANTIDADE TOTAL (KG)\n";
        saida << "--------------------------------------\n";
        saida << "Plastico    | " << std::fixed << std::setprecision(2) << totalPlastico << " kg\n";
        saida << "Papel       | " << std::fixed << std::setprecision(2) << totalPapel << " kg\n";
        saida << "Metal       | " << std::fixed << std::setprecision(2) << totalMetal << " kg\n";
        saida << "--------------------------------------\n";
        saida << "TOTAL GERAL | " << (totalPlastico + totalPapel + totalMetal) << " kg\n";
        saida.close();
        
        std::cout << "\n[SUCESSO] Relatorio gerado em '" << nomeArquivoSaida << "'\n";
    } else {
        std::cout << "Erro ao criar arquivo de relatorio.\n";
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