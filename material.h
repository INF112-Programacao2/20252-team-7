#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
private:
	float preco;
	float peso;
	int tipo;
public:
	Material();
	Material(float, float, int);
	float getPreco();
	float getPeso();
	int getTipo();
	void setPreco(float);
	void setPeso(float);
	void setTipo(int);
	~Material();
};


#endif