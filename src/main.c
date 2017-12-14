#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "funciones.h"

int main(int argc, char **argv){
 
	ini_var *variables = malloc (sizeof (ini_var));
	
	(variables -> display) = NULL;
	(variables -> event_queue) = NULL;
	(variables -> timer) = NULL;
	//ALLEGRO_BITMAP *bouncer = NULL;
	
	(variables -> fondoimg[0]) = NULL;
	(variables -> fondoimg[1]) = NULL;
	(variables -> fondoimg[2]) = NULL;
	(variables -> fondoimg[3]) = NULL;
	(variables -> fondoimg[4]) = NULL;
	(variables -> fondoimg[5]) = NULL;
	
	
	(variables -> pisoimg[0]) = NULL;
	(variables -> pisoimg[1]) = NULL;
	(variables -> pisoimg[2]) = NULL;
	(variables -> pisoimg[3]) = NULL;
	(variables -> pisoimg[4]) = NULL;
	
    (variables -> enemigoimg[0])   = NULL;
    (variables -> enemigoimg[1])   = NULL;
    (variables -> enemigoimg[2])   = NULL;
    (variables -> enemigoimg[3])   = NULL;
    (variables -> enemigoimg[4])   = NULL;
    (variables -> enemigoimg[5])   = NULL;
	
				
	(variables -> cuboimg)  = NULL;//cubo

	(variables -> explosionimg)   = NULL;//explosion
	(variables -> bloqueimg)   = NULL;//bloque
	(variables -> muertofinimg)   = NULL; // muerto
	(variables -> monedaimg)   = NULL; // moneda
	(variables -> volverimg)  = NULL; // volver al menu
	
	
	(variables -> temajuego) = NULL;  
	(variables -> explosionsfx) = NULL;  
	(variables -> monedasfx) = NULL;
	(variables -> levelsfx) = NULL;
	
	// menu
	
	(variables -> fondomenuimg)   = NULL; // fondo menu
	(variables -> opcionesmenuimg)  = NULL; // opciones menu
	(variables -> font) = NULL;
	(variables -> font2) = NULL;
	(variables -> temamenu) = NULL;
	
	Inicializar (&variables);
	
	GameLoop (&variables);
	
	return 0;
}

//fprintf (stderr, "hasta aca anda \n");
