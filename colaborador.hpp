#ifndef COLABORADOR_HPP
#define COLABORADOR_HPP

#include <string>
#include "material.hpp"
#include "Pessoa.hpp"

class Colaborador : public Pessoa {
private:
	int pontos;
public:
	//Construtor e destrutor
	Colaborador(Pessoa pessoa);
	~Colaborador();

	//Getters e Setters
	int getPontos();
	//Material getMaterial();
	//std::string getEndereco();
	void setPontos(int);
	//void setMaterial(Material);
	//void setEndereco(std::string);

	//Outros métodos
	void cadastrarColaborador(std::string nome, std::string endereco, std::string cpf, Material material, int pontos);
};

#endif 
