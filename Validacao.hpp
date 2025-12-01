#ifndef VALIDACAO_HPP 
#define VALIDACAO_HPP 

#include <string>     
#include <stdexcept> 

// ==================================================================================
// CLASSE VALIDACAO
// ----------------------------------------------------------------------------------
// Esta classe funciona como uma "Classe Utilitária". Ela não foi feita para ser
// instanciada (não criamos objetos 'Validacao v;'). Em vez disso, ela agrupa
// funções de verificação relacionadas.
// ==================================================================================
class Validacao {
public:
    // ==============================================================================
    // MÉTODO ESTÁTICO
    // ------------------------------------------------------------------------------
    // A palavra-chave 'static' permite que chamemos esta função sem criar um objeto.
    // Uso: Validacao::validarCPF("...");
    //
    // Observe que o retorno é VOID.
    // Em C++ moderno, quando uma função de validação não retorna 'bool' (true/false),
    // geralmente significa que ela funciona na base da confiança:
    // - Se der certo: A função termina silenciosamente.
    // - Se der errado: Ela lança uma EXCEÇÃO (throw) interrompendo o fluxo.
    // ==============================================================================
    static void validarCPF(std::string cpf);

    // Valida o CNPJ (algoritmo de módulo 11).
    // Lança std::invalid_argument se o formato ou dígitos verificadores estiverem errados.
    static void validarCNPJ(std::string cnpj);
    
    // Valida se a opção numérica do menu é válida (1, 2 ou 3).
    // Impede que o usuário digite "5" para um material que não existe.
    static void validarTipoMaterial(int tipo);
    
    // Valida se o endereço possui tamanho mínimo e contém letras.
    // Evita cadastros "sujos" ou vazios.
    static void validarEndereco(std::string endereco);

    // ==============================================================================
    // FUNÇÃO AUXILIAR 
    // ==============================================================================
    static std::string removerCaracteresNaoNumericos(std::string str);
};

#endif