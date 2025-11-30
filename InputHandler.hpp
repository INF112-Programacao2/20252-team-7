// InputHandler.hpp
#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <iostream>
#include <string>
#include <limits>

class InputHandler {
public:
    static int getInt(const std::string& prompt);
    static float getFloat(const std::string& prompt);
    static std::string getString(const std::string& prompt);
    
    // Novas funções para CPF e CNPJ
    static std::string getCPF(const std::string& prompt);
    static std::string getCNPJ(const std::string& prompt);
};

#endif