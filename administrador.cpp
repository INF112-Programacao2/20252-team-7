#include "administrador.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // Necessário para sort
#include <iomanip>   // Necessário para setw (formatação da tabela)

Administrador::Administrador() {
    std::cout << ">> Painel de Administrador iniciado.\n";
}

Administrador::~Administrador() {}

void Administrador::acessarSistemaRegistro() {
    std::cout << "Funcao de registro direto disponivel nos menus de cada usuario.\n";
}

void Administrador::visualizarColaboradores() {
    std::cout << "\n=== COLABORADORES CADASTRADOS ===\n";
    std::ifstream arquivo("cadastro_colaborador.txt");
    std::string linha;
    
    if (!arquivo.is_open()) {
        std::cout << "Nenhum colaborador cadastrado.\n";
        return;
    }
    
    while (std::getline(arquivo, linha)) {
        std::cout << linha << "\n";
    }
    arquivo.close();
}

void Administrador::visualizarCooperativas() {
    std::cout << "\n=== COOPERATIVAS CADASTRADAS ===\n";
    std::ifstream arquivo("cadastro_cooperativa.txt");
    std::string linha;
    
    if (!arquivo.is_open()) {
        std::cout << "Nenhuma cooperativa cadastrada.\n";
        return;
    }
    
    while (std::getline(arquivo, linha)) {
        std::cout << linha << "\n";
    }
    arquivo.close();
}

void Administrador::visualizarCatadores() {
    std::cout << "\n=== CATADORES CADASTRADOS ===\n";
    std::ifstream arquivo("cadastro_catador.txt");
    std::string linha;
    
    if (!arquivo.is_open()) {
        std::cout << "Nenhum catador cadastrado.\n";
        return;
    }
    
    while (std::getline(arquivo, linha)) {
        std::cout << linha << "\n";
    }
    arquivo.close();
}

// === RELATÓRIO GLOBAL (SOMA TUDO) ===
void Administrador::relatorioTotalMaterial() {
    std::cout << "\n============================================\n";
    std::cout << "   RELATORIO CONSOLIDADO (ADMINISTRATIVO)   \n";
    std::cout << "============================================\n";
    
    // PARTE 1: MATERIAL EM POSSE DOS COLABORADORES (AINDA NÃO VENDIDO)
    float colabPlastico = 0, colabPapel = 0, colabMetal = 0;
    std::ifstream arqColab("cadastro_colaborador.txt");
    std::string linha;
    
    if (arqColab.is_open()) {
        while (std::getline(arqColab, linha)) {
            if (linha.find("Material:") != std::string::npos) {
                try {
                    size_t posDoisPontos = linha.find(":");
                    size_t posKg = linha.find("kg");
                    if (posDoisPontos != std::string::npos && posKg != std::string::npos) {
                        float p = std::stof(linha.substr(posDoisPontos + 1, posKg - (posDoisPontos + 1)));
                        if (linha.find("Plastico") != std::string::npos) colabPlastico += p;
                        else if (linha.find("Papel") != std::string::npos) colabPapel += p;
                        else if (linha.find("Metal") != std::string::npos) colabMetal += p;
                    }
                } catch (...) {}
            }
        }
        arqColab.close();
    }
    
    // PARTE 2: MATERIAL JÁ COMPRADO PELAS COOPERATIVAS (PARSER DO HISTÓRICO)
    float coopPlastico = 0, coopPapel = 0, coopMetal = 0;
    float dinheiroMovimentado = 0;
    std::ifstream arqCompras("historico_compras.txt");
    
    if (arqCompras.is_open()) {
        while (std::getline(arqCompras, linha)) {
            try {
                // 1. Somar Dinheiro
                size_t posCifrao = linha.find("R$ ");
                size_t posPor = linha.find(" por ");
                if (posCifrao != std::string::npos && posPor != std::string::npos) {
                    float valor = std::stof(linha.substr(posCifrao + 3, posPor - (posCifrao + 3)));
                    dinheiroMovimentado += valor;
                }

                // 2. Somar Peso por Tipo
                size_t posKg = linha.find("kg de ");
                if (posPor != std::string::npos && posKg != std::string::npos) {
                    float peso = std::stof(linha.substr(posPor + 5, posKg - (posPor + 5)));
                    
                    if (linha.find("Plastico") != std::string::npos) coopPlastico += peso;
                    else if (linha.find("Papel") != std::string::npos) coopPapel += peso;
                    else if (linha.find("Metal") != std::string::npos) coopMetal += peso;
                }
            } catch (...) {
                continue; 
            }
        }
        arqCompras.close();
    }

    std::cout << std::fixed << std::setprecision(2);
    
    std::cout << "\n>> 1. ESTOQUE NOS COLABORADORES (Ainda nao reciclado):\n";
    std::cout << "   - Plastico: " << colabPlastico << " kg\n";
    std::cout << "   - Papel:    " << colabPapel << " kg\n";
    std::cout << "   - Metal:    " << colabMetal << " kg\n";
    
    std::cout << "\n>> 2. TOTAL COMPRADO POR TODAS AS COOPERATIVAS (Reciclado):\n";
    std::cout << "   - Plastico: " << coopPlastico << " kg\n";
    std::cout << "   - Papel:    " << coopPapel << " kg\n";
    std::cout << "   - Metal:    " << coopMetal << " kg\n";
    std::cout << "   -----------------------------\n";
    std::cout << "   TOTAL GERAL RECICLADO: " << (coopPlastico + coopPapel + coopMetal) << " kg\n";
    
    std::cout << "\n>> 3. FINANCEIRO DO SISTEMA:\n";
    std::cout << "   - Dinheiro total pago aos catadores: R$ " << dinheiroMovimentado << "\n";
    std::cout << "============================================\n";
}

