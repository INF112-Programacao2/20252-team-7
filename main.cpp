#include <iostream>
#include "Pessoa.hpp"
#include "material.hpp"
#include "colaborador.hpp"
#include "Catador.hpp"
#include "cooperativas.hpp"

int main() {
    // Criando um material
    Material m(5.0f, 1);

    // Criando uma pessoa
    Pessoa p("Joao Silva", "Rua A, 123", 123456789, m);

    // Criando um colaborador e um catador a partir da pessoa (construtores existentes esperados)
    Colaborador col(p);
    Catador cat(p);

    // Criando uma cooperativa
    Cooperativas coop;

    // Exibindo alguns dados
    std::cout << "Pessoa: " << p.getNome() << "\n";
    std::cout << "Endereco: " << p.getEndereco() << "\n";
    std::cout << "CPF: " << p.getCpf() << "\n";
    std::cout << "Material peso: " << p.getMaterial().getPeso() << ", tipo: " << p.getMaterial().getTipo() << "\n";

    std::cout << "Colaborador pontos (inicial): " << col.getPontos() << "\n";
    std::cout << "Catador saldo (inicial): " << cat.getSaldo() << "\n";

    // Demonstração simples de uso de setters
    col.setPontos(10);
    cat.setSaldo(50.0f);

    std::cout << "Colaborador pontos (atual): " << col.getPontos() << "\n";
    std::cout << "Catador saldo (atual): " << cat.getSaldo() << "\n";

    return 0;
}