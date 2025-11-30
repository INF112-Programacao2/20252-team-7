#include <iostream>
#include <string>
#include "material.hpp"
#include "colaborador.hpp"
#include "Catador.hpp"
#include "cooperativas.hpp"

int main() {
    Cooperativas coop;
    coop.setEndereco("Rua das Flores, 100");
    coop.setPreco(5.5f);

    int op;
    do {
        std::cout << "\n=== SISTEMA DE RECICLAGEM ===\n";
        std::cout << "1. Cadastrar Colaborador\n";
        std::cout << "2. Cadastrar Catador\n";
        std::cout << "3. Cooperativa comprar material\n";
        std::cout << "4. Colaborador receber pontos\n";
        std::cout << "0. Sair\n";
        std::cout << "Opção: ";
        std::cin >> op;
        std::cin.ignore();

        if (op == 1 || op == 2) {
            std::string nome, end, cpf;
            float peso; int tipo;
            std::cout << "Nome: "; std::getline(std::cin, nome);
            std::cout << "Endereço: "; std::getline(std::cin, end);
            std::cout << "CPF: "; std::getline(std::cin, cpf);
            std::cout << "Peso do material (kg): "; std::cin >> peso;
            std::cout << "Tipo (1-Plástico 2-Papel 3-Metal): "; std::cin >> tipo;

            Material mat(peso, tipo);

            if (op == 1) {
                Colaborador col(nome, end, cpf, &mat);
                col.cadastro(nome, end, cpf, &mat);
                col.receberPontos(100);
            } else {
                Catador cat(nome, end, cpf, &mat);
                cat.cadastro(nome, end, cpf, &mat);
            }
        }
        else if (op == 3) {
            std::string nome, cpf;
            float peso, precoKg;
            std::cout << "Nome do catador: "; std::getline(std::cin, nome);
            std::cout << "CPF do catador: "; std::getline(std::cin, cpf);
            std::cout << "Peso a vender (kg): "; std::cin >> peso;
            std::cout << "Preço por kg: "; std::cin >> precoKg;

            Material m(0, 1);
            Catador cat(nome, "Rua das Flores, 100", cpf, &m); // endereço tem que bater
            coop.comprarMaterial(cat, peso, precoKg);
        }
        else if (op == 4) {
            std::cout << "Funcionalidade de pontos já demonstrada no cadastro!\n";
        }

    } while (op != 0);

    std::cout << "Sistema encerrado. Até logo!\n";
    return 0;
}