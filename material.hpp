#ifndef MATERIAL_HPP
#define MATERIAL_HPP

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
	void setTipo(int);
};

#endif