#include "Pessoa.hpp"
#include "material.hpp"
#include <string>
#include <fstream>

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
std::string Pessoa::getCpf( ) {
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
virtual void Pessoa::definirMaterial(Material mat, float p, int t) {
    mat.setPeso(p);
    mat.setTipo(t);
}

void Pessoa::cadastro(std::string nome, std::string endereco, std::string cpf, Material material) {
	std::ofstream arquivo("cadastro.txt", std::ios::app);

    if (!arquivo.is_open()) {
		std::cerr << "Erro ao abrir o arquivo de cadastro." << std::endl;
        return; //obs:função void não retorna "1"
    }

    arquivo << nome << "," << endereco << "," << cpf << "," 
            << material.getPeso() << "," << material.getTipo();

	arquivo.close();
}
