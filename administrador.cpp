#include "administrador.hpp"
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>   
#include <algorithm> 
#include <iomanip>   

// ==================================================================================
// CONSTRUTOR E DESTRUTOR
// ==================================================================================
Administrador::Administrador() {
    std::cout << ">> Painel de Administrador iniciado.\n";
}

Administrador::~Administrador() {}

// ==================================================================================
// MÉTODOS DE VISUALIZAÇÃO 
// ----------------------------------------------------------------------------------
// Estes 3 métodos seguem o mesmo padrão:
// 1. Abrem o arquivo em modo leitura.
// 2. Verificam se abriu com sucesso.
// 3. Loop while(getline): Lê linha por linha até o fim do arquivo.
// 4. Imprimem na tela.
// ==================================================================================

void Administrador::acessarSistemaRegistro() {
    std::cout << "Funcao de registro direto disponivel nos menus de cada usuario.\n";
}

void Administrador::visualizarColaboradores() {
    std::cout << "\n=== COLABORADORES CADASTRADOS ===\n";
    std::ifstream arquivo("cadastro_colaborador.txt");
    std::string linha;
    
    if (!arquivo.is_open()) {
        std::cout << "Nenhum colaborador cadastrado ou erro ao abrir arquivo.\n";
        return;
    }
    
    while (std::getline(arquivo, linha)) {
        std::cout << linha << "\n";
    }
    arquivo.close(); // Boa prática: fechar explicitamente
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

// ==================================================================================
// RELATÓRIO CONSOLIDADO 
// ----------------------------------------------------------------------------------
// Ler 'cadastro_colaborador.txt' para saber o que está estocado nas casas.
// Ler 'historico_compras.txt' para saber o que já foi reciclado.
// ==================================================================================
void Administrador::relatorioTotalMaterial() {
    std::cout << "\n============================================\n";
    std::cout << "   RELATORIO CONSOLIDADO (ADMINISTRATIVO)   \n";
    std::cout << "============================================\n";
    
    // --- ESTOQUE NOS COLABORADORES ---
    float colabPlastico = 0, colabPapel = 0, colabMetal = 0;
    std::ifstream arqColab("cadastro_colaborador.txt");
    std::string linha;
    
    if (arqColab.is_open()) {
        while (std::getline(arqColab, linha)) {
            // Procura linhas que tenham "Material:" mas que NÃO sejam "Nenhum"
            if (linha.find("Material:") != std::string::npos && linha.find("Nenhum") == std::string::npos) {
                try {
                    // Exemplo de linha: "Material: 10.50kg de Plastico"
                    // Lógica: Encontrar onde começa o número (depois de ':') e onde termina (antes de 'kg')
                    size_t posDoisPontos = linha.find(":");
                    size_t posKg = linha.find("kg");
                    
                    if (posDoisPontos != std::string::npos && posKg != std::string::npos) {
                        // Extrai a substring numérica e converte
                        float p = std::stof(linha.substr(posDoisPontos + 1, posKg - (posDoisPontos + 1)));
                        
                        // Classifica e soma
                        if (linha.find("Plastico") != std::string::npos) colabPlastico += p;
                        else if (linha.find("Papel") != std::string::npos) colabPapel += p;
                        else if (linha.find("Metal") != std::string::npos) colabMetal += p;
                    }
                } catch (...) {
                    // Se a linha estiver mal formatada, ignora e continua
                }
            }
        }
        arqColab.close();
    }
    
    // --- HISTÓRICO DE COMPRAS (JÁ RECICLADO) ---
    float coopPlastico = 0, coopPapel = 0, coopMetal = 0;
    float dinheiroMovimentado = 0;
    std::ifstream arqCompras("historico_compras.txt");
    
    if (arqCompras.is_open()) {
        while (std::getline(arqCompras, linha)) {
            try {
                // Exemplo: "Coop ... pagou R$ 50.00 por 10.00kg de Metal ..."
                
                // 1. Extração do Dinheiro (Entre 'R$ ' e ' por ')
                size_t posCifrao = linha.find("R$ ");
                size_t posPor = linha.find(" por ");
                
                if (posCifrao != std::string::npos && posPor != std::string::npos) {
                    float valor = std::stof(linha.substr(posCifrao + 3, posPor - (posCifrao + 3)));
                    dinheiroMovimentado += valor;
                }

                // 2. Extração do Peso (Entre ' por ' e 'kg de ')
                size_t posKg = linha.find("kg de ");
                if (posPor != std::string::npos && posKg != std::string::npos) {
                    float peso = std::stof(linha.substr(posPor + 5, posKg - (posPor + 5)));
                    
                    if (linha.find("Plastico") != std::string::npos) coopPlastico += peso;
                    else if (linha.find("Papel") != std::string::npos) coopPapel += peso;
                    else if (linha.find("Metal") != std::string::npos) coopMetal += peso;
                }
            } catch (...) {
                continue; // Pula linha com erro
            }
        }
        arqCompras.close();
    }

    // Formatação de saída com 2 casas decimais
    std::cout << std::fixed << std::setprecision(2);
    
    std::cout << "\n>> 1. ESTOQUE NOS COLABORADORES (Ainda nao recolhido):\n";
    std::cout << "   - Plastico: " << colabPlastico << " kg\n";
    std::cout << "   - Papel:    " << colabPapel << " kg\n";
    std::cout << "   - Metal:    " << colabMetal << " kg\n";
    
    std::cout << "\n>> 2. TOTAL COMPRADO POR TODAS AS COOPERATIVAS (Reciclado):\n";
    std::cout << "   - Plastico: " << coopPlastico << " kg\n";
    std::cout << "   - Papel:    " << coopPapel << " kg\n";
    std::cout << "   - Metal:    " << coopMetal << " kg\n";
    std::cout << "   -----------------------------\n";
    std::cout << "   TOTAL GERAL PROCESSADO: " << (coopPlastico + coopPapel + coopMetal) << " kg\n";
    
    std::cout << "\n>> 3. FINANCEIRO DO SISTEMA:\n";
    std::cout << "   - Dinheiro total pago aos catadores: R$ " << dinheiroMovimentado << "\n";
    std::cout << "============================================\n";
}

// ==================================================================================
// RANKING DE PONTUAÇÃO (STL - Sort e Vector)
// ----------------------------------------------------------------------------------
// [Algoritmo de Ordenação]
// ==================================================================================
void Administrador::gerarRanking() {
    std::ifstream arquivo("cadastro_colaborador.txt");
    if (!arquivo.is_open()) {
        std::cout << "Erro: Nao foi possivel abrir o banco de dados de colaboradores.\n";
        return;
    }

    // [STL] std::vector
    // Um array que cresce automaticamente. Armazena objetos do tipo 'RankItem'.
    std::vector<RankItem> lista;
    
    std::string linha;
    std::string nomeAtual = "";
    int pontosAtuais = 0;

    // O arquivo tem várias linhas por usuário. Precisamos juntar Nome e Pontos.
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
            // Ao encontrar o separador, salvamos o objeto completo no vetor
            if (!nomeAtual.empty()) {
                lista.push_back({nomeAtual, pontosAtuais});
            }
            // Reseta variáveis temporárias
            nomeAtual = "";
            pontosAtuais = 0;
        }
    }
    arquivo.close();

    if (lista.empty()) {
        std::cout << "Nenhum colaborador com pontos registrado.\n";
        return;
    }

    // O sort organiza o vetor.
    std::sort(lista.begin(), lista.end(), [](const RankItem& a, const RankItem& b) {
        return a.pontos > b.pontos;
    });

    // Saída Formatada (Tabela)
    std::ofstream arquivoRanking("ranking_geral.txt");
    
    std::cout << "\n===================================\n";
    std::cout << "       TOP COLABORADORES           \n";
    std::cout << "===================================\n";
    // setw define a largura da coluna para alinhar o texto
    std::cout << std::left << std::setw(5) << "POS" 
              << std::setw(25) << "NOME" 
              << std::right << std::setw(10) << "PONTOS" << "\n";
    std::cout << "-----------------------------------\n";

    arquivoRanking << "=== RANKING GERAL DE PONTUACAO ===\n\n";
    
    for (size_t i = 0; i < lista.size(); i++) {
        // Imprime no Console
        std::cout << std::left << std::setw(5) << (i + 1) 
                  << std::setw(25) << lista[i].nome 
                  << std::right << std::setw(10) << lista[i].pontos << "\n";
                  
        // Imprime no Arquivo
        arquivoRanking << (i + 1) << ". " << lista[i].nome << " - " << lista[i].pontos << " pts\n";
    }
    std::cout << "===================================\n";
    
    arquivoRanking.close();
    std::cout << ">> Ranking salvo em 'ranking_geral.txt' com sucesso!\n";
}