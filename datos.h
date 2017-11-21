#include <allegro5/allegro.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

enum MYKEYS {

   KEY_UP,KEY_SPACE
};

typedef struct ini_var {
		
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;	
	
	ALLEGRO_EVENT ev;
	
	ALLEGRO_BITMAP  *fondoimg;//fondo
	ALLEGRO_BITMAP  *pisoimg;//piso
	ALLEGRO_BITMAP  *cuboimg;//cubo
	ALLEGRO_BITMAP  *enemigoimg;//enemigo
	ALLEGRO_BITMAP  *explosionimg;//explosion
	ALLEGRO_BITMAP  *bloqueimg;//bloque
	ALLEGRO_BITMAP  *muertofinimg; // muerto
	ALLEGRO_BITMAP  *monedaimg; // moneda
	ALLEGRO_BITMAP  *volverimg; // volver al menu
	
	ALLEGRO_SAMPLE *temajuego;  
	ALLEGRO_SAMPLE *explosionsfx;  
	ALLEGRO_SAMPLE *monedasfx;
   
	// menu
	
	ALLEGRO_BITMAP  *fondomenuimg; // fondo menu
	ALLEGRO_BITMAP  *opcionesmenuimg; // opciones menu
	ALLEGRO_FONT   *font;
	ALLEGRO_FONT   *font2;
	ALLEGRO_SAMPLE *temamenu;
	
} ini_var;
