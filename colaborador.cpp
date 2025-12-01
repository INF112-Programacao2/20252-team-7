#include "colaborador.hpp"
#include <iostream>
#include <fstream>  // Necessário para ler/escrever arquivos (File I/O)
#include <vector>   // Container da STL para armazenar linhas do arquivo dinamicamente
#include <sstream>  // Necessário para construção de strings (stringstream)
#include <iomanip>  // Necessário para formatar números (setprecision)

// ==================================================================================
// CONSTRUTORES
// ==================================================================================

// Construtor de Cópia: Cria um Colaborador a partir de uma Pessoa existente
Colaborador::Colaborador(const Pessoa& pessoa) : Pessoa(pessoa), pontos(0) {}

// Construtor Completo
Colaborador::Colaborador(std::string nome, std::string endereco, std::string cpf, Material* material)
    : Pessoa(nome, endereco, cpf, material), pontos(0) {}

// [Memória] Destrutor
Colaborador::~Colaborador() {}

// ==================================================================================
// GETTERS E SETTERS
// ==================================================================================
int Colaborador::getPontos() const { return pontos; }
void Colaborador::setPontos(int p) { pontos = p; }

// ==================================================================================
// PERSISTÊNCIA: CADASTRO INICIAL
// ==================================================================================
void Colaborador::cadastro(std::string nome, std::string endereco, std::string cpf, Material* material) {
    std::ofstream arq("cadastro_colaborador.txt", std::ios::app);
    
    if (arq.is_open()) {
        arq << "Nome: " << nome << "\nEndereço: " << endereco << "\nCPF: " << cpf << "\n";
        
        // Formatação visual para o arquivo
        if (material) {
            arq << "Material: " << std::fixed << std::setprecision(2) << material->getPeso() 
                << "kg de " << material->getNomeTipo() << "\n";
        } else {
            arq << "Material: Nenhum (Cadastro Inicial)\n";
        }
        
        arq << "Pontos: 0\n------------------------\n";
        arq.close(); // [File I/O] Sempre fechar o arquivo!
        std::cout << "Colaborador cadastrado com sucesso!\n";
    }
}

// ==================================================================================
// LÓGICA DE NEGÓCIO: REALIZAR DOAÇÃO (Gamificação)
// ----------------------------------------------------------------------------------
// Este método encapsula a regra de negócio mais importante do Colaborador.
// Ele recebe um ponteiro para um Material (criado na Heap pelo Controller),
// calcula os pontos baseados no tipo e peso, e dispara a atualização dos arquivos.
// ==================================================================================
void Colaborador::realizarDoacao(Material* m) {
    // Validação básica
    if (!m || m->getPeso() <= 0) return;

    // Definição de Multiplicadores
    // Usamos 'switch' para mapear o Tipo (int) para um fator de multiplicação.
    int multiplicador = 0;
    switch (m->getTipo()) {
        case 1: multiplicador = 3; break; // Plastico vale 3x
        case 2: multiplicador = 2; break; // Papel vale 2x
        case 3: multiplicador = 4; break; // Metal vale 4x 
        default: multiplicador = 1; break;
    }

    // Cálculo: Peso * Multiplicador
    // static_cast<int> converte o resultado float para int 
    int pontosGanhos = static_cast<int>(m->getPeso() * multiplicador);
    
    // Atualiza o estado do objeto em memória
    this->pontos += pontosGanhos;
    
    // Feedback para o usuário
    std::cout << "\n=== DOACAO REALIZADA ===\n";
    std::cout << "Material: " << m->getNomeTipo() << " (" << m->getPeso() << "kg)\n";
    std::cout << "Regra: x" << multiplicador << " pontos/kg\n";
    std::cout << "Pontos ganhos: " << pontosGanhos << "\n";
    
    // Salva o novo saldo de pontos no arquivo
    salvarPontosNoArquivo();
    
    // Atualiza o estoque de materiais no arquivo (Soma acumulativa)
    adicionarMaterialAoArquivo(m);
}

// Método simples para dar pontos fixos (ex: Bônus de boas-vindas)
void Colaborador::receberPontos(int valor) {
    this->pontos += valor;
    std::cout << ">> Bonus recebido: +" << valor << " pontos!\n";
    salvarPontosNoArquivo();
}

