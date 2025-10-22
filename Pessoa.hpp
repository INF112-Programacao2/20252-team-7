#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <string>
#include "material.hpp"

class Pessoa {
    private:
        std::string _nome;
        std::string _endereco;
        const int _cpf;
        Material _material;
    public:
        Pessoa( std::string nome, std::string endereco, int cpf, Material material ); //Construtor
        ~Pessoa( );//Destrutor
    
        //Funções get
        std::string getNome( );
        std::string getEndereco( );
        int getCpf( );
        Material getMaterial( );

        //Funções set
        void setNome( std::string nome );
        void setEndereco( std::string endereco );
        void setMaterial( Material material );

        //Métodos
		virtual void definirMaterial(Material, float, int);
        void cadastro(std::string, std::string, int, Material);
};

#endif;