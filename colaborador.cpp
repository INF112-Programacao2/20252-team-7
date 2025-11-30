#include "colaborador.hpp"
#include <iostream>
#include <fstream>

Colaborador::Colaborador(const Pessoa& pessoa) : Pessoa(pessoa), pontos(0) {}
Colaborador::Colaborador(std::string nome, std::string endereco, std::string cpf, Material* material)
    : Pessoa(nome, endereco, cpf, material), pontos(0) {}

Colaborador::~Colaborador() {}

int Colaborador::getPontos() const { return pontos; }
void Colaborador::setPontos(int p) { pontos = p; }

void Colaborador::cadastro(std::string nome, std::string endereco, std::string cpf, Material* material) {
    setNome(nome);
    setEndereco(endereco);
    setCpf(cpf);
    setMaterial(material);

    std::ofstream arq("cadastro_colaborador.txt", std::ios::app);
    if (!arq.is_open()) {
        std::cerr << "Erro ao salvar cadastro do colaborador.\n";
        return;
    }
    arq << "Nome: " << nome << "\nEndereço: " << endereco << "\nCPF: " << cpf << "\n";
    if (material) arq << "Material: " << material->getPeso() << "kg (tipo " << material->getTipo() << ")\n";
    arq << "Pontos: " << pontos << "\n------------------------\n";
    arq.close();
    std::cout << "Colaborador cadastrado com sucesso!\n";
}

void Colaborador::receberPontos(int pontosBase) {
    Material* m = getMaterial();
    if (!m || m->getPeso() <= 0) {
        std::cout << "Sem material válido para calcular pontos.\n";
        return;
    }
    int mult = 1;
    switch (m->getTipo()) {
        case 1: mult = 2; break;
        case 2: mult = 3; break;
        case 3: mult = 5; break;
    }
    float bonus = pontosBase * mult * (10.0f / m->getPeso());
    pontos += static_cast<int>(bonus + 0.5f);
    std::cout << "Pontos recebidos! Total: " << pontos << "\n";
}