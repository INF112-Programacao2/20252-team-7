#include "colaborador.hpp"
#include <iostream>
#include <fstream>

Colaborador::Colaborador(const Pessoa& pessoa) 
    : Pessoa(pessoa), 
      pontos(0) { }

int Colaborador::getPontos() const {
    return this->pontos;
}

void Colaborador::setPontos(int pontos) {
    this->pontos = pontos;
}

Colaborador::~Colaborador() { }

void Colaborador::cadastro(std::string nome, std::string endereco, std::string cpf, Material* material) {
    // CORRIGIDO: usar método base com ponteiro
    Pessoa::cadastro(nome, endereco, cpf, material);
    
    std::ofstream arquivo("cadastro_colaborador.txt", std::ios::app);
    
    try {
        if (!arquivo.is_open()) {
            throw std::ios_base::failure("Erro ao abrir o arquivo de cadastro.");
        }
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << e.what() << std::endl;
        return;
    }
    
    arquivo << "Nome: " << nome << std::endl;
    arquivo << "Endereço: " << endereco << std::endl;
    arquivo << "CPF: " << cpf << std::endl;
    if (material) {
        arquivo << "Material - Peso: " << material->getPeso() << ", Tipo: " << material->getTipo() << std::endl;
    } else {
        arquivo << "Material: Nulo" << std::endl;
    }
    arquivo << "Pontos: " << pontos << std::endl;
    arquivo << "------------------------" << std::endl;

    arquivo.close();
    
    std::cout << "Colaborador cadastrado com sucesso!" << std::endl;
}

void Colaborador::receberPontos(int pontosRecebidos) {
    Material* material = this->getMaterial();

    if (material->getPeso() < 0) {
        std::cout << "Peso do material inválido para receber pontos." << std::endl;
        return;
    }
    switch (material->getTipo()) {
        case 1: // Tipo 1
            pontosRecebidos *= 2;
            break;
        case 2: // Tipo 2
            pontosRecebidos *= 3;
            break;
        case 3: // Tipo 3
            pontosRecebidos *= 5;
            break;
        default:
            std::cout << "Tipo de material desconhecido. Nenhum ponto recebido." << std::endl;
            pontosRecebidos = 0;
            break;
    }
    this->pontos += pontosRecebidos/(material->getPeso()/10);
}