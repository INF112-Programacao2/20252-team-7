#include "Catador.hpp"
#include <iostream>
#include <fstream>  // [Persistência] Biblioteca para manipulação de arquivos (File I/O)
#include <vector>   // [Memória] Biblioteca STL para vetores dinâmicos (arrays que crescem)
#include <string>

// ==================================================================================
// CONSTRUTOR DE CÓPIA
// Este construtor permite criar um Catador a partir de um objeto Pessoa genérico.
// A sintaxe ': Pessoa(pessoa)' chama o construtor de cópia da classe base,
// copiando automaticamente nome, cpf, endereço e o ponteiro do material.
// Em seguida, inicializamos o atributo específico '_saldo' com 0.0f.
// ==================================================================================
Catador::Catador(const Pessoa& pessoa) : Pessoa(pessoa), _saldo(0.0f) {}

// ==================================================================================
// CONSTRUTOR PADRÃO (Parametrizado)
// ----------------------------------------------------------------------------------
// Recebemos os dados brutos e os repassamos imediatamente para o construtor da 
// classe Pessoa via lista de inicialização (: Pessoa(...)).
// Isso é mais eficiente do que atribuir manualmente dentro das chaves { }.
// ==================================================================================
Catador::Catador(std::string nome, std::string endereco, std::string cpf, Material* material)
    : Pessoa(nome, endereco, cpf, material), _saldo(0.0f) {}

// ==================================================================================
// DESTRUTOR
// ==================================================================================
Catador::~Catador() {}

// ==================================================================================
// GETTERS E SETTERS
// ==================================================================================
float Catador::getSaldo() const { return _saldo; }
void Catador::setSaldo(float valor) { _saldo = valor; }

// ==================================================================================
// LÓGICA DE NEGÓCIO: RECOLHER MATERIAL
// ----------------------------------------------------------------------------------
// Simula a ação de adicionar peso ao material que o catador já carrega.
// Note o uso de 'this->getMaterial()'. Como o atributo '_material' é privado na 
// classe Pessoa, o Catador (filho) precisa pedir acesso via método público (getter).
// ==================================================================================
void Catador::recolherMaterial(Material* material) {
    if (material && this->getMaterial()) {
        float novoPeso = this->getMaterial()->getPeso() + material->getPeso();
        this->getMaterial()->setPeso(novoPeso);
        std::cout << "Material recolhido! Novo peso: " << novoPeso << "kg\n";
    }
}

// ==================================================================================
// CADASTRO INICIAL
// ----------------------------------------------------------------------------------
// Abre o arquivo em modo 'append' (std::ios::app). Isso significa que o cursor
// de escrita é posicionado no final do arquivo, preservando os dados antigos.
// ==================================================================================
void Catador::cadastro(std::string nome, std::string endereco, std::string cpf, Material* material) {
    std::ofstream arquivo("cadastro_catador.txt", std::ios::app);
    
    if (arquivo.is_open()) {
        arquivo << "Nome: " << nome << "\nEndereço: " << endereco << "\nCPF: " << cpf << "\n";
        
        // Lógica condicional para formatar a saída
        if (material) {
            arquivo << "Material: " << material->getPeso() << "kg de " << material->getNomeTipo() << "\n";
        } else {
            arquivo << "Material: Nenhum (Cadastro Inicial)\n";
        }
        
        arquivo << "Saldo: R$ " << _saldo << "\n------------------------\n";
        arquivo.close(); // [Boa Prática] Sempre liberar o recurso do sistema operacional.
        std::cout << "Catador cadastrado com sucesso!\n";
    }
}

// ==================================================================================
// ATUALIZAR SALDO 
// ----------------------------------------------------------------------------------
// Arquivos de texto (.txt) não permitem editar uma linha específica facilmente,
// pois mudar "10" para "100" empurraria todos os caracteres seguintes.
// A Estratégia de Update usada aqui é:
// 1. Ler TODO o arquivo para a memória RAM (usando um vector<string>).
// 2. Encontrar e modificar a linha desejada na memória.
// 3. Apagar o arquivo antigo e reescrever tudo com os dados novos.
// ==================================================================================
void Catador::adicionarSaldoAoArquivo(float valorAdicionado) {
    std::ifstream leitura("cadastro_catador.txt"); // Modo Leitura
    std::vector<std::string> linhas; // Vetor dinâmico para armazenar o arquivo temporariamente
    std::string linha;
    
    std::string cpfAlvo = "CPF: " + this->getCpf();
    bool encontrouUsuario = false;
    bool saldoAtualizado = false; // Flag de controle

    if (!leitura.is_open()) {
        std::cout << "Erro: Base de dados de catadores nao encontrada.\n";
        return;
    }

    // Carregar e Modificar
    while (std::getline(leitura, linha)) {
        // Verifica se entramos no bloco de dados deste usuário (pelo CPF)
        if (linha.find(cpfAlvo) != std::string::npos) {
            encontrouUsuario = true;
        }

        // Se estamos no bloco certo E achamos a linha de saldo...
        if (encontrouUsuario && linha.find("Saldo: R$ ") != std::string::npos && !saldoAtualizado) {
            try {
                // Extrai o valor numérico (substring após o texto fixo)
                float saldoAntigo = std::stof(linha.substr(10));
                float novoSaldo = saldoAntigo + valorAdicionado;
                
                // Reconstrói a linha com o novo valor
                std::string novaLinha = "Saldo: R$ " + std::to_string(novoSaldo);
                linhas.push_back(novaLinha);
                
                // Atualiza também o objeto na RAM para feedback imediato
                this->_saldo = novoSaldo;
                saldoAtualizado = true; // Garante que não altere saldos de homônimos ou erros
            } catch (...) {
                // Se falhar a conversão, mantém a linha original
                linhas.push_back(linha); 
            }
        } 
        else if (linha.find("------------------------") != std::string::npos) {
            // Fim do bloco deste usuário
            if (encontrouUsuario) {
                encontrouUsuario = false;
                saldoAtualizado = false;
            }
            linhas.push_back(linha);
        }
        else {
            // Linhas que não precisam de alteração são apenas copiadas
            linhas.push_back(linha);
        }
    }
    leitura.close();

    //Reescrever
    // std::ofstream sem 'ios::app' trunca (apaga) o arquivo existente
    std::ofstream escrita("cadastro_catador.txt");
    for (const auto& l : linhas) {
        escrita << l << "\n";
    }
    escrita.close();
}

