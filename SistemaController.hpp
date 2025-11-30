#ifndef SISTEMACONTROLLER_HPP
#define SISTEMACONTROLLER_HPP

#include "material.hpp"
#include "colaborador.hpp"
#include "Catador.hpp"
#include "cooperativas.hpp"
#include "administrador.hpp"
#include "InputHandler.hpp"
#include <string>

class SistemaController {
private:
    bool catadorExiste(const std::string& cpf);
    bool colaboradorExiste(const std::string& cpf);
    bool cooperativaExiste(const std::string& cnpj);

public:
    void executar();
    void menuPrincipal();
    void menuAdministrador();
    void menuCatador();
    void menuColaborador();
    void menuCooperativa();
};

#endif