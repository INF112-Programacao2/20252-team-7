#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <string>
#include "material.hpp"

class Pessoa {
private:
    std::string _nome;
    std::string _endereco;
    std::string _cpf;
    Material* _material;

public:
    Pessoa(std::string nome, std::string endereco, std::string cpf, Material* material = nullptr);
    ~Pessoa();
    
    std::string getNome() const;
    std::string getEndereco() const;
    std::string getCpf() const;
    Material* getMaterial() const;
    
    void setNome(std::string nome);
    void setEndereco(std::string endereco);
    void setCpf(std::string cpf);
    void setMaterial(Material* material);
    
    
    
    
    void definirMaterial(Material* mat, float p, int t);
    // REMOVIDA a linha problemática: virtual void cadastro(...) = 0;

    

};

#endif