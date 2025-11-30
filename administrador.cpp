#include "administrador.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>

Administrador::Administrador() {
    std::cout << "Administrador logado.\n";
}

Administrador::~Administrador() {}

void Administrador::acessarSistemaRegistro() {
    std::cout << "\n=== SISTEMA DE REGISTRO ===\n";
    std::cout << "Função de registro direto disponível nos menus de cada usuário.\n";
    std::cout << "Os usuários são cadastrados automaticamente ao tentarem logar.\n";
}

void Administrador::visualizarColaboradores() {
    std::cout << "\n=== COLABORADORES CADASTRADOS ===\n";
    std::ifstream arquivo("cadastro_colaborador.txt");
    std::string linha;
    
    if (!arquivo.is_open()) {
        std::cout << "Nenhum colaborador cadastrado.\n";
        return;
    }
    
    int count = 0;
    while (std::getline(arquivo, linha)) {
        std::cout << linha << std::endl;
        count++;
    }
    arquivo.close();
    
    if (count == 0) {
        std::cout << "Nenhum colaborador cadastrado.\n";
    }
}

void Administrador::visualizarCooperativas() {
    std::cout << "\n=== COOPERATIVAS CADASTRADAS ===\n";
    std::ifstream arquivo("cadastro_cooperativa.txt");
    std::string linha;
    
    if (!arquivo.is_open()) {
        std::cout << "Nenhuma cooperativa cadastrada.\n";
        return;
    }
    
    int count = 0;
    while (std::getline(arquivo, linha)) {
        std::cout << "Cooperativa: " << linha << std::endl;
        count++;
    }
    arquivo.close();
    
    if (count == 0) {
        std::cout << "Nenhuma cooperativa cadastrada.\n";
    }
}

void Administrador::visualizarCatadores() {
    std::cout << "\n=== CATADORES CADASTRADOS ===\n";
    std::ifstream arquivo("cadastro_catador.txt");
    std::string linha;
    
    if (!arquivo.is_open()) {
        std::cout << "Nenhum catador cadastrado.\n";
        return;
    }
    
    int count = 0;
    while (std::getline(arquivo, linha)) {
        std::cout << linha << std::endl;
        count++;
    }
    arquivo.close();
    
    if (count == 0) {
        std::cout << "Nenhum catador cadastrado.\n";
    }
}

void Administrador::relatorioTotalMaterial() {
    std::cout << "\n=== RELATÓRIO TOTAL DE MATERIAL ===\n";
    
    float totalPlastico = 0, totalPapel = 0, totalMetal = 0;
    
    // Ler colaboradores
    std::ifstream arqColab("cadastro_colaborador.txt");
    std::string linha;
    
    while (std::getline(arqColab, linha)) {
        if (linha.find("Material:") != std::string::npos) {
            // Extrair informações do material (simplificado)
            size_t posKg = linha.find("kg");
            if (posKg != std::string::npos) {
                // Buscar tipo na linha anterior ou seguinte
                std::string linhaTipo;
                std::getline(arqColab, linhaTipo);
                if (linhaTipo.find("tipo 1") != std::string::npos) {
                    totalPlastico += 10; // Valor exemplo
                } else if (linhaTipo.find("tipo 2") != std::string::npos) {
                    totalPapel += 10;
                } else if (linhaTipo.find("tipo 3") != std::string::npos) {
                    totalMetal += 10;
                }
            }
        }
    }
    arqColab.close();
    
    std::cout << "Plástico: " << totalPlastico << " kg\n";
    std::cout << "Papel: " << totalPapel << " kg\n";
    std::cout << "Metal: " << totalMetal << " kg\n";
    std::cout << "TOTAL: " << (totalPlastico + totalPapel + totalMetal) << " kg\n";
    
    // Ler histórico de compras
    std::cout << "\n=== HISTÓRICO DE COMPRAS ===\n";
    std::ifstream arqCompras("historico_compras.txt");
    if (arqCompras.is_open()) {
        while (std::getline(arqCompras, linha)) {
            std::cout << linha << std::endl;
        }
        arqCompras.close();
    } else {
        std::cout << "Nenhuma compra registrada.\n";
    }
}