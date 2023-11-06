# Variáveis
OBJS = main.o ex01/ex01.o ex02/ex02.o ex03/ex03.o ex04/ex04.o ex05/ex05.o ex06/ex06.o
OUTPUT = output
CXX = clang++
CXXFLAGS = -std=c++17

# Regra de compilação
$(OUTPUT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(OUTPUT)

# Regra para compilar arquivos .cpp em arquivos .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para executar o programa a partir do diretório abrir arquivos nos diretorios
run: $(OUTPUT)
	cd ~ && $(OUTPUT)

clean:
	rm -f $(OBJS) $(OUTPUT)
