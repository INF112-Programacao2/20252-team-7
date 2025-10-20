#include "Pessoa.hpp"
#include "material.hpp"
#include <string>

//Construtor
Pessoa::Pessoa( std::string nome, std::string endereco, int cpf, Material material ) :
    _nome( nome ), _endereco( endereco ), _cpf( cpf ), _material( material ) { };

Pessoa::~Pessoa( ) { };

//Funções get
std::string Pessoa::getNome( ) {
    return this->_nome;
}
std::string Pessoa::getEndereco( ) {
    return this->_endereco;
}
int Pessoa::getCpf( ) {
    return this->_cpf;
}
Material Pessoa::getMaterial( ) {
    return this->_material;
}

//Funções set
void Pessoa::setNome( std::string novoNome ) {
    this->_nome = novoNome;
}
void Pessoa::setEndereco( std::string novoEndereco ) {
    this->_endereco = novoEndereco;
}
void Pessoa::setMaterial( Material novoMaterial ) {
    this->_material = novoMaterial;
}

//Métodos
virtual void Pessoa::cadastro(Material mat, float p, int t) {
    mat.setPeso(p);
	mat.setTipo(t);
}