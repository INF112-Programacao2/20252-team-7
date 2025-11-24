#ifndef COLABORADOR_HPP
#define COLABORADOR_HPP

#include <string>
#include "Pessoa.hpp"

class Colaborador : public Pessoa {
private:
    int pontos;
public:
    Colaborador(Pessoa pessoa);
    ~Colaborador();

    int getPontos();
    void setPontos(int pontos);
    
    // CORRIGIDO: Material* em vez de Material
    void cadastrarColaborador(std::string nome, std::string endereco, std::string cpf, Material* material, int pontos);
};

#endif