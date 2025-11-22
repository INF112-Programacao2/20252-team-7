#include "cooperativas.hpp"
#include "material.hpp"
#include "Catador.hpp"
#include "colaborador.hpp"
#include <iostream>
#include <fstream>

Cooperativas::Cooperativas() {
    preco = 0;
    cnpj = "";
    endereco = "";
    material = nullptr;  // INICIALIZAR ponteiro
}

Cooperativas::Cooperativas(float preco, std::string cnpj, std::string endereco, Material* material) {
    this->preco = preco;
    this->cnpj = cnpj;
    this->endereco = endereco;
    this->material = material;
}

float Cooperativas::getPreco() {
    return this->preco;
}

std::string Cooperativas::getCnpj() {
    return this->cnpj;
}

std::string Cooperativas::getEndereco() {
    return this->endereco;
}

Material* Cooperativas::getMaterial() {  // MUDEI: retorna ponteiro
    return this->material;
}

void Cooperativas::setPreco(float preco) {
    this->preco = preco;
}

void Cooperativas::setCnpj(std::string cnpj) {
    this->cnpj = cnpj;
}

void Cooperativas::setEndereco(std::string endereco) {
    this->endereco = endereco;
}

void Cooperativas::setMaterial(Material* material) {  // MUDEI: recebe ponteiro
    this->material = material;
}

Cooperativas::~Cooperativas() {}

void Cooperativas::calcularPreco(float peso, float precoPorKg) {
    float total = peso * precoPorKg;
    std::cout << "Total a pagar: R$ " << total << std::endl;
}

void Cooperativas::comprarMaterial(Catador& catador, float peso, float precoPorKg) {
    if (catador.getEndereco() == this->endereco) {  // CORRIGIDO: () faltando
        catador.setSaldo(catador.getSaldo() + (peso * precoPorKg));
        std::cout << "Compra realizada! Catador " << catador.getNome() 
                  << " recebeu R$ " << (peso * precoPorKg) << std::endl;
    }
}

void Cooperativas::consultarPrecoCooperativa() {
    std::cout << "Preço base da cooperativa: R$ " << preco << " por kg" << std::endl;
}

void Cooperativas::relatorio() {
    std::cout << "=== RELATÓRIO COOPERATIVA ===" << std::endl;
    std::cout << "CNPJ: " << cnpj << std::endl;
    std::cout << "Endereço: " << endereco << std::endl;
    std::cout << "Preço base: R$ " << preco << std::endl;
    if (material) {
        std::cout << "Material: " << material->getPeso() << "kg, tipo " << material->getTipo() << std::endl;
    }
}

void Cooperativas::cadastro(float preco, std::string endereco, std::string cnpj, Material* material) {
    this->preco = preco;
    this->endereco = endereco;
    this->cnpj = cnpj;
    this->material = material;
    
    std::ofstream arquivo("cadastro_cooperativa.txt", std::ios::app);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de cadastro." << std::endl;
        return;
    }

    arquivo << preco << "," << endereco << "," << cnpj << ",";
    if (material) {
        arquivo << material->getPeso() << "," << material->getTipo();
    }
    arquivo << std::endl;

    arquivo.close();
    
    std::cout << "Cooperativa cadastrada com sucesso!" << std::endl;
}
