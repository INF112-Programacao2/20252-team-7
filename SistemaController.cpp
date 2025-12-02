#include "SistemaController.hpp"
#include "material.hpp"
#include "colaborador.hpp"
#include "Catador.hpp"
#include "cooperativas.hpp"
#include "administrador.hpp"
#include "InputHandler.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

// ==================================================================================
// MÉTODO: executar
// ----------------------------------------------------------------------------------
// Ponto de entrada da classe. A main.cpp chama apenas isso.
// Encapsula toda a lógica do sistema dentro do Controller.
// ==================================================================================
void SistemaController::executar() {
    menuPrincipal();
}

// ==================================================================================
// MENU PRINCIPAL
// Usa um loop 'do-while' para manter o programa rodando até o usuário
// escolher a opção 0 (Sair).
// ==================================================================================
void SistemaController::menuPrincipal() {
    int tipoUsuario;
    do {
        std::cout << "\n=== SISTEMA DE RECICLAGEM ===\n";
        std::cout << "1. Administrador\n";
        std::cout << "2. Catador\n";
        std::cout << "3. Colaborador\n";
        std::cout << "4. Cooperativa\n";
        std::cout << "0. Sair\n";
        
        // [InputHandler] Chama método estático para ler inteiro com segurança
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

// ==================================================================================
// FUNÇÕES AUXILIARES DE UNICIDADE (Tratamento de Exceções)
// ----------------------------------------------------------------------------------
// Estas funções garantem que não existam dois usuários com o mesmo ID.
// 1. try: Tenta pegar o CPF.
// 2. throw: Se o CPF já existe, lança um erro manual (runtime_error).
// 3. catch: Captura o erro, mostra a mensagem e o 'while(true)' força a tentar de novo.
// ==================================================================================

std::string SistemaController::obterCPFUnicoCatador() {
    while (true) {
        try {
            // Validação de formato
            std::string cpf = InputHandler::getCPF("Digite o CPF para cadastro: ");
            
            // Validação de Regra de Negócio (Duplicidade)
            if (catadorExiste(cpf)) {
                // [Exceção] 
                throw std::runtime_error("Erro: Este CPF ja esta cadastrado como Catador!");
            }
            return cpf; // Se passou direto, retorna o CPF válido e único
            
        } catch (const std::runtime_error& e) {
            // [Exceção] avisa o usuário
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

// ==================================================================================
// MENU CATADOR
// ==================================================================================
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
            std::string cpf = obterCPFUnicoCatador(); 
            std::string nome = InputHandler::getString("Nome Completo: ");
            std::string end = InputHandler::getEndereco("Endereco: ");
            
            // Cadastro sem material inicial
            Catador cat(nome, end, cpf, nullptr);
            cat.cadastro(nome, end, cpf, nullptr);
            
            cpfLogado = cpf;
        }

        if (!cpfLogado.empty()) {
            Catador cat("", "", cpfLogado, nullptr);
            cat.carregarSaldo(); // Carrega o saldo atual do arquivo
            
            int op;
            do {
                std::cout << "\n=== AREA DO CATADOR (" << cpfLogado << ") ===\n";
                std::cout << "1. Ver Cooperativas (Onde Vender)\n";
                std::cout << "2. Ver Meu Saldo\n";
                std::cout << "3. Ver Locais de Coleta (Colaboradores)\n"; // [OPÇÃO MANTIDA]
                std::cout << "0. Sair (Logout)\n";
                
                op = InputHandler::getInt("Opcao: ");
                
                if(op == 1) cat.visualizarCooperativas();
                else if(op == 2) std::cout << "Saldo: R$ " << cat.getSaldo() << "\n";
                else if(op == 3) cat.visualizarColaboradores(); // Chama o método novo do Catador
                
            } while (op != 0);
        }

    } while (opInicial != 0);
}

// ==================================================================================
// MENU COLABORADOR
// ==================================================================================
void SistemaController::menuColaborador() {
    int opInicial;
    do {
        // Menus de Login/Cadastro similares ao Catador)
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
            
            // Objeto Stack criado, dados salvos no TXT, objeto destruído.
            Colaborador col(nome, end, cpf, nullptr);
            col.cadastro(nome, end, cpf, nullptr);
            
            // Bônus de gamificação
            col.receberPontos(100); 
            cpfLogado = cpf;
        }

        // Área Logada
        if (!cpfLogado.empty()) {
            Colaborador col("", "", cpfLogado, nullptr);
            col.carregarPontos(); // Lê os pontos do arquivo
            int op;
            do {
                std::cout << "\n=== AREA DO COLABORADOR (" << cpfLogado << ") ===\n";
                std::cout << "1. Ver Meus Pontos (e Regras)\n";
                std::cout << "2. Fazer Doacao (Entregar Material)\n";
                std::cout << "0. Sair\n";
                
                op = InputHandler::getInt("Opcao: ");
                
                if(op == 1) {
                    // UX: Mostra tabela de pesos
                    std::cout << "\n=== EXTRATO ===\nTOTAL: " << col.getPontos() << " PTS\n";
                    std::cout << "Tabela: Plastico(x3), Papel(x2), Metal(x4)\n";
                }
                else if(op == 2) {
                    std::cout << "\n--- NOVA DOACAO ---\n";
                    int t = InputHandler::getTipoMaterial("Material: ");
                    float p = InputHandler::getFloat("Peso (kg): ");
                    
                    // Aqui usamos 'new' porque o objeto Material é independente
                    // e passado por ponteiro. Estamos pedindo memória manual ao sistema.
                    Material* m = new Material(p, t);
                    
                    // Passamos o ponteiro para o método processar
                    col.realizarDoacao(m);
                    
                    // DESALOCAÇÃO OBRIGATÓRIA
                    // Como nós criamos com 'new' aqui neste escopo, e a função realizarDoacao
                    // apenas lê os dados para salvar no arquivo (ela não toma posse do ponteiro),
                    // nós devemos deletar 'm' aqui para evitar vazamento de memória.
                    delete m; 
                    m = nullptr;
                }
            } while (op != 0);
        }
    } while (opInicial != 0);
}

// ==================================================================================
// MENU COOPERATIVA
// ==================================================================================
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
            std::cout << "--- PRECOS INICIAIS ---\n";
            float p1 = InputHandler::getFloat("Plastico: ");
            float p2 = InputHandler::getFloat("Papel: ");
            float p3 = InputHandler::getFloat("Metal: ");
            
            Cooperativas coop;
            coop.cadastro(p1, p2, p3, end, cnpj, nullptr);
            cnpjLogado = cnpj;
        }

        if (!cnpjLogado.empty()) {
            Cooperativas coop;
            coop.setCnpj(cnpjLogado);
            coop.carregarDados(); // Carrega preços do arquivo

            // Exibe os preços carregados
            std::cout << "\n[Sessao Iniciada] Precos Atuais:\n";
            std::cout << "Plastico: R$" << coop.getPrecoPlastico() 
                      << " | Papel: R$" << coop.getPrecoPapel() 
                      << " | Metal: R$" << coop.getPrecoMetal() << "\n";

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
                    std::string cpfCatador = InputHandler::getCPF("CPF do Catador: ");
                    
                    if (!catadorExiste(cpfCatador)) {
                        std::cout << ">> Erro: Catador nao encontrado! Cadastre-o primeiro.\n";
                    } else {
                        int t = InputHandler::getTipoMaterial("Material recebido: ");
                        float peso = InputHandler::getFloat("Peso (kg): ");
                        
                        // Define preço baseado no que foi carregado do arquivo
                        float precoKg = 0;
                        if(t == 1) precoKg = coop.getPrecoPlastico();
                        else if(t == 2) precoKg = coop.getPrecoPapel();
                        else if(t == 3) precoKg = coop.getPrecoMetal();
                        
                        float total = peso * precoKg;
                        
                        // Atualiza o arquivo do catador
                        Catador c("", "N/A", cpfCatador, nullptr);
                        c.adicionarSaldoAoArquivo(total);
                        
                        std::string nomeMat = (t==1) ? "Plastico" : (t==2) ? "Papel" : "Metal";
                        coop.registrarCompra(cpfCatador, peso, total, nomeMat);
                        
                        std::cout << ">> SUCESSO! R$ " << total << " pagos ao CPF " << cpfCatador << ".\n";
                    }
                }
                else if(op == 3) coop.gerarRelatorioEstatistico();
            } while (op != 0);
        }
    } while (opInicial != 0);
}