// === RANKING DE COLABORADORES ===
void Administrador::gerarRanking() {
    std::ifstream arquivo("cadastro_colaborador.txt");
    if (!arquivo.is_open()) {
        std::cout << "Erro: Nao foi possivel abrir o banco de dados de colaboradores.\n";
        return;
    }

    std::vector<RankItem> lista;
    std::string linha;
    std::string nomeAtual = "";
    int pontosAtuais = 0;

    while (std::getline(arquivo, linha)) {
        if (linha.find("Nome: ") == 0) {
            nomeAtual = linha.substr(6);
        }
        else if (linha.find("Pontos: ") == 0) {
            try {
                pontosAtuais = std::stoi(linha.substr(8));
            } catch (...) {
                pontosAtuais = 0;
            }
        }
        else if (linha.find("------------------------") != std::string::npos) {
            if (!nomeAtual.empty()) {
                lista.push_back({nomeAtual, pontosAtuais});
            }
            nomeAtual = "";
            pontosAtuais = 0;
        }
    }
    arquivo.close();

    if (lista.empty()) {
        std::cout << "Nenhum colaborador com pontos registrado.\n";
        return;
    }

    // Ordenação Decrescente
    std::sort(lista.begin(), lista.end(), [](const RankItem& a, const RankItem& b) {
        return a.pontos > b.pontos;
    });

    std::ofstream arquivoRanking("ranking_geral.txt");
    
    std::cout << "\n===================================\n";
    std::cout << "       TOP COLABORADORES           \n";
    std::cout << "===================================\n";
    std::cout << std::left << std::setw(5) << "POS" 
              << std::setw(25) << "NOME" 
              << std::right << std::setw(10) << "PONTOS" << "\n";
    std::cout << "-----------------------------------\n";

    arquivoRanking << "=== RANKING ATUALIZADO ===\n\n";
    
    for (size_t i = 0; i < lista.size(); i++) {
        std::cout << std::left << std::setw(5) << (i + 1) 
                  << std::setw(25) << lista[i].nome 
                  << std::right << std::setw(10) << lista[i].pontos << "\n";
                  
        arquivoRanking << (i + 1) << ". " << lista[i].nome << " - " << lista[i].pontos << " pts\n";
    }
    std::cout << "===================================\n";
    
    arquivoRanking.close();
    std::cout << ">> Ranking salvo em 'ranking_geral.txt' com sucesso!\n";
}