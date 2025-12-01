#include "material.hpp"
#include <string>

Material::Material() : peso(0), tipo(0) {}
Material::Material(float p, int t) : peso(p), tipo(t) {}
Material::~Material() {}

float Material::getPeso() { return this->peso; }
int Material::getTipo() { return this->tipo; }

// IMPLEMENTAÇÃO NOVA
std::string Material::getNomeTipo() {
    switch(this->tipo) {
        case 1: return "Plastico";
        case 2: return "Papel";
        case 3: return "Metal";
        default: return "Indefinido";
    }
}

void Material::setPeso(float pe) { this->peso = pe; }
void Material::setTipo(int t) { this->tipo = t; }