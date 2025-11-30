#ifndef COOPERATIVAS_HPP
#define COOPERATIVAS_HPP
#include <iostream>
#include <string>

class Material;
class Catador;
class Colaborador;

class Cooperativas {
private:
    float preco;
    std::string cnpj;
    std::string endereco;
    Material* material;
    
public:
    Cooperativas();
    Cooperativas(float, std::string, std::string, Material*);
    ~Cooperativas();

    float getPreco();
    std::string getCnpj();
    std::string getEndereco();
    Material* getMaterial();
    void setPreco(float);
    void setCnpj(std::string);
    void setEndereco(std::string);
    void setMaterial(Material*);

    void comprarMaterial(Catador& catador, float peso, float precoPorKg); // <<< nome correto
    void calcularPreco(float peso, float precoPorKg);
    void consultarPrecoCooperativa();
    void relatorio();
    void cadastro(float preco, std::string endereco, std::string cnpj, Material* material);
};

#endif