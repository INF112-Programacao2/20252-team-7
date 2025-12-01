#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include <iostream>
#include <string>
#include <vector> // Necessário para manipular a lista do Ranking

// Estrutura auxiliar para facilitar a ordenação do Ranking
struct RankItem {
    std::string nome;
    int pontos;
};

class Administrador {
public:
    Administrador();
    ~Administrador();
    
    // Funcionalidades de Visualização
    void acessarSistemaRegistro();
    void visualizarColaboradores();
    void visualizarCooperativas();
    void visualizarCatadores();
    
    // Funcionalidades de Relatório
    void relatorioTotalMaterial(); // Agora faz o consolidado global
    void gerarRanking();           // Novo método que cria o ranking.txt
};

#endif