#ifndef CATADOR_HPP
#define CATADOR_HPP

#include "Pessoa.hpp"
#include "material.hpp" //deveria ser material e não catador (?)

class Catador : public Pessoa {
    private:
        float _saldo;
    public:
        //Construtor e destrutor.
        Catador( Pessoa pessoa );
        ~Catador( );

        //Função get
        float getSaldo( );

        //Função set
        void setSaldo( float valor );

        //Outras funções
        void recolherMaterial( Material material );
		void cadastro(std::string nome, std::string endereco, std::string cpf, Material material, float saldo);
};

#endif //!!!!!!!!
