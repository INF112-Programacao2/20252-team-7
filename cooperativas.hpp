#ifndef COOPERATIVAS_HPP // [Pré-processador] Guarda de inclusão
#define COOPERATIVAS_HPP

#include <iostream>
#include <string>

class Material;
class Catador;

// ==================================================================================
// CLASSE COOPERATIVAS
// ==================================================================================
class Cooperativas {

// ==================================================================================
// ATRIBUTOS PRIVADOS 
// ----------------------------------------------------------------------------------
private:
    // Dados de negócio específicos para calcular pagamentos
    float precoPlastico;
    float precoPapel;
    float precoMetal;
    
    std::string cnpj;
    std::string endereco;
    
    // [Memória]
    // A Cooperativa "TEM UM" estoque de material.

    Material* material;
    
public:
    // [Construtores]
    // Inicializam a cooperativa vazia ou com dados pré-definidos.
    Cooperativas();
    Cooperativas(float pPlastico, float pPapel, float pMetal, std::string cnpj, std::string endereco, Material* material);
    
    // [Memória - Destrutor]
    // Fundamental! Quando o objeto Cooperativa sai de escopo, este método
    // é chamado para dar 'delete' no ponteiro 'material'.
    ~Cooperativas();

    // [Getters e Setters] Interface pública para manipular dados privados
    float getPrecoPlastico();
    float getPrecoPapel();
    float getPrecoMetal();
    
    void setPrecos(float plastico, float papel, float metal);
    
    std::string getCnpj();
    std::string getEndereco();
    Material* getMaterial();
    void setCnpj(std::string);
    void setEndereco(std::string);
    void setMaterial(Material*);

    // ==============================================================================
    // MÉTODOS DE REGRA DE NEGÓCIO
    // ------------------------------------------------------------------------------
    // Este método recebe um objeto 'Catador' por referencia (&).
    // Isso significa que a Cooperativa vai mexer diretamente no objeto original
    // do Catador (alterando o saldo dele na memória).
    // Se não usássemos &, estaríamos alterando apenas uma cópia, e o saldo
    // original continuaria zero.
    void comprarMaterial(Catador& catador, float peso);
    
    // Salva os dados cadastrais da cooperativa no arquivo .txt
    void cadastro(float pPlastico, float pPapel, float pMetal, std::string endereco, std::string cnpj, Material* material);
    
    // Lê o arquivo de histórico e filtra apenas as compras desta cooperativa (pelo CNPJ)
    void relatorioMaterialComprado();
    
    // [Lógica de Persistência]
    // Grava uma nova linha no arquivo 'historico_compras.txt' contendo
    // quem comprou (CNPJ), quem vendeu (CPF), o que (Material) e quanto (Valor).
    void registrarCompra(const std::string& cpfCatador, float peso, float valorTotal, std::string nomeMaterial);
    
    // Gera um arquivo de texto separado (relatório estatístico) somando os totais.
    void gerarRelatorioEstatistico(); 
    
    // Lista todas as cooperativas cadastradas no sistema.
    void visualizarCooperativas();

    // Carrega preços e endereço do arquivo ao logar
    void carregarDados();
};

#endif