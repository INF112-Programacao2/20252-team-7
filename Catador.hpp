#ifndef CATADOR_HPP
#define CATADOR_HPP

#include "Pessoa.hpp"  // ADICIONAR: incluir a classe base
// REMOVER: #include "colaborador.hpp" - não é necessário

class Catador : public Pessoa {
private:
    float _saldo;
public:
    Catador(Pessoa pessoa);
    ~Catador();

    float getSaldo();
    void setSaldo(float valor);

    void recolherMaterial(Material* material);  // MUDEI: ponteiro
    void cadastro(std::string nome, std::string endereco, std::string cpf, Material* material, float saldo);
};

#endif
