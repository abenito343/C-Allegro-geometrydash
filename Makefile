CC = gcc
CFLAGS = -Wall
ALFLAGS = `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`
DEPS = funciones.h
OBJ = main.o
LIBS = 
EXC = main

all: main_rule

%.o: %.c $(DEPS)
	$(CC) -c -o $< $(CFLAGS)

main_rule: $(OBJ)
	$(CC) -o $(EXC) $^ $(CFLAGS) $(ALFLAGS) $(LIBS)

clean:
	rm -f *.o &(EXC)
