#ifndef SISTEMACONTROLLER_HPP
#define SISTEMACONTROLLER_HPP

#include <string>

class SistemaController {
private:
    // Funções de verificação existentes
    bool catadorExiste(const std::string& cpf);
    bool colaboradorExiste(const std::string& cpf);
    bool cooperativaExiste(const std::string& cnpj);

    // NOVAS FUNÇÕES: Loop que obriga digitar um novo se já existir
    std::string obterCPFUnicoCatador();
    std::string obterCPFUnicoColaborador();
    std::string obterCNPJUnico();

public:
    void executar();
    void menuPrincipal();
    void menuAdministrador();
    
    // Estes menus foram alterados para ter opção Login vs Cadastro
    void menuCatador();
    void menuColaborador();
    void menuCooperativa();
};

#endif