// ==================================================================================
// ADICIONAR MATERIAL 
// ----------------------------------------------------------------------------------
// [Algoritmo de Manipulação de Arquivo]
// Esta função é complexa. Ela precisa ler o arquivo linha por linha, encontrar o
// usuário correto (pelo CPF), verificar se ele já tem aquele tipo de material e,
// se tiver, somar o novo peso ao antigo. Se não tiver, criar uma nova linha.
// ==================================================================================
void Colaborador::adicionarMaterialAoArquivo(Material* m) {
    std::ifstream leitura("cadastro_colaborador.txt");
    std::vector<std::string> linhas; // Vetor para guardar o arquivo inteiro na RAM
    std::string linha;
    
    std::string cpfAlvo = "CPF: " + this->getCpf();
    std::string nomeTipo = m->getNomeTipo(); // Ex: "Plastico"
    
    bool usuarioEncontrado = false;
    bool materialAtualizado = false;
    
    if (!leitura.is_open()) return;

    // 1. LEITURA E MODIFICAÇÃO EM MEMÓRIA
    while (std::getline(leitura, linha)) {
        // Verifica se entramos no bloco deste usuário
        if (linha.find(cpfAlvo) != std::string::npos) {
            usuarioEncontrado = true;
        }

        // Se estamos dentro do bloco do usuário correto
        if (usuarioEncontrado) {
            
            // Cenário A: O usuário tem "Material: Nenhum" (Primeira doação)
            // Ação: Substituímos essa linha pela linha do novo material.
            if (linha.find("Material: Nenhum") != std::string::npos) {
                std::stringstream ss;
                ss << "Material: " << std::fixed << std::setprecision(2) << m->getPeso() << "kg de " << nomeTipo;
                linhas.push_back(ss.str());
                materialAtualizado = true;
                continue; // Pula para a próxima linha do arquivo, já tratamos esta
            }

            // Cenário B: O usuário JÁ TEM uma linha com esse material (Ex: "10kg de Plastico")
            // Ação: Lemos o peso antigo, somamos com o novo e reescrevemos a linha.
            if (linha.find("Material:") != std::string::npos && linha.find(nomeTipo) != std::string::npos) {
                try {
                    // [Parser Manual]
                    // Encontra a posição dos delimitadores ":" e "kg"
                    size_t posDoisPontos = linha.find(":");
                    size_t posKg = linha.find("kg");
                    
                    // Extrai a substring numérica e converte para float
                    float pesoAntigo = std::stof(linha.substr(posDoisPontos + 1, posKg - (posDoisPontos + 1)));
                    
                    // Soma
                    float novoPeso = pesoAntigo + m->getPeso();
                    
                    // Reconstrói a linha
                    std::stringstream ss;
                    ss << "Material: " << std::fixed << std::setprecision(2) << novoPeso << "kg de " << nomeTipo;
                    linhas.push_back(ss.str());
                    materialAtualizado = true;
                    continue;
                } catch (...) {
                    // [Tratamento de Erro Silencioso]
                    // Se a linha estiver corrompida e o stof falhar, não fazemos nada aqui
                    // e deixamos o fluxo seguir. O sistema é resiliente.
                }
            }

            // Cenário C: O usuário tem materiais, mas não desse tipo específico.
            // Ação: Inserimos a nova linha de material ANTES da linha de Pontos.
            if (linha.find("Pontos:") != std::string::npos) {
                if (!materialAtualizado) {
                    std::stringstream ss;
                    ss << "Material: " << std::fixed << std::setprecision(2) << m->getPeso() << "kg de " << nomeTipo;
                    linhas.push_back(ss.str());
                    materialAtualizado = true;
                }
            }
            
            // Fim do bloco do usuário (linha tracejada)
            if (linha.find("------------------------") != std::string::npos) {
                usuarioEncontrado = false;
                materialAtualizado = false; // Reseta flags para não afetar outros usuários
            }
        }
        
        // Se a linha não foi modificada pelos cenários acima, copia ela igual para o vetor.
        linhas.push_back(linha);
    }
    leitura.close();

    // 2. ESCRITA (DUMP)
    // Reescreve o arquivo inteiro com o conteúdo do vetor 'linhas'.
    std::ofstream escrita("cadastro_colaborador.txt");
    for (const auto& l : linhas) {
        escrita << l << "\n";
    }
    escrita.close();
}

// ==================================================================================
// CARREGAR PONTOS
// ----------------------------------------------------------------------------------
// [Gestão de Estado]
// Ao logar, lemos o arquivo para saber quantos pontos o usuário tem acumulados.
// ==================================================================================
void Colaborador::carregarPontos() {
    std::ifstream arquivo("cadastro_colaborador.txt");
    std::string linha;
    std::string cpfAlvo = "CPF: " + this->getCpf();
    bool u = false;
    
    if(!arquivo.is_open()) return;
    
    while(std::getline(arquivo, linha)){
        if(linha.find(cpfAlvo)!=std::string::npos) u=true;
        
        if(u && linha.find("Pontos: ")!=std::string::npos){
            try{ 
                // Converte string para int
                this->pontos = std::stoi(linha.substr(8)); 
            } catch(...){ 
                this->pontos = 0; 
            }
            break; // Achou, pode parar
        }
        if(u && linha.find("------------------------")!=std::string::npos) break;
    }
    arquivo.close();
}

// Salva apenas a alteração de pontos no arquivo (sem mexer nos materiais)
void Colaborador::salvarPontosNoArquivo() {
    std::ifstream l("cadastro_colaborador.txt");
    std::vector<std::string> ls;
    std::string line;
    std::string cpf = "CPF: " + this->getCpf();
    bool u=false, done=false;
    
    while(std::getline(l, line)){
        if(line.find(cpf)!=std::string::npos) u=true;
        
        // Se achou a linha de pontos do usuário logado, substitui pelo valor da memória RAM
        if(u && line.find("Pontos: ")!=std::string::npos && !done){
            ls.push_back("Pontos: " + std::to_string(this->pontos));
            done=true;
        } else if(line.find("------------------------")!=std::string::npos) {
            u=false; ls.push_back(line);
        } else ls.push_back(line);
    }
    l.close();
    
    std::ofstream e("cadastro_colaborador.txt");
    for(const auto& s : ls) e<<s<<"\n";
    e.close();
}

// Apenas exibe o conteúdo do arquivo de cooperativas 
void Colaborador::visualizarCooperativas() {
    std::ifstream f("cadastro_cooperativa.txt");
    std::string l;
    std::cout << "\n=== COOPERATIVAS ===\n";
    while(std::getline(f, l)) std::cout << l << "\n";
    f.close();
}