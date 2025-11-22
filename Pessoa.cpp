#include "Pessoa.hpp"
#include "material.hpp"  // AGORA pode incluir aqui
#include <iostream>
#include <fstream>

// Construtor
Pessoa::Pessoa(std::string nome, std::string endereco, std::string cpf, Material* material) :
    _nome(nome), _endereco(endereco), _cpf(cpf), _material(material) { }

Pessoa::~Pessoa() { }

// Getters
std::string Pessoa::getNome() {
    return _nome;
}

std::string Pessoa::getEndereco() {
    return _endereco;
}

std::string Pessoa::getCpf() {
    return _cpf;
}

Material* Pessoa::getMaterial() {
    return _material;
}

// Setters
void Pessoa::setNome(std::string novoNome) {
    _nome = novoNome;
}

void Pessoa::setEndereco(std::string novoEndereco) {
    _endereco = novoEndereco;
}

void Pessoa::setMaterial(Material* novoMaterial) {
    _material = novoMaterial;
}

// Métodos
void Pessoa::definirMaterial(Material* mat, float p, int t) {
    mat->setPeso(p);
    mat->setTipo(t);
}

void Pessoa::cadastro(std::string nome, std::string endereco, std::string cpf, Material* material) {
    std::ofstream arquivo("cadastro.txt", std::ios::app);
    
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de cadastro." << std::endl;
        return;
    }
    
    arquivo << nome << "," << endereco << "," << cpf << "," 
            << material->getPeso() << "," << material->getTipo() << std::endl;
    
    arquivo.close();
}
