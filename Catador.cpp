#include "Catador.hpp"
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


