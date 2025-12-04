#ifndef COLABORADOR_HPP 
#define COLABORADOR_HPP

#include <string>
#include "Pessoa.hpp" 

// ==================================================================================
// CLASSE COLABORADOR
// ==================================================================================
class Colaborador : public Pessoa {

// ==================================================================================
// ATRIBUTOS PRIVADOS
// ----------------------------------------------------------------------------------
private:
    // [Gamificação] Atributo exclusivo desta classe.
    // Armazena a pontuação acumulada pelas doações.
    int pontos;

public:
    // ==============================================================================
    // CONSTRUTORES E DESTRUTOR
    // ------------------------------------------------------------------------------
    
    // Construtor de cópia: Cria um Colaborador a partir de um objeto Pessoa existente.
    Colaborador(const Pessoa& pessoa);
    
    // Construtor completo: Inicializa a base (Pessoa) e zera os pontos.
    Colaborador(std::string nome, std::string endereco, std::string cpf, Material* material = nullptr);
    
    // [Memória] Destrutor virtual: Garante limpeza correta na hierarquia de herança.
    ~Colaborador();

    // ==============================================================================
    // GETTERS E SETTERS
    // ------------------------------------------------------------------------------
    int getPontos() const;
    void setPontos(int pontos);
    
    // ==============================================================================
    // MÉTODOS DE LÓGICA E PERSISTÊNCIA
    // ------------------------------------------------------------------------------
    
    // [Persistência] Cria o registro inicial no arquivo 'cadastro_colaborador.txt'.
    void cadastro(std::string nome, std::string endereco, std::string cpf, Material* material) override;
    
    // [Regra de Negócio Principal]
    // Substitui a lógica simples de ganhar pontos.
    // 1. Recebe um material (ponteiro alocado na Heap).
    // 2. Aplica multiplicadores (Plástico x3, Metal x4...).
    // 3. Atualiza os pontos na memória e no arquivo.
    // 4. Chama 'adicionarMaterialAoArquivo' para atualizar o estoque global.
    void realizarDoacao(Material* materialDoado);

    // [Regra de Negócio]
    // Permite dar pontos fixos (bônus) sem depender de peso de material.
    // Ex: Ganha 100 pontos ao se cadastrar.
    void receberPontos(int valor); 

    // Apenas lê e exibe o arquivo de cooperativas.
    void visualizarCooperativas();
    
    // [Gestão de Estado ]
    // Estes métodos resolvem o problema de "Amnésia" do programa.
    // carregarPontos: Lê do TXT para a RAM ao fazer login.
    // salvarPontosNoArquivo: Escreve da RAM para o TXT após cada doação.
    void carregarPontos(); 
    void salvarPontosNoArquivo();
    
    // [Lógica de Estoque]
    // Método avançado que abre o arquivo, procura se o usuário já doou aquele
    // tipo de material antes e soma o novo peso ao antigo.
    // Essencial para o Relatório Global do Administrador funcionar corretamente.
    void adicionarMaterialAoArquivo(Material* m);
};

#endif