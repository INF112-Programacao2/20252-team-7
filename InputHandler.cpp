#include "InputHandler.hpp"
#include "Validacao.hpp"
#include <iostream>
#include <string>
#include <limits>

int InputHandler::getInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear(); // Limpa o estado de erro
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida! Digite um número: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

float InputHandler::getFloat(const std::string& prompt) {
    float value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida! Digite um número: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

std::string InputHandler::getString(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// Implementações das novas funções
std::string InputHandler::getCPF(const std::string& prompt) {
    std::string cpf;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, cpf);
        
        if (Validacao::validarCPF(cpf)) {
            return cpf;
        } else {
            std::cout << "CPF inválido! Deve conter 11 dígitos numéricos.\n";
            std::cout << "Exemplo válido: 12345678901 ou 123.456.789-01\n";
        }
    }
}

std::string InputHandler::getCNPJ(const std::string& prompt) {
    std::string cnpj;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, cnpj);
        
        if (Validacao::validarCNPJ(cnpj)) {
            return cnpj;
        } else {
            std::cout << "CNPJ inválido! Deve conter 14 dígitos numéricos.\n";
            std::cout << "Exemplo válido: 11222333000181 ou 11.222.333/0001-81\n";
        }
    }
}