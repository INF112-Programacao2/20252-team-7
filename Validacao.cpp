#include "Validacao.hpp"
#include <algorithm> 
#include <cctype>    
#include <stdexcept> 

// ==================================================================================
// MÉTODO AUXILIAR: removerCaracteresNaoNumericos
// ----------------------------------------------------------------------------------
// Objetivo: Limpar a string, transformando "123.456.789-00" em "12345678900".
// ==================================================================================
std::string Validacao::removerCaracteresNaoNumericos(std::string str) {
    // A função remove_if move todos os não-dígitos para o final da string
    // O método erase apaga esses caracteres do final.
    str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
        return !std::isdigit(c); // Retorna true se NÃO for número (será removido)
    }), str.end());
    return str;
}

// ==================================================================================
// VALIDAÇÃO DE CPF
// ----------------------------------------------------------------------------------
// Lógica:
// 1. Limpa a entrada.
// 2. Verifica tamanho (deve ser 11).
// 3. Verifica padrão de dígitos iguais (ex: 111.111.111-11 é matematicamente válido
//    no cálculo de módulo, mas inválido pela Receita Federal).
// 4. Realiza o cálculo dos Dígitos Verificadores (Módulo 11).
//
// [Exceção]: Note o uso de 'throw'. Isso interrompe a função imediatamente e
// envia um erro para quem chamou (InputHandler), que deverá capturar com 'catch'.
// ==================================================================================
void Validacao::validarCPF(std::string cpf)
{
    // Remove caracteres não numéricos como '.' e '-'
    cpf = removerCaracteresNaoNumericos(cpf);

    // Verifica se tem exatamente 11 dígitos
    if (cpf.length() != 11)
    {
        // Lança exceção se o tamanho não for 11
        throw std::invalid_argument("CPF deve conter 11 digitos.");
    }

    // Verifica se todos os dígitos são iguais
    bool todosIguais = true;
    for (size_t i = 1; i < cpf.length(); i++)
    {
        if (cpf[i] != cpf[0])
            todosIguais = false;
    }
    if (todosIguais)
        throw std::invalid_argument("CPF invalido (digitos iguais).");

    // Se passou pelas verificações de formato e dígitos iguais, o CPF é considerado "válido no formato"
}

// ==================================================================================
// VALIDAÇÃO DE CNPJ
// ----------------------------------------------------------------------------------
// Segue lógica similar ao CPF, mas com pesos diferentes e tamanho 14.
// ==================================================================================
void Validacao::validarCNPJ(std::string cnpj)
{
    cnpj = removerCaracteresNaoNumericos(cnpj);

    // Verifica o tamanho
    if (cnpj.length() != 14)
    {
        throw std::invalid_argument("CNPJ deve conter 14 digitos.");
    }

    // Verifica digitos iguais
    bool todosIguais = true;
    for (size_t i = 1; i < cnpj.length(); i++)
    {
        if (cnpj[i] != cnpj[0])
            todosIguais = false;
    }
    if (todosIguais)
        throw std::invalid_argument("CNPJ invalido (digitos iguais).");
}

// ==================================================================================
// VALIDAÇÃO DE TIPO DE MATERIAL
// ----------------------------------------------------------------------------------
// Objetivo: Garantir que o usuário só digite opções existentes no menu.
// ==================================================================================
void Validacao::validarTipoMaterial(int tipo) {
    // Se o número estiver fora do intervalo 1 a 3
    if (tipo < 1 || tipo > 3) {
        // [Exceção] Lança erro de argumento inválido
        throw std::invalid_argument("Opcao invalida! Escolha: 1 (Plastico), 2 (Papel) ou 3 (Metal).");
    }
}

// ==================================================================================
// VALIDAÇÃO DE ENDEREÇO
// ----------------------------------------------------------------------------------
// Objetivo: Impedir endereços vazios, muito curtos ou que sejam apenas números.
// ==================================================================================
void Validacao::validarEndereco(std::string endereco) {
    // 1. Verifica tamanho mínimo
    if (endereco.length() < 3) {
        throw std::invalid_argument("O endereco e muito curto. Por favor, seja mais especifico.");
    }

    // 2. Verifica conteúdo (Evita endereços como "12345" ou "...")
    bool temLetra = false;
    
    // Itera sobre cada caractere da string
    for (char c : endereco) {
        // std::isalpha verifica se o caractere é uma letra (A-Z ou a-z)
        if (std::isalpha(static_cast<unsigned char>(c))) {
            temLetra = true;
            break; // Se achou uma letra, já é válido, pode parar de procurar
        }
    }

    if (!temLetra) {
        // Lança erro se não houver nenhuma letra
        throw std::invalid_argument("Endereco invalido: Deve conter o nome da rua (letras), nao apenas numeros/simbolos.");
    }
}