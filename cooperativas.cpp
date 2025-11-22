#include "cooperativas.hpp"
#include "material.hpp"
#include "Catador.hpp"
#include "colaborador.hpp"
#include <iostream>

Cooperativas::Cooperativas() {
	preco = 0;
	cnpj = "";
	endereco = "";
}

Cooperativas::Cooperativas(float preco, std::string cnpj, std::string endereco, Material material) {
	this->preco = preco;
	this->cnpj = cnpj;
	this->endereco = endereco;
	this->material = material;
}

float Cooperativas::getPreco() {
	return this->preco;
}

std::string Cooperativas::getCnpj() {
	return this->cnpj;
}

std::string Cooperativas::getEndereco() {
	return this->endereco;
}

Material Cooperativas::getMaterial() {
	return this->material;
}

void Cooperativas::setPreco(float preco) {
	this->preco = preco;
}

void Cooperativas::setCnpj(std::string cnpj) {
	this->cnpj = cnpj;
}

void Cooperativas::setEndereco(std::string endereco) {
	this->endereco = endereco;
}

void Cooperativas::setMaterial(Material material) {
	this->material = material;
}

Cooperativas::~Cooperativas() {}

void Cooperativas::calcularPreco(float peso, float preco) {
	float total = peso * preco;
	std::cout << "Total a pagar: R$ " << total << std::endl;
}

void Cooperativas::comprarMaterial(Catador& catador, float peso, float preco) {  // CORRIGIDO: parâmetro preco
    if (catador.getEndereco() == this->endereco) {  //  () faltando
        catador.setSaldo(catador.getSaldo() + (peso * preco));
    }
}

void Cooperativas::consultarPrecoCooperativa() {
	
}

void Cooperativas::relatorio() {
	
}

void Cooperativas::cadastro(float preco, std::string endereco, std::string cnpj, Material material) {
	std::ofstream arquivo("cadastro.txt", std::ios::app);

	if (!arquivo.is_open()) {
		std::cerr << "Erro ao abrir o arquivo de cadastro." << std::endl;
		return 1;
	}

	arquivo << preco << "," << endereco << "," << cnpj << ","
		<< material.getPeso() << "," << material.getTipo();

	arquivo.close();
}
