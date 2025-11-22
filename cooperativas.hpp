#ifndef COOPERATIVAS_HPP
#define COOPERATIVAS_HPP
#include <iostream>
#include <string>

// Declarações antecipadas
class Material;
class Catador;
class Colaborador;

class Cooperativas {
private:
    float preco;
    std::string cnpj;
    std::string endereco;
    Material* material;  // MUDEI: ponteiro
    
public:
    // Construtor e destrutor
    Cooperativas();
    Cooperativas(float, std::string, std::string, Material*);  // MUDEI: ponteiro
    ~Cooperativas();

    // Getters e Setters
    float getPreco();
    std::string getCnpj();
    std::string getEndereco();
    Material* getMaterial();  // MUDEI: retorna ponteiro
    void setPreco(float);
    void setCnpj(std::string);
    void setEndereco(std::string);
    void setMaterial(Material*);  // MUDEI: recebe ponteiro

    // Métodos
    void comprarMaterial(Catador& catador, float peso, float preco);  // CORRIGIDO: parâmetro preco
    void calcularPreco(float peso, float precoPorKg);
    void consultarPrecoCooperativa();
    void relatorio();
    void cadastro(float preco, std::string endereco, std::string cnpj, Material* material);  // MUDEI: ponteiro
};

#endif
