# variables
OBJS = main/main.o utils/file_to_string.o utils/calcule_char_categories.o utils/hex_to_binary.o utils/hex_to_bytes.o convert_hex_to_base64/convert_hex_to_base64.o fixed_xor/fixed_xor.o single_byte_xor_cipher/single_byte_xor_cipher.o detect_single_character_xor/detect_single_character_xor.o implement_repeating_key_xor/implement_repeating_key_xor.o break_repeating_key_xor/break_repeating_key_xor.o aes_in_ecb_mode/aes_in_ecb_mode.o detect_aes_in_ecb_mode/detect_aes_in_ecb_mode.o
OUTPUT = output
CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lssl -lcrypto

# compile from o to output
$(OUTPUT): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(OUTPUT) $(LDFLAGS)

# compile from cpp to o
%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(OUTPUT)
	@./$(OUTPUT)

clean:
	@rm -f $(OBJS) $(OUTPUT)