// ==================================================================================
// GESTÃO DE ESTADO: CARREGAR SALDO
// ----------------------------------------------------------------------------------
// começa com saldo 0. Este método lê o arquivo para buscar o saldo real acumulado.
// ==================================================================================
void Catador::carregarSaldo() {
    std::ifstream arquivo("cadastro_catador.txt");
    std::string linha;
    std::string cpfAlvo = "CPF: " + this->getCpf();
    bool usuarioEncontrado = false;

    if (!arquivo.is_open()) return;

    while (std::getline(arquivo, linha)) {
        if (linha.find(cpfAlvo) != std::string::npos) {
            usuarioEncontrado = true;
        }

        if (usuarioEncontrado && linha.find("Saldo: R$ ") != std::string::npos) {
            try {
                // Converte string do arquivo para float na memória
                this->_saldo = std::stof(linha.substr(10));
            } catch (...) {
                this->_saldo = 0.0f;
            }
            break; // Otimização: Já achou, para de ler.
        }

        if (usuarioEncontrado && linha.find("------------------------") != std::string::npos) {
            break;
        }
    }
    arquivo.close();
}

void Catador::visualizarCooperativas() {
    std::cout << "\n=== COOPERATIVAS DISPONIVEIS ===\n";
    std::ifstream arquivo("cadastro_cooperativa.txt");
    std::string linha;
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) std::cout << linha << "\n";
        arquivo.close();
    }
}

// ==================================================================================
// VISUALIZAR COLABORADORES (Modo Privacidade)
// ----------------------------------------------------------------------------------
// [Lógica de Filtro e Privacidade]
// O Catador precisa saber onde buscar material (Endereço) e o quê tem lá (Material),
// mas não precisa saber o nome do morador.
// Este método lê o arquivo de colaboradores e imprime apenas os dados relevantes.
// ==================================================================================
void Catador::visualizarColaboradores() {
    std::ifstream arquivo("cadastro_colaborador.txt");
    if (!arquivo.is_open()) {
        std::cout << "Nenhum colaborador cadastrado.\n";
        return;
    }

    std::string linha;
    std::string enderecoAtual;
    std::vector<std::string> materiaisAtuais; // Armazena lista de itens temporariamente
    
    std::cout << "\n=============================================\n";
    std::cout << "   PONTOS DE COLETA (Enderecos e Materiais)  \n";
    std::cout << "=============================================\n";

    while (std::getline(arquivo, linha)) {
        // 1. Identifica Endereço (Pula "Endereço: " que tem 10 chars + encoding)
        if (linha.find("Endereço: ") == 0) {
            enderecoAtual = linha.substr(10); 
        }
        // 2. Identifica Materiais (Ignora se for "Nenhum")
        else if (linha.find("Material: ") == 0) {
            if (linha.find("Nenhum") == std::string::npos) {
                materiaisAtuais.push_back(linha.substr(10)); // Guarda só a descrição
            }
        }
        // 3. Fim do bloco de um usuário -> Processa e Imprime
        else if (linha.find("------------------------") != std::string::npos) {
            // Só exibe se houver materiais úteis para coleta
            if (!materiaisAtuais.empty() && !enderecoAtual.empty()) {
                std::cout << ">> LOCAL: " << enderecoAtual << "\n";
                std::cout << "   DISPONIVEL:\n";
                for (const auto& mat : materiaisAtuais) {
                    std::cout << "   - " << mat << "\n";
                }
                std::cout << "---------------------------------------------\n";
            }
            
            // Reseta variáveis para ler o próximo usuário do arquivo
            enderecoAtual = "";
            materiaisAtuais.clear();
        }
    }
    arquivo.close();
}