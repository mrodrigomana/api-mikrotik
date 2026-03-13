# Makefile da biblioteca (librouteros-api/Makefile)

#.PHONY: all clean install examples
.PHONY: all clean install

CC = gcc
CFLAGS = -Wall -g -fPIC
LDFLAGS = -shared -Wl,-soname,librouteros.so

# Detecta o diretório atual
CURRENT_DIR = $(shell pwd)

# Caminhos de instalação (podem vir do make raiz)
LIB_INSTALL_PATH ?= /usr/local/lib
HEADER_INSTALL_PATH ?= /usr/include

all: librouteros.so

examples: librouteros.o librouteros.h
	@$(MAKE) -C examples all

librouteros.o: librouteros.c librouteros.h
	@$(CC) $(CFLAGS) -c -o librouteros.o librouteros.c

md5.o: md5.c
	@$(CC) $(CFLAGS) -c -o md5.o md5.c

librouteros.so: librouteros.o md5.o
	@$(CC) $(CFLAGS) $(LDFLAGS) -o librouteros.so librouteros.o md5.o
	@echo "Biblioteca criada: $(CURRENT_DIR)/librouteros.so"

install: librouteros.so
	@sudo cp librouteros.so $(LIB_INSTALL_PATH)/
	@sudo cp librouteros.h $(HEADER_INSTALL_PATH)/
	@sudo ldconfig
	@echo "Biblioteca instalada em: $(LIB_INSTALL_PATH)/librouteros.so"
	@echo "Header instalado em: $(HEADER_INSTALL_PATH)/librouteros.h"

clean:
	@rm -f *.o *.so
#	@-$(MAKE) -C examples clean 2>/dev/null || true
	@sudo rm  -f $(LIB_INSTALL_PATH)/librouteros.so
