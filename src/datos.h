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
	
	ALLEGRO_BITMAP  *fondoimg[7];

	
	ALLEGRO_BITMAP  *pisoimg[6];

	ALLEGRO_BITMAP  *enemigoimg[6];//enemigo
	
	
	ALLEGRO_BITMAP  *cuboimg;//cubo
	
	ALLEGRO_BITMAP  *explosionimg;//explosion
	ALLEGRO_BITMAP  *bloqueimg;//bloque
	ALLEGRO_BITMAP  *muertofinimg; // muerto
	ALLEGRO_BITMAP  *monedaimg; // moneda
	ALLEGRO_BITMAP  *volverimg; // volver al menu
	
	ALLEGRO_SAMPLE *temajuego;  
	ALLEGRO_SAMPLE *explosionsfx;  
	ALLEGRO_SAMPLE *monedasfx;
	ALLEGRO_SAMPLE *levelsfx;
   
   
	// menu
	
	ALLEGRO_BITMAP  *fondomenuimg; // fondo menu
	ALLEGRO_BITMAP  *opcionesmenuimg; // opciones menu
	ALLEGRO_FONT   *font;
	ALLEGRO_FONT   *font2;
	ALLEGRO_SAMPLE *temamenu;
	
	bool key[2];
	
} ini_var;

typedef struct posicion {
	
	float bouncer_x;
	
	float bouncer_x2;
	float bouncer_y2;

	float bouncer_x3;

	float bouncer_x4;

	float bouncer_x5;

	float bouncer_x6;
	float bouncer_y6;

	float bouncer_dx;

} posicion;

typedef struct auxpartida {
	
	char vidac[2];
	char scorec[22];
	char nivelc[5];
	int verifvida;
	
	int aux1;
	
	int auxmoneda1,auxmoneda2;
		
	float auxpisox,auxfondox,auxcolision;
	float auxspriteenemigo;
	float auxspritecubox;
	float auxspritecubov;
	float auxspritecuboy;


} auxpartida;

typedef struct frameExplosion {

	int curFrameExplosion;
	int frameCountExplosion;
	int frameDelayExplosion;
	int frameWidthExplosion;
	int frameHeightExplosion;

} frameExplosion;

typedef struct frameMonedita {
	
	int curFrameMonedita;
	int frameCountMonedita;
	int frameDelayMonedita;
	int frameWidthMonedita;
	int frameHeightMonedita;
	
} frameMonedita;
