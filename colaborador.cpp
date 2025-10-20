#include "colaborador.hpp"
#include "material.hpp"
#include <iostream>

Colaborador::Colaborador() {
	pontos = 0;
	endereco = "";
}

Colaborador::Colaborador(int pontos, Material material, std::string endereco) {
	this->pontos = pontos;
	this->material = material;
	this->endereco = endereco;
}

int Colaborador::getPontos() {
	return this->pontos;
}

Material Colaborador::getMaterial() {
	return this->material;
}

std::string Colaborador::getEndereco() {
	return this->endereco;
}

void Colaborador::setPontos(int pontos) {
	this->pontos = pontos;
}

void Colaborador::setMaterial(Material material) {
	this->material = material;
}

void Colaborador::setEndereco(std::string endereco) {
	this->endereco = endereco;
}

Colaborador::~Colaborador() {}

