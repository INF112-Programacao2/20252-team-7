#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <string>
#include "material.hpp"

class Pessoa {
    private:
        std::string _nome;
        std::string _endereco;
        std::string _cpf; // luis: int para string
        Material _material;
    public:
        Pessoa( std::string nome, std::string endereco, int cpf, Material material ); //Construtor
        ~Pessoa( );//Destrutor
    
        //Funções get
        std::string getNome( );
        std::string getEndereco( );
        std::string getCpf( ); //luis: int para string
        Material getMaterial( );

        //Funções set
        void setNome(std::string nome);
	    void setEndereco(std::string endereco);
	    void setMaterial(Material material);

		//Métodos
	    void definirMaterial(Material mat, float p, int t);
	    void cadastro(std::string nome, std::string endereco, std::string cpf, Material material);

#endif //OBS: após o endif, NÃO UTILIZA-SE ";"
