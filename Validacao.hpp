// Validacao.hpp
#ifndef VALIDACAO_HPP
#define VALIDACAO_HPP

#include <string>

class Validacao {
public:
    static bool validarCPF(std::string cpf);
    static bool validarCNPJ(std::string cnpj);
    static std::string removerCaracteresNaoNumericos(std::string str);
};

#endif