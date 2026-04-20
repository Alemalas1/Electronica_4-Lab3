# ==========================================
# 1. SECCIÓN DE DEFINICIONES
# ==========================================
SRC_DIR = ./src
INC_DIR = ./inc
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Búsqueda de archivos
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Compilador y banderas estándar
CC = gcc
CFLAGS = -Wall -pedantic -Werror -I $(INC_DIR)

# --- COMPILACIÓN CONDICIONAL ---
ifeq ($(MODO), estatico)
	CFLAGS += -DMODO_ESTATICO
	OUTPUT_BIN = $(BIN_DIR)/app_estatica
else
	OUTPUT_BIN = $(BIN_DIR)/app_dinamica
endif
# -------------------------------------------

# ==========================================
# 2. REGLAS PRINCIPALES
# ==========================================
all: $(OBJ_DIR) $(BIN_DIR) $(OUTPUT_BIN)

# Regla para enlazar (linkear) el ejecutable final
$(OUTPUT_BIN): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "======================================================"
	@echo " ÉXITO: Programa compilado en -> $@"
	@echo "======================================================"

# Regla para compilar los .c a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- REGLA PARA DOXYGEN ---
doc:
	mkdir -p $(BUILD_DIR)/doc
	doxygen Doxyfile
	@echo "Documentación generada en la carpeta $(BUILD_DIR)/doc"

# ==========================================
# 3. REGLAS DE UTILIDAD (Carpetas y Limpieza)
# ==========================================
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpia solo los compilados, salva la documentación
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Objetos y binarios eliminados. Documentación intacta."

# Botón rojo: Elimina ABSOLUTAMENTE TODO lo generado
clean-all:
	rm -rf $(BUILD_DIR)
	@echo "Limpieza profunda: Carpeta build/ eliminada por completo."

.PHONY: all clean clean-all doc