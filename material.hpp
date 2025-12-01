#ifndef MATERIAL_HPP // [Pré-processador] Guarda de Inclusão (Include Guard)
#define MATERIAL_HPP // Impede que este arquivo seja lido mais de uma vez, evitando erros de redefinição.

#include <string> // Biblioteca padrão para manipular textos (std::string)

// ==================================================================================
// CLASSE MATERIAL
// ----------------------------------------------------------------------------------
// Esta classe representa um objeto do mundo real: o material reciclável.
// Ela é simples e serve principalmente para agrupar dados (peso e tipo).
// ==================================================================================
class Material {

// ==================================================================================
// ATRIBUTOS PRIVADOS
// ==================================================================================
private:
    float peso; // Peso em KG
    int tipo;   // Código do tipo: 1=Plástico, 2=Papel, 3=Metal

// ==================================================================================
// MÉTODOS PÚBLICOS
// ----------------------------------------------------------------------------------
// [Interface Pública]
// São as funções que o resto do programa pode usar para interagir com o Material.
// ==================================================================================
public:
    // [Construtor Padrão] Cria um material vazio (peso 0, tipo 0)
    Material();
    
    // [Construtor Parametrizado] Cria um material já com dados definidos
    // Ex: Material* m = new Material(10.5, 1);
    Material(float peso, int tipo);
    
    // [Destrutor] Chamado quando o objeto é destruído (delete m)
    ~Material();

    // [Getters]
    float getPeso();
    int getTipo();
    
    // [Helper / Utilitário]
    // Função auxiliar que traduz o código numérico (int) para texto (string).
    // Ex: Transforma 1 em "Plastico". Útil para relatórios e exibição na tela.
    std::string getNomeTipo(); 
    
    // [Setters]
    void setPeso(float peso);
    void setTipo(int tipo);
};

#endif // Fim do guarda de inclusão MATERIAL_HPP