# Makefile raiz para API-mikrotik

.PHONY: all clean lib app install

# Detecta o diretório raiz atual
ROOT_DIR := $(shell pwd)

# Diretórios dos subprojetos
LIB_DIR := $(ROOT_DIR)/librouteros-api
APP_DIR := $(ROOT_DIR)/app
APP_NAME := api_mikrotik
# Caminho de instalação da biblioteca (EDITÁVEL AQUI)
LIB_INSTALL_PATH := /usr/local/lib
HEADER_INSTALL_PATH := /usr/include

# Alvos principais
all: clean lib app
	@echo "\033[30;42;6mBuild completo realizado com sucesso!\033[m"

# Compila a biblioteca compartilhada
lib:
	@echo "Compilando librouteros-api..."
	@cd $(LIB_DIR) && $(MAKE) all
	@echo "Biblioteca compilada com sucesso!"

# Compila a aplicação (usando lib LOCAL)
app: lib
	@echo "Compilando aplicação (modo desenvolvimento)..."
	@cd $(APP_DIR) && $(MAKE) all APP_NAME=$(APP_NAME)
	@echo "Aplicação compilada com sucesso!"

# Instala a biblioteca no sistema e compila app com lib instalada
install: clean lib
	@echo "Instalando librouteros-api no sistema..."
	@cd $(LIB_DIR) && $(MAKE) install LIB_INSTALL_PATH=$(LIB_INSTALL_PATH) HEADER_INSTALL_PATH=$(HEADER_INSTALL_PATH)
	@echo "Biblioteca instalada!"
	@echo "Compilando aplicação com a biblioteca instalada..."
	@cd $(APP_DIR) && $(MAKE) all LIB_INSTALL_PATH=$(LIB_INSTALL_PATH) APP_NAME=$(APP_NAME)
	@echo "Instalação concluída!"

# Limpa todos os arquivos compilados
clean:
	@echo "Limpando librouteros-api..."
	@-cd $(LIB_DIR) && $(MAKE) clean 
	@echo "Limpando aplicação..."
	@-cd $(APP_DIR) && $(MAKE) clean APP_NAME=$(APP_NAME)
	@echo "Limpeza concluída!"