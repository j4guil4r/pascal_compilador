# Configuración
CC = g++
CFLAGS = -std=c++17 -I./src
TEST_DIR = ./test/test
ASM_DIR = ./test/asm
BIN = ./bin/compiler

# Encontrar todos los archivos .pas
TEST_FILES = $(wildcard $(TEST_DIR)/*.pas)
ASM_FILES = $(patsubst $(TEST_DIR)/%.pas,$(ASM_DIR)/%.s,$(TEST_FILES))

.PHONY: all clean run

all: $(BIN) $(ASM_FILES)

# Compilar el main
$(BIN): main.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) $< -o $@

# Generar .s (ASM) para cada test
$(ASM_DIR)/%.s: $(TEST_DIR)/%.pas $(BIN)
	mkdir -p $(ASM_DIR)
	$(BIN) $< > $@

# Ejecutar todas las pruebas
run: $(BIN)
	for test in $(TEST_FILES); do \
		echo "Procesando $$test..."; \
		$(BIN) $$test; \
	done

clean:
	rm -rf bin $(ASM_DIR)