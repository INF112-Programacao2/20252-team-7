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

    // Verifica digitos iguais
    bool todosIguais = true;
    for (size_t i = 1; i < cpf.length(); i++)
    {
        if (cpf[i] != cpf[0])
            todosIguais = false;
    }
    if (todosIguais)
        throw std::invalid_argument("CPF invalido (digitos iguais).");

    // Digitos verificadores
    int soma = 0;
    for (int i = 0; i < 9; i++)
        soma += (cpf[i] - '0') * (10 - i);
    int primeiro = 11 - (soma % 11);
    if (primeiro >= 10)
        primeiro = 0;
    if (primeiro != (cpf[9] - '0'))
        throw std::invalid_argument("CPF invalido.");

    soma = 0;
    for (int i = 0; i < 10; i++)
        soma += (cpf[i] - '0') * (11 - i);
    int segundo = 11 - (soma % 11);
    if (segundo >= 10)
        segundo = 0;
    if (segundo != (cpf[10] - '0'))
        throw std::invalid_argument("CPF invalido.");
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

    int pesos1[12] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    int soma = 0;
    for (int i = 0; i < 12; i++)
        soma += (cnpj[i] - '0') * pesos1[i];
    int d1 = soma % 11;
    d1 = (d1 < 2) ? 0 : 11 - d1;
    if (d1 != (cnpj[12] - '0'))
        throw std::invalid_argument("CNPJ invalido.");

    int pesos2[13] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    soma = 0;
    for (int i = 0; i < 13; i++)
        soma += (cnpj[i] - '0') * pesos2[i];
    int d2 = soma % 11;
    d2 = (d2 < 2) ? 0 : 11 - d2;
    if (d2 != (cnpj[13] - '0'))
        throw std::invalid_argument("CNPJ invalido.");
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