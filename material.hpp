#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <string>

class Material {
private:
	float peso;
	int tipo;
public:
	//Construtor e destrutor
	Material();
	Material(float, int);
	~Material();

	//Getters e Setters
	float getPeso();
	int getTipo();
	void setPeso(float);
	std::string getNomeTipo();
	void setTipo(int);
};

#endif