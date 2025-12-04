#include "material.hpp" // Inclui a definição da classe para que o compilador conheça os métodos
#include <string>       // Necessário para usar std::string

// ==================================================================================
// CONSTRUTOR PADRÃO
// ==================================================================================
Material::Material() : peso(0), tipo(0) {
    // Corpo vazio, pois as variáveis já foram iniciadas na lista acima.
}

// ==================================================================================
// CONSTRUTOR PARAMETRIZADO
// ----------------------------------------------------------------------------------
// Permite criar o objeto já com dados: 'Material* m = new Material(10.5, 1);'.
// Recebe 'p' e 't' e joga direto nos atributos privados 'peso' e 'tipo'.
// ==================================================================================
Material::Material(float p, int t) : peso(p), tipo(t) {}

// ==================================================================================
// DESTRUTOR
// ==================================================================================
Material::~Material() {}

// ==================================================================================
// GETTERS 
// ==================================================================================
float Material::getPeso() {
    return this->peso;
}

int Material::getTipo() {
    return this->tipo;
}

// ==================================================================================
// MÉTODO DE LÓGICA AUXILIAR
// ----------------------------------------------------------------------------------
// [Lógica]
// Traduz o código numérico interno (1, 2, 3) para uma String legível.
// Isso evita que a interface (SistemaController) tenha que fazer 'if/else'
// toda vez que quiser imprimir o nome do material. A própria classe sabe seu nome.
// ==================================================================================
std::string Material::getNomeTipo() {
    switch(this->tipo) {
        case 1: return "Plastico";
        case 2: return "Papel";
        case 3: return "Metal";
        default: return "Indefinido"; // Caso de segurança
    }
}

// ==================================================================================
// SETTERS 
// ==================================================================================
void Material::setPeso(float pe) {
    this->peso = pe;
}

void Material::setTipo(int t) {
    this->tipo = t;
}