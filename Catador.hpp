#ifndef CATADOR_HPP
#define CATADOR_HPP

#include "Pessoa.hpp" 

// ==================================================================================
// CLASSE CATADOR
// ----------------------------------------------------------------------------------
// A classe Catador herda publicamente de Pessoa (: public Pessoa).
// Isso significa que o Catador ganha automaticamente todos os atributos (nome, cpf, 
// endereco, material) e métodos da classe Pessoa.
// ==================================================================================
class Catador : public Pessoa {

// ==================================================================================
// ATRIBUTOS PRIVADOS
// ----------------------------------------------------------------------------------
// O saldo financeiro é um dado sensível. Declaramos como 'private' para que
// ninguém fora desta classe possa alterá-lo diretamente (ex: catador._saldo = 1000).
// ==================================================================================
private:
    float _saldo; // Dinheiro acumulado pelas vendas para a Cooperativa

public:
    // ==============================================================================
    // CONSTRUTORES
    Catador(const Pessoa& pessoa);
    
    // Construtor Completo:
    // Recebe os dados básicos e repassa para o construtor da classe pai (Pessoa),
    // enquanto inicializa seu atributo próprio (_saldo) com 0.
    Catador(std::string nome, std::string endereco, std::string cpf, Material* material = nullptr);
    
    // [Memória - Destrutor]
    ~Catador();

    // ==============================================================================
    // MÉTODOS DE ACESSO (Getters e Setters)
    // ------------------------------------------------------------------------------
    float getSaldo() const;
    
    // Altera o saldo na memória RAM (temporário).
    void setSaldo(float valor);
    
    // ==============================================================================
    // MÉTODOS DE REGRA DE NEGÓCIO
    // ------------------------------------------------------------------------------
    
    // Simula a ação de coletar mais material na rua, somando ao peso atual.
    void recolherMaterial(Material* material);
    
    // [Persistência] Cria o registro inicial do catador no arquivo .txt
    void cadastro(std::string nome, std::string endereco, std::string cpf, Material* material);
    
    // Apenas lê o arquivo de cooperativas para informar onde vender.
    void visualizarCooperativas();
    
    // ==============================================================================
    // GESTÃO FINANCEIRA E PERSISTÊNCIA
    // ------------------------------------------------------------------------------
    
    // [Lógica de Atualização]
    // Este método resolve o problema de persistência do dinheiro.
    // Ele abre o arquivo 'cadastro_catador.txt', procura a linha deste CPF específico
    // e edita o valor do saldo diretamente no disco rígido.
    // Usado pela Cooperativa na hora do pagamento.
    void adicionarSaldoAoArquivo(float valorAdicionado);
    
    // Lê o arquivo de colaboradores.
    // Filtra os dados para mostrar apenas Endereço e Materiais (preserva a privacidade do nome).
    void visualizarColaboradores();
    
    // [Gestão de Estado]
    // Quando o usuário entra no sistema, este método lê o arquivo .txt e atualiza
    // a variável '_saldo' na memória RAM para refletir o valor real guardado.
    void carregarSaldo(); 
};

#endif