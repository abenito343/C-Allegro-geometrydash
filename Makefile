## Makefile generico para proyectos de Info1
# Made in Leandro Kollenberger
# Uso: Agregar archivos .c en la carpeta src, y archivos .h en inc
# Modificar el nombre del ejecutable aca, y del proyecto en el doxyFile
# Compilar con 'make', limpiar con 'make clean'
# Opcional: agregar un target 'test' que ejecute la aplicacion en modo "debug" o similar

# nombre del ejecutable de salida
EXEC = gdash
# configuracion del compilador
CC = gcc
CFLAGS = -Wall
# comentar lo siguiente para desactivar el debug
CFLAGS += -g

##### librerias a linkear
LIBS = -lm
## descomentar lo siguiente para allegro
LIBS += $(shell pkg-config --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0)
CFLAGS += $(shell pkg-config --cflags allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0)
## idem para opencv
#LIBS += $(shell pkg-config --libs opencv)
#CFLAGS += $(shell pkg-config --cflags opencv)
## ncurses
#LIBS += $(shell pkg-config --libs ncurses)
#CFLAGS += $(shell pkg-config --cflags ncurses)

# todo lo de aca abajo no importa... MAGIA
PWD = $(shell pwd)
BINFOLDER = $(PWD)/bin
SRC_PATH = $(PWD)/src
INC_PATH = $(PWD)/inc
DOC_PATH = $(PWD)/doc
SRC := $(wildcard $(SRC_PATH)/*.c)
OBJ := $(subst $(SRC_PATH),$(BINFOLDER),$(SRC:.c=.o))
ROJO=$(shell echo -e "\033[0;31m")
BLANCO=$(shell echo -e "\033[0m")

all: $(BINFOLDER) $(EXEC)

$(BINFOLDER)/%.o: $(SRC_PATH)/%.c
	@echo ""
	@echo "$(ROJO) == Compilando $< == $(BLANCO)"
	$(CC) -c -o $@ $< $(CFLAGS) -I $(INC_PATH)

$(EXEC): $(OBJ)
	@echo ""
	@echo "$(ROJO) === Linkeando $(EXEC) === $(BLANCO)"
	$(CC) -o $@ $(wildcard $(BINFOLDER)/*.o) $(CFLAGS) $(LIBS)

clean:
	@rm -rf $(BINFOLDER)/
	@rm -rf $(DOC_PATH)/
	@rm -f $(EXEC)

$(BINFOLDER):
	@mkdir -p $(BINFOLDER)/

$(DOC_PATH):
	@mkdir -p $(DOC_PATH)/

doc: $(DOC_PATH)
	doxygen doxyFile.cfg
