#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <string>   
#include <iostream> 

// ==================================================================================
// CLASSE INPUTHANDLER (Manipulador de Entradas)
// ----------------------------------------------------------------------------------
// Esta classe é uma "caixa de ferramentas". Ela não mantém estado (não tem variáveis
// como 'nome' ou 'saldo'). A única função dela é fornecer métodos seguros para ler
// dados do teclado.
//
// Vantagem da Abstração:
// O resto do sistema (SistemaController) não precisa saber limpar o buffer do teclado
// (cin.ignore) ou checar erros de fluxo (cin.fail). Ele apenas pede "me dê um inteiro"
// e esta classe resolve os problemas técnicos "sujos" internamente.
// ==================================================================================
class InputHandler {
public:
    // ==============================================================================
    // MÉTODOS ESTÁTICOS 
    // ==============================================================================

    // [Tratamento de Erro Interno]
    // Lê um número inteiro. Se o usuário digitar letras, este método captura o erro
    // do cin (failbit), limpa o buffer e pede novamente num loop, sem travar o programa.
    static int getInt(const std::string& prompt);

    // Lê um número decimal (float). Aplica a mesma proteção contra caracteres inválidos.
    static float getFloat(const std::string& prompt);

    // Lê uma linha de texto completa (incluindo espaços).
    // Resolve o problema clássico do C++ onde o 'cin >>' deixa o 'Enter' no buffer.
    static std::string getString(const std::string& prompt);
    
    // ==============================================================================
    // MÉTODOS DE INPUT COM VALIDAÇÃO 
    // ------------------------------------------------------------------------------
    // Estes métodos não apenas leem, mas garantem que o dado faz sentido para o sistema.
    // Eles trabalham em conjunto com a classe 'Validacao'.
    //
    // [Exceção] O contrato desses métodos é:
    // Eu prometo que só vou retornar para o programa quando o usuário digitar
    // um valor válido. Se ele errar, eu trato a exceção (catch) aqui dentro
    // e peço para ele digitar de novo.
    // ==============================================================================
    
    // Garante retorno de apenas números (remove pontos/traços) e valida o algoritmo matemático.
    static std::string getCPF(const std::string& prompt);

    // Mesma lógica do CPF, mas para 14 dígitos e pesos diferentes.
    static std::string getCNPJ(const std::string& prompt);

    // Mostra o menu de materiais (1-Plastico, 2-Papel, 3-Metal) e garante que o
    // retorno seja estritamente 1, 2 ou 3.
    static int getTipoMaterial(const std::string& prompt);
    
    // Exige que o endereço tenha tamanho mínimo e contenha letras.
    static std::string getEndereco(const std::string& prompt);
};

#endif 