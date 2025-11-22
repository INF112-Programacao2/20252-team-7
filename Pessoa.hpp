#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <string>
// REMOVER: #include "material.hpp" - causa include circular

// Declaração antecipada
class Material;

class Pessoa {
private:
    std::string _nome;
    std::string _endereco;
    std::string _cpf;  // JÁ CORRIGIDO: string em vez de int
    Material* _material;  // MUDEI: ponteiro ou referência

public:
    Pessoa(std::string nome, std::string endereco, std::string cpf, Material* material);
    ~Pessoa();
    
    std::string getNome();
    std::string getEndereco();
    std::string getCpf();
    Material* getMaterial();  // MUDEI: retorna ponteiro
    
    void setNome(std::string nome);
    void setEndereco(std::string endereco);
    void setMaterial(Material* material);  // MUDEI: recebe ponteiro
    
    void definirMaterial(Material* mat, float p, int t);
    void cadastro(std::string nome, std::string endereco, std::string cpf, Material* material);
};

#endif
