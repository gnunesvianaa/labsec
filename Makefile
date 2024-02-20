# variables
OBJS = main.o ex01/ex01.o ex02/ex02.o ex03/ex03.o ex04/ex04.o ex05/ex05.o ex06/ex06.o
OUTPUT = output
CXX = g++
CXXFLAGS = -std=c++17

# compile from o to output
$(OUTPUT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(OUTPUT)

# compile from cpp to o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -f $(OBJS) $(OUTPUT)
