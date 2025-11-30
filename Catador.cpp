#include "Catador.hpp"
#include <iostream>
#include <fstream>
#include "material.hpp"

// === CONSTRUTOR POR CÓPIA (já existia) ===
Catador::Catador(const Pessoa& pessoa) 
    : Pessoa(pessoa), 
      _saldo(0.0f) {}

// === NOVO CONSTRUTOR COMPLETO (agora no lugar certo!) ===
Catador::Catador(std::string nome, std::string endereco, std::string cpf, Material* material)
    : Pessoa(nome, endereco, cpf, material), _saldo(0.0f) {}

// Destrutor
Catador::~Catador() { }

// Getter e Setter
float Catador::getSaldo() const {
    return _saldo;
}

void Catador::setSaldo(float valor) {
    _saldo = valor;
}

void Catador::recolherMaterial(Material* material) {
    if (material && this->getMaterial()) {
        float pesoAtual = this->getMaterial()->getPeso();
        float novoPeso = pesoAtual + material->getPeso();
        this->getMaterial()->setPeso(novoPeso);
        std::cout << "Material recolhido! Novo peso: " << novoPeso << "kg" << std::endl;
    } else {
        std::cout << "Erro ao recolher material." << std::endl;
    }
}

// === FUNÇÃO CADASTRO (agora limpa e correta) ===
void Catador::cadastro(std::string nome, std::string endereco, std::string cpf, Material* material) {
    Pessoa::setNome(nome);
    Pessoa::setEndereco(endereco);
    Pessoa::setCpf(cpf);
    Pessoa::setMaterial(material);

    std::ofstream arquivo("cadastro_catador.txt", std::ios::app);
    
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de cadastro." << std::endl;
        return;
    }
    
    arquivo << "Nome: " << nome << std::endl;
    arquivo << "Endereço: " << endereco << std::endl;
    arquivo << "CPF: " << cpf << std::endl;
    if (material) {
        arquivo << "Material - Peso: " << material->getPeso() 
                << ", Tipo: " << material->getTipo() << std::endl;
    } else {
        arquivo << "Material: Nulo" << std::endl;
    }
    arquivo << "Saldo: R$ " << _saldo << std::endl;
    arquivo << "------------------------" << std::endl;

    arquivo.close();
    
    std::cout << "Catador cadastrado com sucesso!" << std::endl;
}