#include "Catador.hpp"
#include <iostream>
#include <fstream>

// Construtor
Catador::Catador(Pessoa pessoa) : Pessoa(pessoa.getNome(), pessoa.getEndereco(), pessoa.getCpf(), pessoa.getMaterial()) {
    _saldo = 0.0f;
}

// Destrutor
Catador::~Catador() { }

// Getter
float Catador::getSaldo() {
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

void Catador::cadastro(std::string nome, std::string endereco, std::string cpf, Material* material, float saldo) {
    // CORRIGIDO: usar método base com ponteiro
    Pessoa::cadastro(nome, endereco, cpf, material);
    
    std::ofstream arquivo("cadastro_catador.txt", std::ios::app);
    
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de cadastro." << std::endl;
        return;
    }
    
    arquivo << "," << saldo << std::endl;
    arquivo.close();
    
    std::cout << "Catador cadastrado com sucesso!" << std::endl;
}
