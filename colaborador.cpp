#include "colaborador.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

Colaborador::Colaborador(const Pessoa& pessoa) : Pessoa(pessoa), pontos(0) {}
Colaborador::Colaborador(std::string nome, std::string endereco, std::string cpf, Material* material)
    : Pessoa(nome, endereco, cpf, material), pontos(0) {}

Colaborador::~Colaborador() {}

int Colaborador::getPontos() const { return pontos; }
void Colaborador::setPontos(int p) { pontos = p; }

void Colaborador::cadastro(std::string nome, std::string endereco, std::string cpf, Material* material) {
    std::ofstream arq("cadastro_colaborador.txt", std::ios::app);
    if (arq.is_open()) {
        arq << "Nome: " << nome << "\nEndereço: " << endereco << "\nCPF: " << cpf << "\n";
        if (material) arq << "Material: " << material->getPeso() << "kg de " << material->getNomeTipo() << "\n";
        arq << "Pontos: 0\n------------------------\n";
        arq.close();
        std::cout << "Colaborador cadastrado!\n";
    }
}

// Doação de Material (Usa multiplicador)
void Colaborador::realizarDoacao(Material* m) {
    if (!m || m->getPeso() <= 0) return;

    int multiplicador = 0;
    switch (m->getTipo()) {
        case 1: multiplicador = 3; break; // Plastico
        case 2: multiplicador = 2; break; // Papel
        case 3: multiplicador = 4; break; // Metal
        default: multiplicador = 1; break;
    }

    int pontosGanhos = static_cast<int>(m->getPeso() * multiplicador);
    this->pontos += pontosGanhos;
    
    std::cout << "\n=== DOACAO REALIZADA ===\n";
    std::cout << "Material: " << m->getNomeTipo() << " (" << m->getPeso() << "kg)\n";
    std::cout << "Pontos ganhos: " << pontosGanhos << "\n";
    
    salvarPontosNoArquivo();
}

// [CORREÇÃO] Doação de Valor Fixo (Bônus)
void Colaborador::receberPontos(int valor) {
    this->pontos += valor;
    std::cout << ">> Bonus recebido: +" << valor << " pontos!\n";
    salvarPontosNoArquivo();
}

// === PERSISTÊNCIA ===
void Colaborador::carregarPontos() {
    std::ifstream arquivo("cadastro_colaborador.txt");
    std::string linha;
    std::string cpfAlvo = "CPF: " + this->getCpf();
    bool encontrouUsuario = false;

    if (!arquivo.is_open()) return;

    while (std::getline(arquivo, linha)) {
        if (linha.find(cpfAlvo) != std::string::npos) {
            encontrouUsuario = true;
        }
        if (encontrouUsuario && linha.find("Pontos: ") != std::string::npos) {
            try {
                this->pontos = std::stoi(linha.substr(8));
            } catch (...) {
                this->pontos = 0;
            }
            break;
        }
        if (encontrouUsuario && linha.find("------------------------") != std::string::npos) {
            break;
        }
    }
    arquivo.close();
}

void Colaborador::salvarPontosNoArquivo() {
    std::ifstream leitura("cadastro_colaborador.txt");
    std::vector<std::string> linhas;
    std::string linha;
    std::string cpfAlvo = "CPF: " + this->getCpf();
    bool usuarioAtual = false;
    bool atualizado = false;

    if (!leitura.is_open()) return;

    while (std::getline(leitura, linha)) {
        if (linha.find(cpfAlvo) != std::string::npos) {
            usuarioAtual = true;
        }
        
        if (usuarioAtual && linha.find("Pontos: ") != std::string::npos && !atualizado) {
            linhas.push_back("Pontos: " + std::to_string(this->pontos));
            atualizado = true;
        } 
        else if (linha.find("------------------------") != std::string::npos) {
            usuarioAtual = false;
            linhas.push_back(linha);
        } 
        else {
            linhas.push_back(linha);
        }
    }
    leitura.close();

    std::ofstream escrita("cadastro_colaborador.txt");
    for (const auto& l : linhas) {
        escrita << l << "\n";
    }
    escrita.close();
}

void Colaborador::visualizarCooperativas() {
    std::cout << "\n=== COOPERATIVAS ===\n";
    std::ifstream arquivo("cadastro_cooperativa.txt");
    std::string linha;
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) std::cout << linha << "\n";
        arquivo.close();
    }
}