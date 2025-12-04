#ifndef SISTEMACONTROLLER_HPP
#define SISTEMACONTROLLER_HPP

#include <string>

// ==================================================================================
// CLASSE SISTEMACONTROLLER
// ----------------------------------------------------------------------------------
// Esta classe atua como o "Controller" (Controlador). Ela não representa um objeto
// do mundo real (como uma Pessoa), mas sim o FLUXO do programa.
// Responsabilidades:
// 1. Gerenciar os Menus.
// 2. Receber input do usuário (via InputHandler).
// 3. Instanciar e comandar os Objetos (Catador, Colaborador, etc).
// ==================================================================================
class SistemaController {

// ==================================================================================
// [Encapsulamento]
// ==================================================================================
private:
    // Funções booleanas que abrem os arquivos .txt para verificar existência.
    // Retornam true se o dado já estiver cadastrado.
    bool catadorExiste(const std::string& cpf);
    bool colaboradorExiste(const std::string& cpf);
    bool cooperativaExiste(const std::string& cnpj);

    // Estas funções implementam a regra de "Unicidade".
    // Elas contêm loops (while) que forçam o usuário a tentar digitar um CPF/CNPJ
    // até encontrar um que NÃO exista no banco de dados.
    // Elas usam try/catch internamente para tratar a tentativa de cadastro duplicado.
    std::string obterCPFUnicoCatador();
    std::string obterCPFUnicoColaborador();
    std::string obterCNPJUnico();

// ==================================================================================
// [Interface da Classe]
// Estes são os botões que o mundo exterior (a função main) pode apertar.
// ==================================================================================
public:
    // Função principal que inicia o loop do programa.
    // É a única coisa que a main.cpp chama.
    void executar();

    // [Modularização de Menus]
    // Cada função abaixo cuida de toda a interação de um perfil específico.
    // Dentro delas, ocorre a instanciação de objetos (Alocação de Memória) e
    // a chamada de métodos de negócio (ex: catador.recolherMaterial()).
    void menuPrincipal();      // Menu inicial (Escolha de perfil)
    void menuAdministrador();  // Painel de gestão e relatórios globais
    void menuCatador();        // Login, cadastro e saldo do catador
    void menuColaborador();    // Doação e pontuação
    void menuCooperativa();    // Compra de material e pagamento
};

#endif