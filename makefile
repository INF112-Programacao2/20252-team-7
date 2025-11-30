# Compilador
CXX = g++
# Flags de compilação
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -g
# Nome do executável principal
TARGET = programa
# Nome do executável de testes
TEST_TARGET = teste

# Arquivos fonte
SRCS = main.cpp material.cpp Pessoa.cpp Catador.cpp colaborador.cpp cooperativas.cpp
TEST_SRCS = main_test.cpp material.cpp Pessoa.cpp Catador.cpp colaborador.cpp cooperativas.cpp

# Arquivos objeto
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Regra principal
all: $(TARGET)

# Regra para o executável principal
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regra para o executável de testes
test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Regras para compilar cada arquivo objeto
main.o: main.cpp Pessoa.hpp material.hpp colaborador.hpp Catador.hpp cooperativas.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

main_test.o: main_test.cpp Pessoa.hpp material.hpp colaborador.hpp Catador.hpp cooperativas.hpp
	$(CXX) $(CXXFLAGS) -c main_test.cpp

material.o: material.cpp material.hpp
	$(CXX) $(CXXFLAGS) -c material.cpp

Pessoa.o: Pessoa.cpp Pessoa.hpp material.hpp
	$(CXX) $(CXXFLAGS) -c Pessoa.cpp

Catador.o: Catador.cpp Catador.hpp Pessoa.hpp material.hpp
	$(CXX) $(CXXFLAGS) -c Catador.cpp

colaborador.o: colaborador.cpp colaborador.hpp Pessoa.hpp material.hpp
	$(CXX) $(CXXFLAGS) -c colaborador.cpp

cooperativas.o: cooperativas.cpp cooperativas.hpp material.hpp Catador.hpp colaborador.hpp
	$(CXX) $(CXXFLAGS) -c cooperativas.cpp

administrador.o: administrador.cpp administrador.hpp
	g++ -Wall -Wextra -pedantic -std=c++11 -g -c administrador.cpp

# E atualize a linha do programa:
programa: main.o material.o Pessoa.o Catador.o colaborador.o cooperativas.o administrador.o
	g++ -Wall -Wextra -pedantic -std=c++11 -g -o programa main.o material.o Pessoa.o Catador.o colaborador.o cooperativas.o administrador.o
# Limpeza
clean:
	rm -f *.o $(TARGET) $(TEST_TARGET) cadastro.txt cadastro_catador.txt cadastro_colaborador.txt

# Executar o programa principal
run: $(TARGET)
	./$(TARGET)

# Executar testes
run-test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Debug com gdb
debug: $(TARGET)
	gdb ./$(TARGET)

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make all     - Compila o programa principal"
	@echo "  make test    - Compila os testes"
	@echo "  make run     - Executa o programa principal"
	@echo "  make run-test - Executa os testes"
	@echo "  make clean   - Remove arquivos gerados"
	@echo "  make debug   - Executa com debugger"
	@echo "  make help    - Mostra esta ajuda"

.PHONY: all clean run run-test debug help test
