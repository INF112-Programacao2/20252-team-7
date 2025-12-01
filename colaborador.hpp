#ifndef COLABORADOR_HPP
#define COLABORADOR_HPP

#include <string>
#include "Pessoa.hpp"

class Colaborador : public Pessoa {
private:
    int pontos;
public:
    Colaborador(const Pessoa& pessoa);
    Colaborador(std::string nome, std::string endereco, std::string cpf, Material* material = nullptr);
    ~Colaborador();

    int getPontos() const;
    void setPontos(int pontos);
    
    void cadastro(std::string nome, std::string endereco, std::string cpf, Material* material);
    
    // Calcula pontos baseado no material (Regra x2, x3, x4)
    void realizarDoacao(Material* materialDoado);

    // [CORREÇÃO] Este método volta para permitir bônus fixos (ex: cadastro)
    void receberPontos(int valor); 

    void visualizarCooperativas();
    
    void carregarPontos(); 
    void salvarPontosNoArquivo();
};

#endif