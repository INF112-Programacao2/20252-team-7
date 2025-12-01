#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <string>
#include <iostream>

class InputHandler {
public:
    // Funções genéricas
    static int getInt(const std::string& prompt);
    static float getFloat(const std::string& prompt);
    static std::string getString(const std::string& prompt);
    
    // Funções com validação específica
    static std::string getCPF(const std::string& prompt);
    static std::string getCNPJ(const std::string& prompt);
    static int getTipoMaterial(const std::string& prompt);
    
    // O novo método de endereço
    static std::string getEndereco(const std::string& prompt);
};

#endif