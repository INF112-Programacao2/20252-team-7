#include "InputHandler.hpp"
#include "Validacao.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <limits> 

// ==================================================================================
// MÉTODOS GENÉRICOS 
// ==================================================================================

int InputHandler::getInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value; // Tenta ler um inteiro
        
        // [Stream - Verificação de Erro]
        // std::cin.fail() retorna 'true' se o usuário digitou algo que não é int (ex: "abc")
        if (std::cin.fail()) {
            // Passo 1: Limpar o estado de erro.
            // Se não fizermos isso, o cin se recusa a ler qualquer coisa nova.
            std::cin.clear(); 
            
            // Passo 2: Limpar o buffer (o lixo que o usuário digitou).
            // 'ignore' descarta caracteres até encontrar uma quebra de linha ('\n').
            // numeric_limits<...>::max() significa "ignore quantos caracteres forem necessários".
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::cout << "Entrada invalida! Digite um numero inteiro.\n";
        } else {
            // [Stream - Limpeza de Rastro]
            // Se deu certo, ainda precisamos limpar o buffer
            // Se a próxima leitura for um 'getline', ela vai ler esse 'Enter' e achar que
            // o usuário digitou uma string vazia.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            return value; // Retorna o valor limpo e seguro
        }
    }
}

float InputHandler::getFloat(const std::string& prompt) {
    float value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        // Mesma lógica de proteção do getInt
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida! Digite um numero decimal (use ponto).\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// [Stream] Leitura de Strings
// Usamos std::getline em vez de std::cin >> string.
// - cin >> string: Lê apenas até o primeiro espaço (não lê nomes compostos).
// - getline: Lê a linha inteira até o Enter.
std::string InputHandler::getString(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// ==================================================================================
// MÉTODOS ESPECÍFICOS (Integração com Validação e Exceções)
// ==================================================================================

std::string InputHandler::getCPF(const std::string& prompt, char exitSymbol) {
    std::string cpf;
    while (true) {
        // Informa ao usuário que existe a opção de cancelar com o simbolo
        std::cout << prompt << " (ou digite '" << exitSymbol << "' para cancelar): ";
        std::getline(std::cin, cpf);

        // Remove espaços nas extremidades (trim simples)
        while (!cpf.empty() && std::isspace(static_cast<unsigned char>(cpf.front()))) cpf.erase(0, 1);
        while (!cpf.empty() && std::isspace(static_cast<unsigned char>(cpf.back()))) cpf.pop_back();

        // Se o usuario digitou apenas o simbolo de saida, retorna string vazia para indicar cancelamento
        if (cpf.size() == 1 && cpf[0] == exitSymbol) {
            return std::string("");
        }

        // [Exceção - Bloco Protegido]
        try {
            // Tenta validar. Se falhar, Validacao::validarCPF lança um 'throw'.
            Validacao::validarCPF(cpf);
            // Se chegou aqui, não houve erro. Retorna o CPF limpo (apenas números).
            return Validacao::removerCaracteresNaoNumericos(cpf);
        } catch (const std::invalid_argument& e) {
            std::cerr << "ERRO: " << e.what() << "\n";
            std::cout << "Tente novamente (ex: 123.456.789-01)." << "\n";
            // O loop 'while(true)' fará o programa voltar ao início e pedir de novo.
        }
    }
}

std::string InputHandler::getCNPJ(const std::string& prompt) {
    std::string cnpj;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, cnpj);
        
        try {
            Validacao::validarCNPJ(cnpj);
            return Validacao::removerCaracteresNaoNumericos(cnpj);
        } catch (const std::invalid_argument& e) {
            std::cerr << "ERRO: " << e.what() << "\n";
            std::cout << "Tente novamente (ex: 11.222.333/0001-81).\n";
        }
    }
}

// [Reutilização de Código]
// Este método combina a segurança do 'getInt' com a validação lógica do 'Validacao'.
int InputHandler::getTipoMaterial(const std::string& prompt) {
    int tipo;
    while (true) {
        // Exibe o menu visualmente
        std::cout << "\n=== SELECIONE O TIPO DE MATERIAL ===\n";
        std::cout << "[1] Plastico\n";
        std::cout << "[2] Papel\n";
        std::cout << "[3] Metal\n";
        std::cout << "------------------------------------\n";
        
        // 1. Garante que é um número (trata letras/símbolos)
        tipo = getInt(prompt); 
        
        try {
            // 2. Garante que é um número válido (1, 2 ou 3)
            Validacao::validarTipoMaterial(tipo);
            return tipo;
        } catch (const std::invalid_argument& e) {
            std::cerr << "ERRO: " << e.what() << "\n";
            std::cout << "Tente novamente.\n";
        }
    }
}

std::string InputHandler::getEndereco(const std::string& prompt) {
    std::string endereco;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, endereco);
        
        try {
            Validacao::validarEndereco(endereco);
            return endereco; // Retorna apenas se passar na validação
        } catch (const std::invalid_argument& e) {
            std::cerr << "ERRO: " << e.what() << "\n";
            std::cout << "Por favor, digite o endereco corretamente.\n";
        }
    }
}