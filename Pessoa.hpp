#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <string>
#include "material.hpp"  // INCLUIR DIRETAMENTE em vez de declaração antecipada

class Pessoa {
private:
    std::string _nome;
    std::string _endereco;
    std::string _cpf;
    Material* _material;

public:
    Pessoa(std::string nome, std::string endereco, std::string cpf, Material* material);
    ~Pessoa();
    
    std::string getNome();
    std::string getEndereco();
    std::string getCpf();
    Material* getMaterial();
    
    void setNome(std::string nome);
    void setEndereco(std::string endereco);
    void setMaterial(Material* material);
    
    void definirMaterial(Material* mat, float p, int t);
    void cadastro(std::string nome, std::string endereco, std::string cpf, Material* material);
};

#endif