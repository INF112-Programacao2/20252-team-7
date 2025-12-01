#include "SistemaController.hpp"
#include "material.hpp"
#include "colaborador.hpp"
#include "Catador.hpp"
#include "cooperativas.hpp"
#include "administrador.hpp"
#include "InputHandler.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept> // Necessário para tratamento de erros (runtime_error)

void SistemaController::executar() {
    menuPrincipal();
}

void SistemaController::menuPrincipal() {
    int tipoUsuario;
    do {
        std::cout << "\n=== SISTEMA DE RECICLAGEM ===\n";
        std::cout << "1. Administrador\n";
        std::cout << "2. Catador\n";
        std::cout << "3. Colaborador\n";
        std::cout << "4. Cooperativa\n";
        std::cout << "0. Sair\n";
        
        tipoUsuario = InputHandler::getInt("Selecione: ");

        switch (tipoUsuario) {
            case 1: menuAdministrador(); break;
            case 2: menuCatador(); break;
            case 3: menuColaborador(); break;
            case 4: menuCooperativa(); break;
            case 0: std::cout << "Encerrando o sistema...\n"; break;
            default: std::cout << "Opcao invalida.\n";
        }
    } while (tipoUsuario != 0);
}

// === FUNÇÕES AUXILIARES DE UNICIDADE (Validam se já existe no banco) ===

std::string SistemaController::obterCPFUnicoCatador() {
    while (true) {
        try {
            std::string cpf = InputHandler::getCPF("Digite o CPF para cadastro: ");
            if (catadorExiste(cpf)) {
                throw std::runtime_error("Erro: Este CPF ja esta cadastrado como Catador!");
            }
            return cpf;
        } catch (const std::runtime_error& e) {
            std::cout << ">> " << e.what() << "\n>> Por favor, digite outro CPF.\n";
        }
    }
}

std::string SistemaController::obterCPFUnicoColaborador() {
    while (true) {
        try {
            std::string cpf = InputHandler::getCPF("Digite o CPF para cadastro: ");
            if (colaboradorExiste(cpf)) {
                throw std::runtime_error("Erro: Este CPF ja esta cadastrado como Colaborador!");
            }
            return cpf;
        } catch (const std::runtime_error& e) {
            std::cout << ">> " << e.what() << "\n>> Por favor, digite outro CPF.\n";
        }
    }
}

std::string SistemaController::obterCNPJUnico() {
    while (true) {
        try {
            std::string cnpj = InputHandler::getCNPJ("Digite o CNPJ para cadastro: ");
            if (cooperativaExiste(cnpj)) {
                throw std::runtime_error("Erro: Este CNPJ ja esta cadastrado!");
            }
            return cnpj;
        } catch (const std::runtime_error& e) {
            std::cout << ">> " << e.what() << "\n>> Por favor, digite outro CNPJ.\n";
        }
    }
}

// === MENUS ESPECÍFICOS ===

void SistemaController::menuCatador() {
    int opInicial;
    do {
        std::cout << "\n--- MENU CATADOR ---\n";
        std::cout << "1. Entrar (Login)\n";
        std::cout << "2. Cadastrar Novo Catador\n";
        std::cout << "0. Voltar\n";
        opInicial = InputHandler::getInt("Opcao: ");

        std::string cpfLogado = "";

        if (opInicial == 1) {
            std::string cpf = InputHandler::getCPF("CPF: ");
            if (catadorExiste(cpf)) {
                std::cout << "Login realizado com sucesso!\n";
                cpfLogado = cpf;
            } else {
                std::cout << ">> CPF nao encontrado no sistema.\n";
            }
        } 
        else if (opInicial == 2) {
            std::cout << "--- NOVO CADASTRO DE CATADOR ---\n";
            
            // Garante CPF único
            std::string cpf = obterCPFUnicoCatador(); 
            std::string nome = InputHandler::getString("Nome Completo: ");
            std::string end = InputHandler::getEndereco("Endereco: ");
            
            // ATUALIZADO: Passa nullptr pois não tem material inicial
            Catador cat(nome, end, cpf, nullptr);
            cat.cadastro(nome, end, cpf, nullptr);
            
            cpfLogado = cpf;
        }

        // Área Logada
        if (!cpfLogado.empty()) {
            // Objeto temporário. Nota: O saldo na memória iniciará como 0 aqui.
            // Para ver o saldo real atualizado, o usuário deve relogar ou implementarmos um 'carregarDados'.
            // Porém, a função de adicionar dinheiro funciona direto no arquivo, então é seguro.
            Catador cat("", "", cpfLogado, nullptr);
            int op;
            do {
                std::cout << "\n=== AREA DO CATADOR (" << cpfLogado << ") ===\n";
                std::cout << "1. Ver Cooperativas Disponiveis\n";
                std::cout << "2. Ver Meu Saldo (Sessao Atual)\n";
                std::cout << "0. Sair (Logout)\n";
                
                op = InputHandler::getInt("Opcao: ");
                
                if(op == 1) cat.visualizarCooperativas();
                else if(op == 2) std::cout << "Saldo: R$ " << cat.getSaldo() << "\n";
                
            } while (op != 0);
        }

    } while (opInicial != 0);
}

