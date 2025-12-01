#include "Catador.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Construtor de Cópia
Catador::Catador(const Pessoa& pessoa) : Pessoa(pessoa), _saldo(0.0f) {}

// Construtor Padrão
Catador::Catador(std::string nome, std::string endereco, std::string cpf, Material* material)
    : Pessoa(nome, endereco, cpf, material), _saldo(0.0f) {}

Catador::~Catador() {}

float Catador::getSaldo() const { return _saldo; }
void Catador::setSaldo(float valor) { _saldo = valor; }

void Catador::recolherMaterial(Material* material) {
    if (material && this->getMaterial()) {
        float novoPeso = this->getMaterial()->getPeso() + material->getPeso();
        this->getMaterial()->setPeso(novoPeso);
        std::cout << "Material recolhido! Novo peso: " << novoPeso << "kg\n";
    }
}

// === CADASTRO ATUALIZADO (Sem exigir material inicial) ===
void Catador::cadastro(std::string nome, std::string endereco, std::string cpf, Material* material) {
    std::ofstream arquivo("cadastro_catador.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "Nome: " << nome << "\nEndereço: " << endereco << "\nCPF: " << cpf << "\n";
        
        if (material) {
            arquivo << "Material: " << material->getPeso() << "kg de " << material->getNomeTipo() << "\n";
        } else {
            arquivo << "Material: Nenhum (Cadastro Inicial)\n";
        }
        
        arquivo << "Saldo: R$ " << _saldo << "\n------------------------\n";
        arquivo.close();
        std::cout << "Catador cadastrado com sucesso!\n";
    }
}

void Catador::visualizarCooperativas() {
    std::cout << "\n=== COOPERATIVAS DISPONIVEIS ===\n";
    std::ifstream arquivo("cadastro_cooperativa.txt");
    std::string linha;
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) std::cout << linha << "\n";
        arquivo.close();
    }
}

// === LÓGICA DE SALDO PERSISTENTE (Edita o arquivo TXT) ===
void Catador::adicionarSaldoAoArquivo(float valorAdicionado) {
    std::ifstream leitura("cadastro_catador.txt");
    std::vector<std::string> linhas;
    std::string linha;
    
    std::string cpfAlvo = "CPF: " + this->getCpf();
    bool encontrouUsuario = false;
    bool saldoAtualizado = false;

    if (!leitura.is_open()) {
        std::cout << "Erro: Base de dados de catadores nao encontrada.\n";
        return;
    }

    // 1. Lê todo o arquivo para a memória
    while (std::getline(leitura, linha)) {
        // Verifica se achou o usuário pelo CPF
        if (linha.find(cpfAlvo) != std::string::npos) {
            encontrouUsuario = true;
        }

        // Se estamos no bloco do usuário certo e achamos a linha de Saldo
        if (encontrouUsuario && linha.find("Saldo: R$ ") != std::string::npos && !saldoAtualizado) {
            try {
                // Pega o valor antigo e soma
                float saldoAntigo = std::stof(linha.substr(10));
                float novoSaldo = saldoAntigo + valorAdicionado;
                
                // Cria a nova linha
                std::string novaLinha = "Saldo: R$ " + std::to_string(novoSaldo);
                linhas.push_back(novaLinha);
                
                // Atualiza o objeto na memória
                this->_saldo = novoSaldo;
                saldoAtualizado = true; // Impede que altere saldos de outros usuários
            } catch (...) {
                linhas.push_back(linha); // Se der erro, mantém original
            }
        } 
        else if (linha.find("------------------------") != std::string::npos) {
            // Fim do bloco deste usuário
            if (encontrouUsuario) {
                encontrouUsuario = false;
                saldoAtualizado = false;
            }
            linhas.push_back(linha);
        }
        else {
            linhas.push_back(linha); // Copia as outras linhas
        }
    }
    leitura.close();

    // 2. Reescreve o arquivo com o saldo atualizado
    std::ofstream escrita("cadastro_catador.txt");
    for (const auto& l : linhas) {
        escrita << l << "\n";
    }
    escrita.close();
}