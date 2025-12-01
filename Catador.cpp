#include "Catador.hpp"
#include <iostream>
#include <fstream>  // [Persistência] Biblioteca para leitura/escrita de arquivos
#include <vector>   // [Memória] Biblioteca STL para vetores dinâmicos
#include <string>

// ==================================================================================
// CONSTRUTOR DE CÓPIA
// Este construtor recebe um objeto 'Pessoa' genérico e o "promove" a Catador.
// A sintaxe ': Pessoa(pessoa)' chama o construtor de cópia da classe base,
// copiando nome, cpf e endereço. Em seguida, inicializamos o saldo com 0.
// ==================================================================================
Catador::Catador(const Pessoa& pessoa) : Pessoa(pessoa), _saldo(0.0f) {}

// ==================================================================================
// CONSTRUTOR PADRÃO (Parametrizado)
// ----------------------------------------------------------------------------------
// [POO - Inicialização em Cadeia]
// Recebemos os dados brutos e repassamos imediatamente para o construtor da 
// classe Pessoa (: Pessoa(nome...)). Isso evita duplicar a lógica de atribuição.
// ==================================================================================
Catador::Catador(std::string nome, std::string endereco, std::string cpf, Material* material)
    : Pessoa(nome, endereco, cpf, material), _saldo(0.0f) {}

// ==================================================================================
// DESTRUTOR
// ----------------------------------------------------------------------------------
// [Memória]
// ==================================================================================
Catador::~Catador() {}

// ==================================================================================
// GETTERS E SETTERS
// ==================================================================================
float Catador::getSaldo() const { return _saldo; }
void Catador::setSaldo(float valor) { _saldo = valor; }

// ==================================================================================
// RECOLHER MATERIAL
// ----------------------------------------------------------------------------------
// Usamos 'this->getMaterial()' porque o atributo '_material' é privado na classe Pessoa.
// Não podemos acessar '_material' diretamente aqui, temos que pedir ao método público da mãe.
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
// std::ios::app (Append): Abre o arquivo e posiciona o cursor no final.
// Isso garante que não vamos apagar os catadores que já foram cadastrados antes.
// ==================================================================================
void Catador::cadastro(std::string nome, std::string endereco, std::string cpf, Material* material) {
    std::ofstream arquivo("cadastro_catador.txt", std::ios::app);
    
    if (arquivo.is_open()) {
        arquivo << "Nome: " << nome << "\nEndereço: " << endereco << "\nCPF: " << cpf << "\n";
        
        // Lógica condicional para escrita formatada
        if (material) {
            arquivo << "Material: " << material->getPeso() << "kg de " << material->getNomeTipo() << "\n";
        } else {
            arquivo << "Material: Nenhum (Cadastro Inicial)\n";
        }
        
        arquivo << "Saldo: R$ " << _saldo << "\n------------------------\n";
        arquivo.close(); // Sempre liberar o recurso do sistema operacional
        std::cout << "Catador cadastrado com sucesso!\n";
    }
}

// ==================================================================================
// ATUALIZAR SALDO
// ----------------------------------------------------------------------------------
// Arquivos de texto sequenciais não permitem editar uma linha no meio facilmente.
// A estratégia padrão é:
// 1. Ler TUDO para a memória.
// 2. Modificar a linha desejada na memória.
// 3. Reescrever o arquivo inteiro com os dados novos.
// ==================================================================================
void Catador::adicionarSaldoAoArquivo(float valorAdicionado) {
    std::ifstream leitura("cadastro_catador.txt"); // Modo Leitura
    std::vector<std::string> linhas; // Vetor dinâmico para guardar o arquivo
    std::string linha;
    
    std::string cpfAlvo = "CPF: " + this->getCpf();
    bool encontrouUsuario = false;
    bool saldoAtualizado = false; // Flag para garantir que só alteramos o saldo deste usuário

    if (!leitura.is_open()) {
        std::cout << "Erro: Base de dados de catadores nao encontrada.\n";
        return;
    }

    // Carregar arquivo 
    while (std::getline(leitura, linha)) {
        // Verifica se entramos no bloco do usuário correto
        if (linha.find(cpfAlvo) != std::string::npos) {
            encontrouUsuario = true;
        }

        // Se estamos no bloco do usuário e achamos a linha de saldo
        if (encontrouUsuario && linha.find("Saldo: R$ ") != std::string::npos && !saldoAtualizado) {
            try {
                // 'substr(10)' pega tudo depois de "Saldo: R$ "
                // 'stof' converte esse texto para número float
                float saldoAntigo = std::stof(linha.substr(10));
                float novoSaldo = saldoAntigo + valorAdicionado;
                
                // Cria a nova string atualizada
                std::string novaLinha = "Saldo: R$ " + std::to_string(novoSaldo);
                linhas.push_back(novaLinha);
                
                // Atualiza também o objeto na memória RAM para refletir a mudança imediata
                this->_saldo = novoSaldo;
                saldoAtualizado = true; // Marca como feito para não alterar outros saldos
            } catch (...) {
                // [Tratamento de Erro] Se falhar a conversão, mantém a linha original para não corromper
                linhas.push_back(linha); 
            }
        } 
        else if (linha.find("------------------------") != std::string::npos) {
            // Se chegou na linha tracejada, acabou o bloco deste usuário
            if (encontrouUsuario) {
                encontrouUsuario = false;
                saldoAtualizado = false;
            }
            linhas.push_back(linha);
        }
        else {
            // Qualquer outra linha (Nome, Endereço) é apenas copiada
            linhas.push_back(linha);
        }
    }
    leitura.close();

    // Reescrever o arquivo 
    // std::ofstream sem 'ios::app' apaga o arquivo atual e cria um novo vazio (Truncate)
    std::ofstream escrita("cadastro_catador.txt");
    for (const auto& l : linhas) {
        escrita << l << "\n";
    }
    escrita.close();
}

// ==================================================================================
// GESTÃO DE ESTADO: CARREGAR SALDO
// ----------------------------------------------------------------------------------
// Este método vai no arquivo, busca o valor real e atualiza a variável '_saldo'.
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

        // Se achou o usuário e a linha de saldo
        if (usuarioEncontrado && linha.find("Saldo: R$ ") != std::string::npos) {
            try {
                // Converte string para float e guarda no atributo privado
                this->_saldo = std::stof(linha.substr(10));
            } catch (...) {
                this->_saldo = 0.0f;
            }
            break; // Otimização: Já achou o que queria, para de ler o arquivo
        }

        if (usuarioEncontrado && linha.find("------------------------") != std::string::npos) {
            break; // Fim do bloco
        }
    }
    arquivo.close();
}

void Catador::visualizarCooperativas() {
    std::cout << "\n=== COOPERATIVAS DISPONIVEIS ===\n";
    std::ifstream arquivo("cadastro_cooperativa.txt");
    std::string linha;
    
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::cout << linha << "\n";
        }
        arquivo.close();
    }
}