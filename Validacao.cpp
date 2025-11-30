#include "Validacao.hpp"
#include <string>
#include <algorithm>
#include <cctype> 

std::string Validacao::removerCaracteresNaoNumericos(std::string str) {
    str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
        return !std::isdigit(c);
    }), str.end());
    return str;
}

bool Validacao::validarCPF(std::string cpf) {
    cpf = removerCaracteresNaoNumericos(cpf);
    
    if (cpf.length() != 11) {
        return false;
    }
    
    // Verifica se todos os dígitos são iguais
    bool todosIguais = true;
    for (size_t i = 1; i < cpf.length(); i++) {
        if (cpf[i] != cpf[0]) {
            todosIguais = false;
            break;
        }
    }
    if (todosIguais) return false;
    
    // Cálculo dos dígitos verificadores
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * (10 - i);
    }
    int primeiroDigito = 11 - (soma % 11);
    if (primeiroDigito >= 10) primeiroDigito = 0;

    if (primeiroDigito != (cpf[9] - '0')) {
        return false;
    }

    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += (cpf[i] - '0') * (11 - i);
    }
    int segundoDigito = 11 - (soma % 11);
    if (segundoDigito >= 10) segundoDigito = 0;

    return segundoDigito == (cpf[10] - '0');
}

bool Validacao::validarCNPJ(std::string cnpj) {
    cnpj = removerCaracteresNaoNumericos(cnpj);
    
    if (cnpj.length() != 14) {
        return false;
    }

    // Cálculo do primeiro dígito verificador
    int pesos1[12] = {5,4,3,2,9,8,7,6,5,4,3,2};
    int soma = 0;
    for (int i = 0; i < 12; i++) {
        soma += (cnpj[i] - '0') * pesos1[i];
    }
    int primeiroDigito = soma % 11;
    primeiroDigito = (primeiroDigito < 2) ? 0 : 11 - primeiroDigito;

    if (primeiroDigito != (cnpj[12] - '0')) {
        return false;
    }

    // Cálculo do segundo dígito verificador
    int pesos2[13] = {6,5,4,3,2,9,8,7,6,5,4,3,2};
    soma = 0;
    for (int i = 0; i < 13; i++) {
        soma += (cnpj[i] - '0') * pesos2[i];
    }
    int segundoDigito = soma % 11;
    segundoDigito = (segundoDigito < 2) ? 0 : 11 - segundoDigito;

    return segundoDigito == (cnpj[13] - '0');
}