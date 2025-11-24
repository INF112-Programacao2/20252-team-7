#ifndef CATADOR_HPP
#define CATADOR_HPP

#include "Pessoa.hpp"

class Catador : public Pessoa {
private:
    float _saldo;
public:
    Catador(Pessoa pessoa);
    ~Catador();

    float getSaldo();
    void setSaldo(float valor);

    // CORRIGIDO: Material* em vez de Material
    void recolherMaterial(Material* material);
    void cadastro(std::string nome, std::string endereco, std::string cpf, Material* material, float saldo);
};

#endif