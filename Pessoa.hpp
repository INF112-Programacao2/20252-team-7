#ifndef PESSOA_HPP // [Pré-processador] Evita inclusão circular
#define PESSOA_HPP

#include <string>
#include "material.hpp"

// ==================================================================================
// CLASSE PESSOA (Classe Base / Superclasse)
// ----------------------------------------------------------------------------------
// [POO - Herança]
// Esta classe serve de molde para 'Catador' e 'Colaborador'.
// Ela contém os atributos que são COMUNS a todos os usuários do sistema.
// ==================================================================================
class Pessoa {
    
// ==================================================================================
// ÁREA PRIVADA (Private)
// ==================================================================================
private:
    std::string _nome;
    std::string _endereco;
    std::string _cpf;
    
    // [Memória - Ponteiro]
    // Usamos 'Material*' (ponteiro) em vez de 'Material' (objeto estático).
    // Motivo: Isso nos permite alocar o material dinamicamente na memória Heap
    // e controlar o tempo de vida dele manualmente (ou trocá-lo facilmente).
    // Relação: Pessoa "TEM UM" Material (Associação).
    Material* _material;

public:
    // Construtor: Inicializa os atributos quando o objeto nasce.
    // O parâmetro 'material' tem valor padrão nullptr (opcional).
    Pessoa(std::string nome, std::string endereco, std::string cpf, Material* material = nullptr);
    
    // ==============================================================================
    // DESTRUTOR VIRTUAL
    // ------------------------------------------------------------------------------
    // [POO - Polimorfismo]
    // A palavra-chave 'virtual' aqui é obrigatória quando usamos herança.
    // Cenário: Imagine que temos um ponteiro genérico 'Pessoa* p = new Catador();'.
    // Se fizermos 'delete p', o compilador precisa saber que deve chamar primeiro o
    // destrutor do Catador e depois o da Pessoa.
    // SEM 'virtual': O programa chamaria apenas ~Pessoa(), e o que fosse específico
    // do Catador ficaria preso na memória (Vazamento).
    // COM 'virtual': O programa sabe descer na hierarquia e destruir tudo corretamente.
    // ==============================================================================
    virtual ~Pessoa(); 
    
    // [Interface Pública] Getters (Acessores)
    // O 'const' no final garante que esses métodos apenas leem dados, sem modificar nada.
    std::string getNome() const;
    std::string getEndereco() const;
    std::string getCpf() const;
    Material* getMaterial() const;
    
    // [Interface Pública] Setters (Modificadores)
    void setNome(std::string nome);
    void setEndereco(std::string endereco);
    void setCpf(std::string cpf);
    
    // [Gerenciamento de Memória]
    // Ao definir um novo material, a implementação deste método (.cpp)
    // será responsável por verificar se já existia um anterior e deletá-lo (delete)
    // para evitar vazamento de memória antes de apontar para o novo.
    void setMaterial(Material* material);
    
    // Método utilitário para alterar propriedades do material interno
    void definirMaterial(Material* mat, float p, int t);
};

#endif