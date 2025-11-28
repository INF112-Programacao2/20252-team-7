#include "Catador.hpp"
#include <iostream>
#include <fstream>
#include "material.hpp"

// Construtor
Catador::Catador(const Pessoa& pessoa) 
    : Pessoa(pessoa), 
      _saldo(0.0f) {}

// Destrutor
Catador::~Catador() { }

// Getter
float Catador::getSaldo() const {
    return _saldo;
}

// Setter
void Catador::setSaldo(float valor) {
    _saldo = valor;
}

// Outras funções - CORRIGIDAS para usar ponteiros
void Catador::recolherMaterial(Material* material) {
    if (material && this->getMaterial()) {
        float pesoAtual = this->getMaterial()->getPeso();
        float novoPeso = pesoAtual + material->getPeso();
        this->getMaterial()->setPeso(novoPeso);
        std::cout << "Material recolhido! Novo peso: " << novoPeso << "kg" << std::endl;
    }
}

void Catador::cadastro(std::string nome, std::string endereco, std::string cpf, Material* material) {
    // CORRIGIDO: usar método base com ponteiro
    Pessoa::cadastro(nome, endereco, cpf, material);
    
    std::ofstream arquivo("cadastro_catador.txt", std::ios::app);
    
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
    arquivo << "Saldo: " << _saldo << std::endl;
    arquivo << "------------------------" << std::endl;

    arquivo.close();
    
    std::cout << "Catador cadastrado com sucesso!" << std::endl;
}
