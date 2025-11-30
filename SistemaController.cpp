#include "SistemaController.hpp"
#include <iostream>
#include <fstream>

void SistemaController::executar() {
    menuPrincipal();
}

void SistemaController::menuPrincipal() {
    int tipoUsuario;
    
    do {
        std::cout << "\n=== SISTEMA DE RECICLAGEM - LOGIN ===\n";
        std::cout << "1. Administrador do Sistema\n";
        std::cout << "2. Catador\n";
        std::cout << "3. Colaborador\n";
        std::cout << "4. Cooperativa\n";
        std::cout << "0. Sair\n";
        
        tipoUsuario = InputHandler::getInt("Selecione seu tipo de usuário: ");

        switch (tipoUsuario) {
            case 1:
                menuAdministrador();
                break;
            case 2:
                menuCatador();
                break;
            case 3:
                menuColaborador();
                break;
            case 4:
                menuCooperativa();
                break;
            case 0:
                std::cout << "Sistema encerrado. Até logo!\n";
                break;
            default:
                std::cout << "Opção inválida! Digite 0-4.\n";
        }
    } while (tipoUsuario != 0);
}

void SistemaController::menuAdministrador() {
    Administrador admin;
    int op;
    
    do {
        std::cout << "\n=== PAINEL ADMINISTRADOR ===\n";
        std::cout << "1. Acessar sistema de registro\n";
        std::cout << "2. Visualizar colaboradores\n";
        std::cout << "3. Visualizar cooperativas\n";
        std::cout << "4. Visualizar catadores\n";
        std::cout << "5. Relatório total de material\n";
        std::cout << "0. Voltar\n";
        
        op = InputHandler::getInt("Opção: ");

        switch (op) {
            case 1:
                admin.acessarSistemaRegistro();
                break;
            case 2:
                admin.visualizarColaboradores();
                break;
            case 3:
                admin.visualizarCooperativas();
                break;
            case 4:
                admin.visualizarCatadores();
                break;
            case 5:
                admin.relatorioTotalMaterial();
                break;
            case 0:
                std::cout << "Voltando ao menu principal...\n";
                break;
            default:
                std::cout << "Opção inválida! Digite 0-5.\n";
        }
    } while (op != 0);
}

void SistemaController::menuCatador() {
    std::string cpf = InputHandler::getString("CPF: ");

    if (!catadorExiste(cpf)) {
        std::string resposta = InputHandler::getString("Catador não encontrado. Deseja cadastrar? (s/n): ");
        
        if (resposta == "s" || resposta == "S") {
            std::string nome = InputHandler::getString("Nome: ");
            std::string end = InputHandler::getString("Endereço: ");
            float peso = InputHandler::getFloat("Peso do material (kg): ");
            int tipo = InputHandler::getInt("Tipo (1-Plástico 2-Papel 3-Metal): ");

            Material mat(peso, tipo);
            Catador cat(nome, end, cpf, &mat);
            cat.cadastro(nome, end, cpf, &mat);
            std::cout << "Catador cadastrado com sucesso!\n";
        } else {
            return;
        }
    }

    // Menu do catador logado
    Catador cat("", "", cpf, nullptr);
    int op;
    do {
        std::cout << "\n=== PAINEL CATADOR ===\n";
        std::cout << "1. Visualizar cooperativas\n";
        std::cout << "2. Visualizar saldo\n";
        std::cout << "3. Modificar saldo\n";
        std::cout << "4. Visualizar colaboradores\n";
        std::cout << "0. Voltar\n";
        
        op = InputHandler::getInt("Opção: ");

        switch (op) {
            case 1:
                cat.visualizarCooperativas();
                break;
            case 2:
                std::cout << "Saldo atual: R$ " << cat.getSaldo() << std::endl;
                break;
            case 3:
                {
                    float novoSaldo = InputHandler::getFloat("Novo saldo: R$ ");
                    cat.setSaldo(novoSaldo);
                    std::cout << "Saldo atualizado!\n";
                }
                break;
            case 4:
                cat.visualizarColaboradores();
                break;
            case 0:
                std::cout << "Voltando...\n";
                break;
            default:
                std::cout << "Opção inválida! Digite 0-4.\n";
        }
    } while (op != 0);
}

