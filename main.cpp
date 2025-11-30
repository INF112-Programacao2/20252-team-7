#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "material.hpp"
#include "colaborador.hpp"
#include "Catador.hpp"
#include "cooperativas.hpp"
#include "administrador.hpp"

void menuAdministrador();
void menuCatador();
void menuColaborador();
void menuCooperativa();
bool catadorExiste(const std::string& cpf);
bool colaboradorExiste(const std::string& cpf);
bool cooperativaExiste(const std::string& cnpj);

int main() {
    int tipoUsuario;
    
    do {
        std::cout << "\n=== SISTEMA DE RECICLAGEM - LOGIN ===\n";
        std::cout << "1. Administrador do Sistema\n";
        std::cout << "2. Catador\n";
        std::cout << "3. Colaborador\n";
        std::cout << "4. Cooperativa\n";
        std::cout << "0. Sair\n";
        std::cout << "Selecione seu tipo de usuário: ";
        std::cin >> tipoUsuario;
        std::cin.ignore();

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
                std::cout << "Opção inválida!\n";
        }
    } while (tipoUsuario != 0);

    return 0;
}

void menuAdministrador() {
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
        std::cout << "Opção: ";
        std::cin >> op;
        std::cin.ignore();

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
                std::cout << "Opção inválida!\n";
        }
    } while (op != 0);
}

void menuCatador() {
    std::string cpf;
    std::cout << "\n=== ACESSO CATADOR ===\n";
    std::cout << "CPF: ";
    std::getline(std::cin, cpf);

    if (!catadorExiste(cpf)) {
        char cadastrar;
        std::cout << "Catador não encontrado. Deseja cadastrar? (s/n): ";
        std::cin >> cadastrar;
        std::cin.ignore();
        
        if (cadastrar == 's' || cadastrar == 'S') {
            std::string nome, end;
            float peso; int tipo;
            
            std::cout << "Nome: "; std::getline(std::cin, nome);
            std::cout << "Endereço: "; std::getline(std::cin, end);
            std::cout << "Peso do material (kg): "; std::cin >> peso;
            std::cout << "Tipo (1-Plástico 2-Papel 3-Metal): "; std::cin >> tipo;

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
        std::cout << "Opção: ";
        std::cin >> op;
        std::cin.ignore();

        switch (op) {
            case 1:
                cat.visualizarCooperativas();
                break;
            case 2:
                std::cout << "Saldo atual: R$ " << cat.getSaldo() << std::endl;
                break;
            case 3:
                {
                    float novoSaldo;
                    std::cout << "Novo saldo: R$ ";
                    std::cin >> novoSaldo;
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
                std::cout << "Opção inválida!\n";
        }
    } while (op != 0);
}

void menuColaborador() {
    std::string cpf;
    std::cout << "\n=== ACESSO COLABORADOR ===\n";
    std::cout << "CPF: ";
    std::getline(std::cin, cpf);

    if (!colaboradorExiste(cpf)) {
        char cadastrar;
        std::cout << "Colaborador não encontrado. Deseja cadastrar? (s/n): ";
        std::cin >> cadastrar;
        std::cin.ignore();
        
        if (cadastrar == 's' || cadastrar == 'S') {
            std::string nome, end;
            float peso; int tipo;
            
            std::cout << "Nome: "; std::getline(std::cin, nome);
            std::cout << "Endereço: "; std::getline(std::cin, end);
            std::cout << "Peso do material (kg): "; std::cin >> peso;
            std::cout << "Tipo (1-Plástico 2-Papel 3-Metal): "; std::cin >> tipo;

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
        std::cout << "Opção: ";
        std::cin >> op;
        std::cin.ignore();

        switch (op) {
            case 1:
                std::cout << "Pontos atuais: " << col.getPontos() << std::endl;
                break;
            case 2:
                {
                    float novoPeso; int novoTipo;
                    std::cout << "Novo peso (kg): ";
                    std::cin >> novoPeso;
                    std::cout << "Novo tipo (1-Plástico 2-Papel 3-Metal): ";
                    std::cin >> novoTipo;
                    
                    Material* novoMat = new Material(novoPeso, novoTipo);
                    col.setMaterial(novoMat);
                    std::cout << "Material atualizado!\n";
                }
                break;
            case 0:
                std::cout << "Voltando...\n";
                break;
            default:
                std::cout << "Opção inválida!\n";
        }
    } while (op != 0);
}

void menuCooperativa() {
    std::string cnpj;
    std::cout << "\n=== ACESSO COOPERATIVA ===\n";
    std::cout << "CNPJ: ";
    std::getline(std::cin, cnpj);

    if (!cooperativaExiste(cnpj)) {
        char cadastrar;
        std::cout << "Cooperativa não encontrada. Deseja cadastrar? (s/n): ";
        std::cin >> cadastrar;
        std::cin.ignore();
        
        if (cadastrar == 's' || cadastrar == 'S') {
            std::string endereco;
            float preco;
            
            std::cout << "Endereço: "; std::getline(std::cin, endereco);
            std::cout << "Preço base por kg: R$ "; std::cin >> preco;

            Cooperativas coop;
            coop.setCnpj(cnpj); // Definir o CNPJ
            coop.cadastro(preco, endereco, cnpj, nullptr);
            std::cout << "Cooperativa cadastrada com sucesso!\n";
        } else {
            return;
        }
    }

    // Menu da cooperativa logada
    Cooperativas coop;
    coop.setCnpj(cnpj); // Definir CNPJ para a sessão
    int op;
    do {
        std::cout << "\n=== PAINEL COOPERATIVA ===\n";
        std::cout << "1. Relatório de material comprado\n";
        std::cout << "2. Modificar quantidade comprada\n";
        std::cout << "0. Voltar\n";
        std::cout << "Opção: ";
        std::cin >> op;
        std::cin.ignore();

        switch (op) {
            case 1:
                coop.relatorioMaterialComprado();
                break;
            case 2:
                {
                    std::string nomeCatador;
                    float peso, precoKg;
                    std::cout << "Nome do catador: "; std::getline(std::cin, nomeCatador);
                    std::cout << "Peso comprado (kg): "; std::cin >> peso;
                    std::cout << "Preço por kg: R$ "; std::cin >> precoKg;
                    
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
                std::cout << "Opção inválida!\n";
        }
    } while (op != 0);
}

bool catadorExiste(const std::string& cpf) {
    std::ifstream arquivo("cadastro_catador.txt");
    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.find("CPF: " + cpf) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool colaboradorExiste(const std::string& cpf) {
    std::ifstream arquivo("cadastro_colaborador.txt");
    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.find("CPF: " + cpf) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool cooperativaExiste(const std::string& cnpj) {
    std::ifstream arquivo("cadastro_cooperativa.txt");
    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.find(cnpj) != std::string::npos) {
            return true;
        }
    }
    return false;
}