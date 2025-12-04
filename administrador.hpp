#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include <iostream>
#include <string>
#include <vector> 

// ==================================================================================
// ESTRUTURA AUXILIAR: RankItem
// ----------------------------------------------------------------------------------
// Para fazer o Ranking, precisamos ler o arquivo, guardar o par (Nome, Pontos)
// na memória e depois ordenar essa lista. Essa struct facilita a criação de um
// std::vector<RankItem> para usar no algoritmo de 'sort'.
// ==================================================================================
struct RankItem {
    std::string nome;
    int pontos;
};

// ==================================================================================
// CLASSE ADMINISTRADOR
// ----------------------------------------------------------------------------------
// Diferente de 'Catador' ou 'Colaborador', esta classe não herda de 'Pessoa'.
// Ela atua como um "Gerente do Sistema".
//
// Responsabilidades:
// 1. Não mantém dados persistentes próprios (não tem atributos como nome ou saldo).
// 2. A função dela é ler os arquivos gerados pelas outras classes (.txt),
//    processar esses dados (somas, ordenação) e exibir relatórios.
// ==================================================================================
class Administrador {
public:
    // Construtor e Destrutor padrão.
    Administrador();
    ~Administrador();
    
    // ==============================================================================
    // MÉTODOS DE VISUALIZAÇÃO 
    // ==============================================================================
    
    // Mostra mensagem sobre como o registro funciona no sistema.
    void acessarSistemaRegistro();
    
    // Lista o conteúdo de 'cadastro_colaborador.txt'.
    void visualizarColaboradores();
    
    // Lista o conteúdo de 'cadastro_cooperativa.txt'.
    void visualizarCooperativas();
    
    // Lista o conteúdo de 'cadastro_catador.txt'.
    void visualizarCatadores();
    
    // ==============================================================================
    // MÉTODOS DE RELATÓRIOS 
    // ==============================================================================
    
    // [Agregação Global]
    // Lê o arquivo de colaboradores e o histórico de compras
    // (material já vendido), soma tudo por categoria (Plástico, Papel, Metal)
    // e mostra o total financeiro movimentado no sistema.
    void relatorioTotalMaterial(); 
    
    // [Algoritmo de Ordenação]
    // 1. Lê todos os colaboradores e seus pontos.
    // 2. Armazena em um vetor de 'RankItem'.
    // 3. Ordena o vetor do maior para o menor.
    // 4. Gera um novo arquivo 'ranking_geral.txt' com o pódio.
    void gerarRanking();
};

#endif