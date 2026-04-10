# Makefile da aplicação (app/Makefile)

.PHONY: all clean

# Se LIB_INSTALL_PATH foi passado, usa biblioteca do sistema
# Senão, usa a biblioteca local

ifdef APP_NAME
    APP_NAME_PROJECT := $(APP_NAME)
else
    APP_NAME_PROJECT := app_local
endif

ifdef LIB_INSTALL_PATH
    # Modo instalação - usa lib do sistema
    LIB_PATH := $(LIB_INSTALL_PATH)
    INC_PATH := /usr/include
    RPATH := $(LIB_INSTALL_PATH)
else
    # Modo desenvolvimento - usa lib local
    LIB_PATH := $(shell cd ../librouteros-api && pwd)
    INC_PATH := ../librouteros-api
    RPATH := $(LIB_PATH)
endif

all: meuapp
	@echo "\033[30;42;6mAplicação compilada: $(APP_NAME_PROJECT)\033[m"
	@echo "Biblioteca usada: $(LIB_PATH)/librouteros.so"

meuapp: main.c
	@gcc main.c -I$(INC_PATH) -L$(LIB_PATH) -Wl,-rpath,$(RPATH) -lrouteros -o $(APP_NAME_PROJECT) parse_items.c options.c


clean:
	@rm -f $(APP_NAME_PROJECT)
