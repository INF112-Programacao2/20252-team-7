#include "colaborador.hpp"
#include "material.hpp"
#include <iostream>

Colaborador::Colaborador(Pessoa pessoa) : Pessoa(pessoa.getNome(), pessoa.getEndereco(), pessoa.getCpf(), pessoa.getMaterial()) {
	this->pontos = 0;
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

void Colaborador::cadastrarColaborador(std::string nome, std::string endereco, int cpf, Material material, int pontos) : Pessoa::cadastro(nome, endereco, cpf, material) {
	std::ofstream arquivo("cadastro_catador.txt", std::ios::app);

	if (!arquivo.is_open()) {
		std::cerr << "Erro ao abrir o arquivo de cadastro." << std::endl;
		return;
	}

	arquivo << "," << pontos;

	arquivo.close();
}