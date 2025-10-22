#ifndef CATADOR_HPP
#define CATADOR_HPP

#include "Pessoa.hpp"
#include "colaborador.hpp"

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
		void cadastro(std::string nome, std::string endereco, int cpf, Material material, float saldo);
};

#endif;