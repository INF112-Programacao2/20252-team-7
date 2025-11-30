#ifndef COLABORADOR_HPP
#define COLABORADOR_HPP

#include <string>
#include "Pessoa.hpp"

class Colaborador : public Pessoa {
private:
    int pontos;
public:
    Colaborador(const Pessoa& pessoa);
    Colaborador(std::string nome, std::string endereco, std::string cpf, Material* material = nullptr); // NOVO
    ~Colaborador();

    int getPontos() const;
    void setPontos(int pontos);
    void cadastro(std::string nome, std::string endereco, std::string cpf, Material* material);
    void receberPontos(int pontosRecebidos);
};

#endif