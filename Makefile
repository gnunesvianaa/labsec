# variables
OBJS = main/main.o convert_hex_to_base64/convert_hex_to_base64.o fixed_xor/fixed_xor.o single_byte_xor_cipher/single_byte_xor_cipher.o detect_single_character_xor/detect_single_character_xor.o implement_repeating_key_xor/implement_repeating_key_xor.o break_repeating_key_xor/break_repeating_key_xor.o
OUTPUT = output
CXX = g++
CXXFLAGS = -std=c++17

# compile from o to output
$(OUTPUT): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(OUTPUT)

# compile from cpp to o
%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(OUTPUT)
	@./$(OUTPUT)

clean:
	@rm -f $(OBJS) $(OUTPUT)
