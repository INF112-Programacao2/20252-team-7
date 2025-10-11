#include "material.h"

Material::Material() {
	preco = 0;
	peso = 0;
	tipo = 0;
}

Material::Material(float p, float pe, int t) : preco(p), peso(pe), tipo(t) {}

float Material::getPreco() {
	return this->preco;
}

float Material::getPeso() {
	return this->peso;
}

int Material::getTipo() {
	return this->tipo;
}

void Material::setPreco(float p) {
	this->preco = p;
}

void Material::setPeso(float pe) {
	this->peso = pe;
}

void Material::setTipo(int t) {
	this->tipo = t;
}

Material::~Material() {}