void SistemaController::menuColaborador() {
    std::string cpf = InputHandler::getString("CPF: ");

    if (!colaboradorExiste(cpf)) {
        std::string resposta = InputHandler::getString("Colaborador não encontrado. Deseja cadastrar? (s/n): ");
        
        if (resposta == "s" || resposta == "S") {
            std::string nome = InputHandler::getString("Nome: ");
            std::string end = InputHandler::getString("Endereço: ");
            float peso = InputHandler::getFloat("Peso do material (kg): ");
            int tipo = InputHandler::getInt("Tipo (1-Plástico 2-Papel 3-Metal): ");

            Material mat(peso, tipo);
            Colaborador col(nome, end, cpf, &mat);
            col.cadastro(nome, end, cpf, &mat);
            col.receberPontos(100);
            std::cout << "Colaborador cadastrado com sucesso!\n";
        } else {
            return;
        }
    }

    // Menu do colaborador logado
    Colaborador col("", "", cpf, nullptr);
    int op;
    do {
        std::cout << "\n=== PAINEL COLABORADOR ===\n";
        std::cout << "1. Visualizar pontos\n";
        std::cout << "2. Modificar material doado\n";
        std::cout << "0. Voltar\n";
        
        op = InputHandler::getInt("Opção: ");

        switch (op) {
            case 1:
                std::cout << "Pontos atuais: " << col.getPontos() << std::endl;
                break;
            case 2:
                {
                    float novoPeso = InputHandler::getFloat("Novo peso (kg): ");
                    int novoTipo = InputHandler::getInt("Novo tipo (1-Plástico 2-Papel 3-Metal): ");
                    
                    Material* novoMat = new Material(novoPeso, novoTipo);
                    col.setMaterial(novoMat);
                    std::cout << "Material atualizado!\n";
                }
                break;
            case 0:
                std::cout << "Voltando...\n";
                break;
            default:
                std::cout << "Opção inválida! Digite 0-2.\n";
        }
    } while (op != 0);
}

void SistemaController::menuCooperativa() {
    std::string cnpj = InputHandler::getString("CNPJ: ");

    if (!cooperativaExiste(cnpj)) {
        std::string resposta = InputHandler::getString("Cooperativa não encontrada. Deseja cadastrar? (s/n): ");
        
        if (resposta == "s" || resposta == "S") {
            std::string endereco = InputHandler::getString("Endereço: ");
            float preco = InputHandler::getFloat("Preço base por kg: R$ ");

            Cooperativas coop;
            coop.setCnpj(cnpj);
            coop.cadastro(preco, endereco, cnpj, nullptr);
            std::cout << "Cooperativa cadastrada com sucesso!\n";
        } else {
            return;
        }
    }

    // Menu da cooperativa logada
    Cooperativas coop;
    coop.setCnpj(cnpj);
    int op;
    do {
        std::cout << "\n=== PAINEL COOPERATIVA ===\n";
        std::cout << "1. Relatório de material comprado\n";
        std::cout << "2. Modificar quantidade comprada\n";
        std::cout << "0. Voltar\n";
        
        op = InputHandler::getInt("Opção: ");

        switch (op) {
            case 1:
                coop.relatorioMaterialComprado();
                break;
            case 2:
                {
                    std::string nomeCatador = InputHandler::getString("Nome do catador: ");
                    float peso = InputHandler::getFloat("Peso comprado (kg): ");
                    float precoKg = InputHandler::getFloat("Preço por kg: R$ ");
                    
                    Material m(0, 1);
                    Catador cat(nomeCatador, coop.getEndereco(), "00000000000", &m);
                    coop.comprarMaterial(cat, peso, precoKg);
                    coop.registrarCompra(nomeCatador, peso, precoKg);
                }
                break;
            case 0:
                std::cout << "Voltando...\n";
                break;
            default:
                std::cout << "Opção inválida! Digite 0-2.\n";
        }
    } while (op != 0);
}

bool SistemaController::catadorExiste(const std::string& cpf) {
    std::ifstream arquivo("cadastro_catador.txt");
    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.find("CPF: " + cpf) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool SistemaController::colaboradorExiste(const std::string& cpf) {
    std::ifstream arquivo("cadastro_colaborador.txt");
    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.find("CPF: " + cpf) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool SistemaController::cooperativaExiste(const std::string& cnpj) {
    std::ifstream arquivo("cadastro_cooperativa.txt");
    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.find(cnpj) != std::string::npos) {
            return true;
        }
    }
    return false;
}