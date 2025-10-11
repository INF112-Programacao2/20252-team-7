#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
private:
	float peso;
	int tipo;
public:
	Material();
	Material(float, int);
	float getPeso();
	int getTipo();
	void setPeso(float);
	void setTipo(int);
	~Material();
};

#endif