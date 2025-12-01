#include "Validacao.hpp"
#include <algorithm>
#include <cctype>

std::string Validacao::removerCaracteresNaoNumericos(std::string str)
{
    str.erase(std::remove_if(str.begin(), str.end(), [](char c)
                             { return !std::isdigit(c); }),
              str.end());
    return str;
}

void Validacao::validarCPF(std::string cpf)
{
    cpf = removerCaracteresNaoNumericos(cpf);

    if (cpf.length() != 11)
    {
        throw std::invalid_argument("CPF deve conter 11 digitos.");
    }

    bool todosIguais = true;
    for (size_t i = 1; i < cpf.length(); i++)
    {
        if (cpf[i] != cpf[0])
            todosIguais = false;
    }
    if (todosIguais)
        throw std::invalid_argument("CPF invalido (digitos iguais).");
}

void Validacao::validarTipoMaterial(int tipo)
{
    if (tipo < 1 || tipo > 3)
    {
        throw std::invalid_argument("Tipo de material invalido. Opcoes: 1 (Plastico), 2 (Papel) ou 3 (Metal).");
    }
}

void Validacao::validarCNPJ(std::string cnpj)
{
    cnpj = removerCaracteresNaoNumericos(cnpj);

    if (cnpj.length() != 14)
    {
        throw std::invalid_argument("CNPJ deve conter 14 digitos.");
    }

    bool todosIguais = true;
    for (size_t i = 1; i < cnpj.length(); i++)
    {
        if (cnpj[i] != cnpj[0])
            todosIguais = false;
    }
    if (todosIguais)
        throw std::invalid_argument("CNPJ invalido (digitos iguais).");
}

void Validacao::validarEndereco(std::string endereco) {
    // 1. Verificação de tamanho mínimo
    if (endereco.length() < 3) {
        throw std::invalid_argument("Endereco muito curto (minimo 3 caracteres).");
    }

    // 2. Verificação de Conteúdo (Obriga a ter letras)
    bool temLetra = false;
    for (char c : endereco) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            temLetra = true;
            break;
        }
    }

    if (!temLetra) {
        throw std::invalid_argument("Endereco invalido. Digite o nome da rua ou bairro (deve conter letras).");
    }
    
    // Opcional: Proibir caracteres estranhos no início se necessário
    if (!std::isalnum(static_cast<unsigned char>(endereco[0]))) {
         // throw std::invalid_argument("O endereco deve comecar com letra ou numero.");
    }
}