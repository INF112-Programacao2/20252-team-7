#ifndef COOPERATIVAS_HPP
#define COOPERATIVAS_HPP
#include <iostream>
#include <string>

class Material;
class Catador;

class Cooperativas {
private:
    float precoPlastico;
    float precoPapel;
    float precoMetal;
    
    std::string cnpj;
    std::string endereco;
    Material* material;
    
public:
    Cooperativas();
    Cooperativas(float pPlastico, float pPapel, float pMetal, std::string cnpj, std::string endereco, Material* material);
    ~Cooperativas();

    float getPrecoPlastico();
    float getPrecoPapel();
    float getPrecoMetal();
    
    void setPrecos(float plastico, float papel, float metal);
    
    std::string getCnpj();
    std::string getEndereco();
    Material* getMaterial();
    void setCnpj(std::string);
    void setEndereco(std::string);
    void setMaterial(Material*);

    void comprarMaterial(Catador& catador, float peso);
    void cadastro(float pPlastico, float pPapel, float pMetal, std::string endereco, std::string cnpj, Material* material);
    
    void relatorioMaterialComprado();
    
    // MUDANÇA: Parâmetro agora representa o CPF
    void registrarCompra(const std::string& cpfCatador, float peso, float valorTotal, std::string nomeMaterial);
    
    void gerarRelatorioEstatistico(); 
    void visualizarCooperativas();
};

#endif