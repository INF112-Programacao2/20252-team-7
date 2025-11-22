#ifndef COLABORADOR_HPP
#define COLABORADOR_HPP

#include <string>
#include "Pessoa.hpp"  // ADICIONAR: incluir a classe base
// REMOVER: #include "material.hpp" - já vem via Pessoa

class Colaborador : public Pessoa {
private:
    int pontos;
public:
    Colaborador(Pessoa pessoa);
    ~Colaborador();

    int getPontos();
    void setPontos(int pontos);
    
    void cadastrarColaborador(std::string nome, std::string endereco, std::string cpf, Material* material, int pontos);
};

#endif