void SistemaController::menuColaborador() {
    int opInicial;
    do {
        std::cout << "\n--- MENU COLABORADOR ---\n";
        std::cout << "1. Entrar (Login)\n";
        std::cout << "2. Cadastrar Novo Colaborador\n";
        std::cout << "0. Voltar\n";
        opInicial = InputHandler::getInt("Opcao: ");

        std::string cpfLogado = "";

        if (opInicial == 1) {
            std::string cpf = InputHandler::getString("CPF: ");
            if (colaboradorExiste(cpf)) {
                std::cout << "Login realizado!\n";
                cpfLogado = cpf;
            } else {
                std::cout << ">> CPF nao encontrado.\n";
            }
        }
        else if (opInicial == 2) {
            std::cout << "--- NOVO CADASTRO DE COLABORADOR ---\n";
            std::string cpf = obterCPFUnicoColaborador();
            std::string nome = InputHandler::getString("Nome: ");
            std::string end = InputHandler::getEndereco("Endereco: ");
            
            // ATUALIZADO: Cadastro sem material inicial
            Colaborador col(nome, end, cpf, nullptr);
            col.cadastro(nome, end, cpf, nullptr);
            
            // Dá o bônus de boas-vindas
            col.receberPontos(100); 
            cpfLogado = cpf;
        }

        // Área Logada
        if (!cpfLogado.empty()) {
            Colaborador col("", "", cpfLogado, nullptr);
            col.carregarPontos(); // Carrega pontos do arquivo para a memória
            int op;
            do {
                std::cout << "\n=== AREA DO COLABORADOR (" << cpfLogado << ") ===\n";
                std::cout << "1. Ver Pontos\n";
                std::cout << "2. Fazer Doacao (Entregar Material)\n";
                std::cout << "0. Sair\n";
                
                op = InputHandler::getInt("Opcao: ");
                
                if(op == 1) std::cout << "Pontos Totais: " << col.getPontos() << "\n";
                else if(op == 2) {
                    std::cout << "\n--- NOVA DOACAO ---\n";
                    int t = InputHandler::getTipoMaterial("Material: ");
                    float p = InputHandler::getFloat("Peso (kg): ");
                    
                    Material* m = new Material(p, t);
                    col.realizarDoacao(m);
                    delete m;
                }
            } while (op != 0);
        }
    } while (opInicial != 0);
}

