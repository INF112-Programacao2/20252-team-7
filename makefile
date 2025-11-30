CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 
TARGET = programa

# Lista TODOS os arquivos .cpp
SOURCES = \
    main.cpp \
    material.cpp \
    Pessoa.cpp \
    Catador.cpp \
    colaborador.cpp \
    cooperativas.cpp \
    administrador.cpp \
    InputHandler.cpp \
    SistemaController.cpp\
    Validacao.cpp\

# Gera automaticamente a lista de objetos
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Regra genérica para compilar qualquer .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run