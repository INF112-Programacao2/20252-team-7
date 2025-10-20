#ifndef COLABORADOR_HPP
#define COLABORADOR_HPP

#include <string>
#include "material.hpp"

class Colaborador {
private:
	int pontos;
	Material material;
	std::string endereco;
public:
	//Construtor e destrutor
	Colaborador();
	Colaborador(int, Material, std::string);
	~Colaborador();

	//Getters e Setters
	int getPontos();
	Material getMaterial();
	std::string getEndereco();
	void setPontos(int);
	void setMaterial(Material);
	void setEndereco(std::string);
};


#endif 
