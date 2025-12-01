#ifndef VALIDACAO_HPP
#define VALIDACAO_HPP

#include <string>
#include <stdexcept>

class Validacao {
public:
    static void validarCPF(std::string cpf);
    static void validarCNPJ(std::string cnpj);
    static void validarTipoMaterial(int tipo);
    static void validarEndereco(std::string endereco);
    static std::string removerCaracteresNaoNumericos(std::string str);
};

#endif