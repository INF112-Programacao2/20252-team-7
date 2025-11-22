#include "colaborador.hpp"
#include <iostream>
#include <fstream>

Colaborador::Colaborador(Pessoa pessoa) : Pessoa(pessoa.getNome(), pessoa.getEndereco(), pessoa.getCpf(), pessoa.getMaterial()) {
    this->pontos = 0;
}

int Colaborador::getPontos() {
    return this->pontos;
}

void Colaborador::setPontos(int pontos) {
    this->pontos = pontos;
}

Colaborador::~Colaborador() { }

void Colaborador::cadastrarColaborador(std::string nome, std::string endereco, std::string cpf, Material* material, int pontos) {
    // CORRIGIDO: usar método base com ponteiro
    Pessoa::cadastro(nome, endereco, cpf, material);
    
    std::ofstream arquivo("cadastro_colaborador.txt", std::ios::app);
    
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de cadastro." << std::endl;
        return;
    }
    
    arquivo << "," << pontos << std::endl;
    arquivo.close();
    
    std::cout << "Colaborador cadastrado com sucesso!" << std::endl;
}
