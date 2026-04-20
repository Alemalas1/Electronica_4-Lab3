# ==========================================
# 1. SECCIÓN DE DEFINICIONES
# ==========================================
SRC_DIR = ./src
INC_DIR = ./inc
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
DOC_DIR = ./doc

# Búsqueda de archivos
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Compilador y banderas estándar
CC = gcc
CFLAGS = -Wall -pedantic -Werror -I $(INC_DIR)

# ---COMPILACIÓN CONDICIONAL ---
# Si en la terminal escribís "make MODO=estatico", entra por acá:
ifeq ($(MODO), estatico)
    CFLAGS += -DMODO_ESTATICO
    OUTPUT_BIN = $(BIN_DIR)/app_estatica
else
# Si solo escribís "make", entra por acá (modo dinámico por defecto):
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
	doxygen Doxyfile
	@echo "Documentación generada en la carpeta $(DOC_DIR)"

# ==========================================
# 3. REGLAS DE UTILIDAD (Carpetas y Limpieza)
# ==========================================
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BUILD_DIR) $(DOC_DIR)
	@echo "Carpetas build/ y doc/ eliminadas correctamente."

.PHONY: all clean doc