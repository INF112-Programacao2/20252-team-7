#include "InputHandler.hpp"
#include "Validacao.hpp"
#include <iostream>
#include <string>
#include <limits> // Necessário para numeric_limits

int InputHandler::getInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear(); // Limpa o estado de erro
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
            std::cout << "Entrada invalida! Digite um numero inteiro.\n";
        } else {
            // Importante: Limpa o buffer após ler o número para não atrapalhar o próximo getline
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
            std::cout << "Entrada invalida! Digite um numero decimal (use ponto).\n";
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

std::string InputHandler::getCPF(const std::string& prompt) {
    std::string cpf;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, cpf);
        
        try {
            Validacao::validarCPF(cpf);
            return Validacao::removerCaracteresNaoNumericos(cpf);
        } catch (const std::invalid_argument& e) {
            std::cerr << "ERRO: " << e.what() << "\n";
            std::cout << "Tente novamente (ex: 123.456.789-01).\n";
        }
    }
}

std::string InputHandler::getCNPJ(const std::string& prompt) {
    std::string cnpj;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, cnpj);
        
        try {
            Validacao::validarCNPJ(cnpj);
            return Validacao::removerCaracteresNaoNumericos(cnpj);
        } catch (const std::invalid_argument& e) {
            std::cerr << "ERRO: " << e.what() << "\n";
            std::cout << "Tente novamente (ex: 11.222.333/0001-81).\n";
        }
    }
}

int InputHandler::getTipoMaterial(const std::string& prompt) {
    int tipo;
    while (true) {
        std::cout << "\n=== SELECIONE O TIPO DE MATERIAL ===\n";
        std::cout << "[1] Plastico\n";
        std::cout << "[2] Papel\n";
        std::cout << "[3] Metal\n";
        std::cout << "------------------------------------\n";

        tipo = getInt(prompt); 
        
        try {
            Validacao::validarTipoMaterial(tipo);
            return tipo;
        } catch (const std::invalid_argument& e) {
            std::cerr << "ERRO: " << e.what() << "\n";
            std::cout << "Tente novamente.\n";
        }
    }
}

// === A IMPLEMENTAÇÃO QUE FALTAVA ===
std::string InputHandler::getEndereco(const std::string& prompt) {
    std::string endereco;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, endereco);
        
        try {
            // Chama a validação (tamanho minimo e presença de letras)
            Validacao::validarEndereco(endereco);
            return endereco; // Se não deu erro, retorna o endereço
        } catch (const std::invalid_argument& e) {
            std::cerr << "ERRO: " << e.what() << "\n";
            std::cout << "Por favor, digite o endereco corretamente.\n";
        }
    }
}