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
void Validacao::validarCPF(std::string cpf) {
    cpf = removerCaracteresNaoNumericos(cpf);
    
    // Verificação de Tamanho
    if (cpf.length() != 11) {
        // [Exceção] Lança erro se o tamanho estiver errado
        throw std::invalid_argument("CPF invalido: O documento deve conter exatamente 11 digitos.");
    }
    
    // Verificação de Dígitos Iguais (Ex: 000.000.000-00)
    bool todosIguais = true;
    for (size_t i = 1; i < cpf.length(); i++) {
        if (cpf[i] != cpf[0]) {
            todosIguais = false;
            break; // Se achou um diferente, o CPF não é de dígitos iguais
        }
    }
    if (todosIguais) {
        // Lança erro pois CPFs com todos dígitos iguais são inválidos
        throw std::invalid_argument("CPF invalido: Sequencia de digitos repetidos.");
    }
    
    // Cálculo Matemático (Primeiro Dígito Verificador)
    int soma = 0;
    // Multiplica os 9 primeiros dígitos por pesos decrescentes (10 a 2)
    for (int i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * (10 - i); // (cpf[i] - '0') converte char '5' para int 5
    }
    
    int primeiroDigito = 11 - (soma % 11);
    if (primeiroDigito >= 10) primeiroDigito = 0; // Se resto for 0 ou 1, digito é 0

    // Validação do Primeiro Dígito
    if (primeiroDigito != (cpf[9] - '0')) {
        // [Exceção] O dígito calculado não bate com o digitado
        throw std::invalid_argument("CPF invalido: Digito verificador incorreto.");
    }

    // Cálculo Matemático (Segundo Dígito Verificador)
    soma = 0;
    // Multiplica os 10 primeiros dígitos (incluindo o 1º verificador) por pesos (11 a 2)
    for (int i = 0; i < 10; i++) {
        soma += (cpf[i] - '0') * (11 - i);
    }
    
    int segundoDigito = 11 - (soma % 11);
    if (segundoDigito >= 10) segundoDigito = 0;

    // Validação do Segundo Dígito
    if (segundoDigito != (cpf[10] - '0')) {
        // [Exceção]
        throw std::invalid_argument("CPF invalido: Digito verificador incorreto.");
    }
    
    // Se chegou até aqui sem lançar 'throw', o CPF é válido.
}

// ==================================================================================
// VALIDAÇÃO DE CNPJ
// ----------------------------------------------------------------------------------
// Segue lógica similar ao CPF, mas com pesos diferentes e tamanho 14.
// ==================================================================================
void Validacao::validarCNPJ(std::string cnpj) {
    cnpj = removerCaracteresNaoNumericos(cnpj);
    
    if (cnpj.length() != 14) {
        throw std::invalid_argument("CNPJ invalido: Deve conter 14 digitos.");
    }

    // Pesos específicos para o algoritmo de CNPJ
    int pesos1[12] = {5,4,3,2,9,8,7,6,5,4,3,2};
    int soma = 0;
    
    // Cálculo do 1º Dígito
    for (int i = 0; i < 12; i++) {
        soma += (cnpj[i] - '0') * pesos1[i];
    }
    int primeiroDigito = soma % 11;
    primeiroDigito = (primeiroDigito < 2) ? 0 : 11 - primeiroDigito;

    if (primeiroDigito != (cnpj[12] - '0')) {
        throw std::invalid_argument("CNPJ invalido: Digito verificador incorreto.");
    }

    // Cálculo do 2º Dígito
    int pesos2[13] = {6,5,4,3,2,9,8,7,6,5,4,3,2};
    soma = 0;
    for (int i = 0; i < 13; i++) {
        soma += (cnpj[i] - '0') * pesos2[i];
    }
    int segundoDigito = soma % 11;
    segundoDigito = (segundoDigito < 2) ? 0 : 11 - segundoDigito;

    if (segundoDigito != (cnpj[13] - '0')) {
        throw std::invalid_argument("CNPJ invalido: Digito verificador incorreto.");
    }
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