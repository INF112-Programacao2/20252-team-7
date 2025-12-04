#include "Pessoa.hpp"
#include <iostream>

// ==================================================================================
// CONSTRUTOR
// ----------------------------------------------------------------------------------
// [POO] Inicialização de Objetos.
// Utilizamos a "Lista de Inicialização" (: _nome(nome), ...) que é mais eficiente
// do que fazer atribuições dentro das chaves { }.
// ==================================================================================
Pessoa::Pessoa(std::string nome, std::string endereco, std::string cpf, Material* material)
    : _nome(nome), _endereco(endereco), _cpf(cpf), _material(material) {}

// ==================================================================================
// DESTRUTOR VIRTUAL 
// ----------------------------------------------------------------------------------
// 1. Verificamos se _material aponta para algo (_material != nullptr).
// 2. Se aponta, usamos 'delete' para liberar o espaço na Heap.
// 3. Zeramos o ponteiro para evitar que ele aponte para lixo.
// ==================================================================================
Pessoa::~Pessoa() {
    if (_material != nullptr) {
        delete _material; // [Memória] Libera a memória RAM alocada dinamicamente
        _material = nullptr;
    }
}

// ==================================================================================
// GETTERS
// ----------------------------------------------------------------------------------
// [POO - Encapsulamento]
// Retornam os valores dos atributos privados para o mundo externo.
// O 'const' garante que chamar esses métodos não altera o objeto.
// ==================================================================================
std::string Pessoa::getNome() const { return _nome; }
std::string Pessoa::getEndereco() const { return _endereco; }
std::string Pessoa::getCpf() const { return _cpf; }
Material* Pessoa::getMaterial() const { return _material; }

// ==================================================================================
// SETTERS 
// ----------------------------------------------------------------------------------
// Permitem alterar os atributos privados de forma controlada.
// ==================================================================================
void Pessoa::setNome(std::string nome) { _nome = nome; }
void Pessoa::setEndereco(std::string endereco) { _endereco = endereco; }
void Pessoa::setCpf(std::string cpf) { _cpf = cpf; }

// ==================================================================================
// SETTER COMPLEXO (Gerenciamento de Memória)
// ----------------------------------------------------------------------------------
// [Memória - Prevenção de Vazamento]
// Este setter é especial. Não podemos simplesmente fazer '_material = material'.
// Por quê?
// Se _material já estivesse apontando para um objeto na memória (ex: Plástico),
// e nós simplesmente sobrescrevêssemos o ponteiro com um novo (ex: Papel),
// perderíamos o endereço do Plástico. Ele ficaria ocupando memória RAM para sempre
// e nós nunca mais conseguiríamos deletá-lo.
//
// Solução:
// 1. Verifica se já existe um material antigo.
// 2. Se existir, DELETA o antigo primeiro.
// 3. Só então atribui o novo.
// ==================================================================================
void Pessoa::setMaterial(Material* material) { 
    if (_material != nullptr) {
        delete _material; // [Memória] Limpa o antigo antes de receber o novo
    }
    _material = material; 
}

// Método utilitário para alterar propriedades do material existente
void Pessoa::definirMaterial(Material* mat, float p, int t) {
    if (mat) {
        mat->setPeso(p);
        mat->setTipo(t);
    }
}