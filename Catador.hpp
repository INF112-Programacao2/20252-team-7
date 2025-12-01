#ifndef CATADOR_HPP
#define CATADOR_HPP

#include "Pessoa.hpp"

class Catador : public Pessoa {
private:
    float _saldo;
public:
    Catador(const Pessoa& pessoa);
    Catador(std::string nome, std::string endereco, std::string cpf, Material* material = nullptr);
    ~Catador();

    float getSaldo() const;
    void setSaldo(float valor);
    void recolherMaterial(Material* material);
    void cadastro(std::string nome, std::string endereco, std::string cpf, Material* material);
    
    // NOVOS MÉTODOS
    void visualizarCooperativas();
    void visualizarColaboradores();
    // Procura o CPF deste catador no arquivo e soma o valor ao saldo existente
    void adicionarSaldoAoArquivo(float valorAdicionado);
};

#endif