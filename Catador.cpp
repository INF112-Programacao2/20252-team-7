#include "Catador.hpp"
#include "colaborador.hpp"
#include "Pessoa.hpp"
#include <iostream>

//Construtor
Catador::Catador( Pessoa pessoa ) : Pessoa( pessoa.getNome( ), pessoa.getEndereco( ), pessoa.getCpf( ), pessoa.getMaterial( ) ) {
	this->_saldo = 0.0f;
};

//Destrutor
Catador::~Catador() {};

//Função get
float Catador::getSaldo( ) {
	return this->_saldo;
}

//Função set
void Catador::setSaldo( float valor ) {
	this->_saldo = valor;
}

//Outras funções
void Catador::recolherMaterial( Material material ) {
	float pesoAtual = this->getMaterial().getPeso();
	float novoPeso = pesoAtual + material.getPeso();
	Material matAtual = this->getMaterial();
	matAtual.setPeso(novoPeso);
	this->setMaterial(matAtual);
}

void Catador::cadastro(std::string nome, std::string endereco, int cpf, Material material, float saldo) : Pessoa::cadatro(nome, endereco, cpf, material) {


	std::ofstream arquivo("cadastro_catador.txt", std::ios::app);

	if (!arquivo.is_open()) {
		std::cerr << "Erro ao abrir o arquivo de cadastro." << std::endl;
		return;
	}

	arquivo << "," << saldo;

	arquivo.close();
}