// ==================================================================================
// MENU ADMINISTRADOR
// ----------------------------------------------------------------------------------
// Acesso a relatórios globais e ranking.
// ==================================================================================
void SistemaController::menuAdministrador() {
    Administrador admin;
    int op;
    do {
        std::cout << "\n=== PAINEL ADMIN ===\n";
        std::cout << "1. Visualizar Colaboradores\n";
        std::cout << "2. Visualizar Cooperativas\n";
        std::cout << "3. Visualizar Catadores\n";
        std::cout << "4. Ranking de Pontos\n";
        std::cout << "5. Relatorio Global (Total Material)\n";
        std::cout << "0. Voltar\n";
        
        op = InputHandler::getInt("Opcao: ");
        
        if(op==1) admin.visualizarColaboradores();
        else if(op==2) admin.visualizarCooperativas();
        else if(op==3) admin.visualizarCatadores();
        else if(op==4) admin.gerarRanking(); // Chama lógica de ordenação 
        else if(op==5) admin.relatorioTotalMaterial(); // Chama lógica de consolidação
        else if(op!=0) std::cout << "Opcao invalida.\n";
        
    } while(op!=0);
}

// ==================================================================================
// FUNÇÕES DE VERIFICAÇÃO 
// ----------------------------------------------------------------------------------
// Abrem os arquivos em modo leitura para checar existência de strings.
// ==================================================================================
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