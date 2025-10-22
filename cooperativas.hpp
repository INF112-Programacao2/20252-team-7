#ifndef COOPERATIVAS_HPP
#define COOPERATIVAS_HPP
#include <iostream>
#include "material.hpp"
#include "Catador.hpp"
#include "colaborador.hpp"

class Cooperativas {
private:
	float preco;
	std::string cnpj;
	std::string endereco;
	Material material;
public:
	//Construtor e destrutor
	Cooperativas();
	Cooperativas(float, std::string, std::string, Material);
	~Cooperativas();

	//Getters e Setters
	float getPreco();
	std::string getCnpj();
	std::string getEndereco();
	Material getMaterial();
	void setPreco(float);
	void setCnpj(std::string);
	void setEndereco(std::string);
	void setMaterial(Material);

	//Métodos
	void comprarMaterial(Catador&, float peso, Material);
	void calcularPreco(float, float);
	void consultarPrecoCooperativa();
	void relatorio();
	void cadastro(float, std::string, std::string, Material);
};


#endif