void SistemaController::menuCooperativa() {
    int opInicial;
    do {
        std::cout << "\n--- MENU COOPERATIVA ---\n";
        std::cout << "1. Entrar (Login)\n";
        std::cout << "2. Cadastrar Nova Cooperativa\n";
        std::cout << "0. Voltar\n";
        opInicial = InputHandler::getInt("Opcao: ");

        std::string cnpjLogado = "";

        if (opInicial == 1) {
            std::string cnpj = InputHandler::getCNPJ("CNPJ: ");
            if (cooperativaExiste(cnpj)) {
                std::cout << "Acesso liberado!\n";
                cnpjLogado = cnpj;
            } else {
                std::cout << ">> CNPJ nao encontrado.\n";
            }
        }
        else if (opInicial == 2) {
            std::cout << "--- NOVO CADASTRO ---\n";
            std::string cnpj = obterCNPJUnico();
            std::string end = InputHandler::getEndereco("Endereco Sede: ");
            
            std::cout << "--- DEFINICAO DE PRECOS (R$/kg) ---\n";
            float p1 = InputHandler::getFloat("Plastico: ");
            float p2 = InputHandler::getFloat("Papel: ");
            float p3 = InputHandler::getFloat("Metal: ");
            
            Cooperativas coop;
            coop.cadastro(p1, p2, p3, end, cnpj, nullptr);
            cnpjLogado = cnpj;
        }

        // Área Logada
        if (!cnpjLogado.empty()) {
            Cooperativas coop;
            coop.setCnpj(cnpjLogado);
            coop.setEndereco("Sede"); 
            // Em um sistema real, leríamos os preços do arquivo aqui.
            // Para simulação, definimos preços fixos ou pedimos confirmação.
            coop.setPrecos(0.5, 0.2, 5.0); 

            int op;
            do {
                std::cout << "\n=== AREA COOPERATIVA (" << cnpjLogado << ") ===\n";
                std::cout << "1. Historico de Transacoes\n";
                std::cout << "2. Registrar Compra (Pagar Catador)\n";
                std::cout << "3. Relatorio Estatistico\n";
                std::cout << "0. Sair\n";
                
                op = InputHandler::getInt("Opcao: ");
                
                if(op == 1) coop.relatorioMaterialComprado();
                else if(op == 2) {
                    std::cout << "\n--- REGISTRAR COMPRA ---\n";
                    
                    // ATUALIZADO: Pede CPF ao invés de Nome
                    std::string cpfCatador = InputHandler::getCPF("CPF do Catador: ");
                    
                    if (!catadorExiste(cpfCatador)) {
                        std::cout << ">> Erro: Catador nao encontrado! Cadastre-o primeiro.\n";
                    } else {
                        // Fluxo direto: Material -> Peso -> Pagamento
                        int t = InputHandler::getTipoMaterial("Material recebido: ");
                        float peso = InputHandler::getFloat("Peso (kg): ");
                        
                        // Define preço automaticamente
                        float precoKg = 0;
                        if(t == 1) precoKg = coop.getPrecoPlastico();
                        else if(t == 2) precoKg = coop.getPrecoPapel();
                        else if(t == 3) precoKg = coop.getPrecoMetal();
                        
                        float total = peso * precoKg;
                        
                        // Objeto temporário para acessar o arquivo do catador
                        // Nome e Endereço vazios pois só precisamos do CPF para achar a linha no TXT
                        Catador c("", "N/A", cpfCatador, nullptr);
                        
                        // 1. Atualiza o saldo no arquivo do Catador
                        c.adicionarSaldoAoArquivo(total);
                        
                        // 2. Registra na Cooperativa (Usando CPF no histórico)
                        std::string nomeMat = (t==1) ? "Plastico" : (t==2) ? "Papel" : "Metal";
                        coop.registrarCompra(cpfCatador, peso, total, nomeMat);
                        
                        std::cout << ">> SUCESSO! R$ " << total << " creditados para o CPF " << cpfCatador << ".\n";
                    }
                }
                else if(op == 3) coop.gerarRelatorioEstatistico();
                
            } while (op != 0);
        }
    } while (opInicial != 0);
}

void SistemaController::menuAdministrador() {
    Administrador admin;
    int op;
    do {
        std::cout << "\n=== PAINEL ADMIN ===\n";
        std::cout << "1. Visualizar Colaboradores\n";
        std::cout << "2. Visualizar Cooperativas\n";
        std::cout << "3. Visualizar Catadores\n";
        std::cout << "4. Ranking de Pontos\n";
        std::cout << "5. Relatorio Global (Total Material)\n"; // Opção Nova
        std::cout << "0. Voltar\n";
        
        op = InputHandler::getInt("Opcao: ");
        
        if(op==1) admin.visualizarColaboradores();
        else if(op==2) admin.visualizarCooperativas();
        else if(op==3) admin.visualizarCatadores();
        else if(op==4) admin.gerarRanking();
        else if(op==5) admin.relatorioTotalMaterial();
        else if(op!=0) std::cout << "Opcao invalida.\n";
        
    } while(op!=0);
}

// Funções de verificação de arquivo
bool SistemaController::catadorExiste(const std::string& cpf) {
    std::ifstream f("cadastro_catador.txt");
    std::string l; if(!f.is_open()) return false;
    while(std::getline(f, l)) if(l.find(cpf) != std::string::npos) return true;
    return false;
}
bool SistemaController::colaboradorExiste(const std::string& cpf) {
    std::ifstream f("cadastro_colaborador.txt");
    std::string l; if(!f.is_open()) return false;
    while(std::getline(f, l)) if(l.find(cpf) != std::string::npos) return true;
    return false;
}
bool SistemaController::cooperativaExiste(const std::string& cnpj) {
    std::ifstream f("cadastro_cooperativa.txt");
    std::string l; if(!f.is_open()) return false;
    while(std::getline(f, l)) if(l.find(cnpj) != std::string::npos) return true;
    return false;
}