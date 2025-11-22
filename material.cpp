#include "material.hpp"  // CORRIGIDO: era "material.h"
Material::Material() {
	peso = 0;
	tipo = 0;
}

Material::Material(float p, int t) : peso(p), tipo(t) {}

float Material::getPeso() {
	return this->peso;
}

int Material::getTipo() {
	return this->tipo;
}

void Material::setPeso(float pe) {
	this->peso = pe;
}

void Material::setTipo(int t) {
	this->tipo = t;
}

Material::~Material() {}
