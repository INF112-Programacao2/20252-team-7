#include "Pessoa.hpp"
#include "material.hpp"
#include <iostream>

Pessoa::Pessoa(std::string nome, std::string endereco, std::string cpf, Material* material)
    : _nome(nome), _endereco(endereco), _cpf(cpf), _material(material) {}

Pessoa::~Pessoa() {}

std::string Pessoa::getNome() const { return _nome; }
std::string Pessoa::getEndereco() const { return _endereco; }
std::string Pessoa::getCpf() const { return _cpf; }
Material* Pessoa::getMaterial() const { return _material; }

void Pessoa::setNome(std::string nome) { _nome = nome; }
void Pessoa::setEndereco(std::string endereco) { _endereco = endereco; }
void Pessoa::setCpf(std::string cpf) { _cpf = cpf; }           // <<< IMPLEMENTADO
void Pessoa::setMaterial(Material* material) { _material = material; }

void Pessoa::definirMaterial(Material* mat, float p, int t) {
    if (mat) {
        mat->setPeso(p);
        mat->setTipo(t);
    }
}