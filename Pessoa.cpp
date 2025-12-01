#include "Pessoa.hpp"
#include <iostream>

Pessoa::Pessoa(std::string nome, std::string endereco, std::string cpf, Material* material)
    : _nome(nome), _endereco(endereco), _cpf(cpf), _material(material) {}

Pessoa::~Pessoa() {
    if (_material != nullptr) {
        delete _material;
        _material = nullptr;
    }
}

std::string Pessoa::getNome() const { return _nome; }
std::string Pessoa::getEndereco() const { return _endereco; }
std::string Pessoa::getCpf() const { return _cpf; }
Material* Pessoa::getMaterial() const { return _material; }

void Pessoa::setNome(std::string nome) { _nome = nome; }
void Pessoa::setEndereco(std::string endereco) { _endereco = endereco; }
void Pessoa::setCpf(std::string cpf) { _cpf = cpf; }

void Pessoa::setMaterial(Material* material) { 
    // Se já existe um material, deleta antes de substituir
    if (_material != nullptr) {
        delete _material;
    }
    _material = material; 
}

void Pessoa::definirMaterial(Material* mat, float p, int t) {
    if (mat) {
        mat->setPeso(p);
        mat->setTipo(t);
    }
}