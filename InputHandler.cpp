#include "InputHandler.hpp"
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