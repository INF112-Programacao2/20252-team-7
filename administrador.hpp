#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include <iostream>
#include <string>
#include <vector>

class Administrador {
public:
    Administrador();
    ~Administrador();
    
    void acessarSistemaRegistro();
    void visualizarColaboradores();
    void visualizarCooperativas();
    void visualizarCatadores();
    void relatorioTotalMaterial();
};

#endif