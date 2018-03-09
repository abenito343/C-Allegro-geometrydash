/*! \file Inicializarcl.c
    \brief Funciones de inicializacion Cliente.
*/

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

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "datos.h"

	const float FPS = 60;
//	const int INI_SCREEN_W = 1280;
//	const int INI_SCREEN_H = 720;

int	Inicializar (ini_var **var, auxpartida **axpartida, frameExplosion **fEx, frameMonedita **fMo) {

	ini_var *variables;
	auxpartida *auxpar;
	frameExplosion *fE;
	frameMonedita *fM;
	
//	bool tecla[2] = { false , false };
	
	variables = *(var);
	auxpar = *(axpartida);
	fE = *(fEx);
	fM = *(fMo);


	(variables -> display) = NULL;
	(variables -> event_queue) = NULL;
	(variables -> timer) = NULL;
	
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
    (variables -> enemigoimg[6])   = NULL;
    (variables -> enemigoimg[7])   = NULL;
	
				
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
	(variables -> fondoipimg)   = NULL; // fondo menu
	(variables -> opcionesmenuimg)  = NULL; // opciones menu
	(variables -> jugarenlineaimg)  = NULL; 
	(variables -> mapasimg)  = NULL; 
	(variables -> mapasimg2)  = NULL; 
	(variables -> font) = NULL;
	(variables -> font2) = NULL;
	(variables -> temamenu) = NULL;
	
	(variables -> auxmapas) = 0;

// Inicializacion Teclas
	
	(variables -> key)[0] = false;
	(variables -> key)[1] = false;
	(variables -> key)[2] = false;
	(variables -> key)[3] = false;
	(variables -> key)[4] = false;
	(variables -> key)[5] = false;
	(variables -> key)[6] = false;
	(variables -> key)[7] = false;
	(variables -> key)[8] = false;
	(variables -> key)[9] = false;
	(variables -> key)[10] = false;
	(variables -> key)[11] = false;
	(variables -> key)[12] = false;
	(variables -> key)[13] = false;
	(variables -> key)[14] = false;
	(variables -> key)[15] = false;
	(variables -> key)[16] = false;
	(variables -> key)[17] = false;
	(variables -> key)[18] = false;
	(variables -> key)[19] = false;
	(variables -> key)[20] = false;
	(variables -> key)[21] = false;


// Inicializacion de variables partidas

	(auxpar -> verifvida) = 0;
	
	(auxpar -> auxspriteenemigo) = 0;
	(auxpar -> auxspritecubox) = 0;
	(auxpar -> auxspritecubov) = 0;
	(auxpar -> auxspritecuboy) = 0;
	
	(auxpar -> INI_niv) = NULL;
	(auxpar -> aux_niv) = NULL;
	
	(fE -> curFrameExplosion) = 0;
	(fE -> frameCountExplosion) = 0;
	(fE -> frameDelayExplosion) = 5;
	(fE -> frameWidthExplosion) = 283;
	(fE -> frameHeightExplosion) = 300;
	
	(fM -> curFrameMonedita) = 0;
	(fM -> frameCountMonedita) = 0;
	(fM -> frameDelayMonedita) = 10;
	(fM -> frameWidthMonedita) = 46;
	(fM -> frameHeightMonedita) = 46;


// Inicializacion Allegro

	if(!al_init()) {
		al_show_native_message_box((variables -> display), "Error", "Error", "Failed to initialize allegro!", 
								NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}
	
	(variables -> timer) = al_create_timer(1.0 / FPS);
	if(!(variables -> timer)) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
	
	(variables -> timer2) = al_create_timer(2.0);
	if(!(variables -> timer2)) {
		fprintf(stderr, "failed to create timer 2!\n");
		return -1;
	}
	
	if(!al_init_image_addon()) {
		al_show_native_message_box((variables -> display), "Error", "Error", "Failed to initialize al_init_image_addon!", 
								NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}

// Audio
	
	if(!al_install_audio()){
		fprintf(stderr, "failed to initialize audio!\n");
		return -1;
	}
	
	if(!al_init_acodec_addon()){
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return -1;
	}
	
	if (!al_reserve_samples(1)){
		fprintf(stderr, "failed to reserve samples!\n");
		return -1;
	}

// Sonidos
	
	(variables -> temajuego)= al_load_sample( "sonidos/DarudeJapishstorm.wav" );		
	(variables -> explosionsfx) = al_load_sample( "sonidos/Japish3.wav" );
	(variables -> monedasfx) = al_load_sample( "sonidos/arrrg.wav" );
	(variables -> levelsfx) = al_load_sample( "sonidos/mandalemecha.wav" );
	(variables -> temamenu)= al_load_sample( "sonidos/DarudeJapishstorm.wav" );
	
	if (!(variables -> temajuego)){
		printf( "Audio clip sample not loaded!\n" ); 
		return -1;
	}

// Pantalla
	
	(variables -> display) = al_create_display(1280,720);
	
	if(!(variables -> display)) {
		al_show_native_message_box((variables -> display), "Error", "Error", "Failed to initialize (variables -> display)!", 
								NULL, ALLEGRO_MESSAGEBOX_ERROR);                            
		al_destroy_timer((variables -> timer));
	return -1;
	}
	
	(variables -> cuboimg) = al_load_bitmap("imagenes/cubos.png");
	
	if(!(variables -> cuboimg)) {
		al_show_native_message_box((variables -> display), "Error", "Error", "Failed to load image!", 
								NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display((variables -> display));
		return -1;
	}
	
	al_set_target_bitmap((variables -> cuboimg));
	
	al_set_target_bitmap(al_get_backbuffer((variables -> display)));
	
	
  /* bouncer = al_create_bitmap((BOUNCER_SIZE), (BOUNCER_SIZE));
   if(!bouncer) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display((variables -> display));
      al_destroy_timer((variables -> timer));
      return -1;
   }*/
  // al_set_target_bitmap(bouncer);
	
	al_clear_to_color(al_map_rgb(255, 0, 255));
 
 //  al_set_target_bitmap(al_get_backbuffer((variables -> display)));
 
	(variables -> event_queue) = al_create_event_queue();

   
	if(!(variables -> event_queue)) {
		fprintf(stderr, "failed to create event_queue!\n");
		//al_destroy_bitmap(bouncer);
		al_destroy_display((variables -> display));
		al_destroy_timer((variables -> timer));
		al_destroy_timer((variables -> timer2));
		return -1;
	}
		
	al_register_event_source((variables -> event_queue), al_get_display_event_source((variables -> display)));
	
	al_register_event_source((variables -> event_queue), al_get_timer_event_source((variables -> timer)));
	al_register_event_source((variables -> event_queue), al_get_timer_event_source((variables -> timer2)));	// Para red
	
	al_register_event_source((variables -> event_queue), al_get_mouse_event_source());
	
	
	al_register_event_source((variables -> event_queue), al_get_keyboard_event_source());
	
	al_clear_to_color(al_map_rgb(0,0,0));
	
	al_flip_display();
	

//	al_start_timer((variables -> timer));			//Desactivado, inicia en cada funcion
	al_start_timer((variables -> timer2));			// Inicia timer de para red

// Imagenes
	//(variables -> fondoimg) = al_load_bitmap("imagenes/fondo5.png");
	(variables -> fondoimg[0]) = al_load_bitmap("imagenes/fondo1.png");
	(variables -> fondoimg[1]) = al_load_bitmap("imagenes/fondo1.png");
	(variables -> fondoimg[2]) = al_load_bitmap("imagenes/fondo2.png");
	(variables -> fondoimg[3])= al_load_bitmap("imagenes/fondo3.png");
	(variables -> fondoimg[4]) = al_load_bitmap("imagenes/fondo4.png");
	(variables -> fondoimg[5]) = al_load_bitmap("imagenes/fondo5.png");
	(variables -> fondoimg[6]) = al_load_bitmap("imagenes/final.png");
	
	(variables -> pisoimg[0]) = al_load_bitmap("imagenes/piso1.png");
	(variables -> pisoimg[1]) = al_load_bitmap("imagenes/piso1.png");
	(variables -> pisoimg[2]) = al_load_bitmap("imagenes/piso2.png");
	(variables -> pisoimg[3]) = al_load_bitmap("imagenes/piso3.png");
	(variables -> pisoimg[4]) = al_load_bitmap("imagenes/piso4.png");
	(variables -> pisoimg[5]) = al_load_bitmap("imagenes/piso5.png");
	

	(variables -> enemigoimg[1])  = al_load_bitmap("imagenes/enemigo12.jpg"); 
	(variables -> enemigoimg[2])  = al_load_bitmap("imagenes/enemigo22.jpg"); 
	(variables -> enemigoimg[3])  = al_load_bitmap("imagenes/enemigo3.png"); 
	(variables -> enemigoimg[4])  = al_load_bitmap("imagenes/enemigo42.jpg");
	(variables -> enemigoimg[5])  = al_load_bitmap("imagenes/enemigo52.jpg");   
	(variables -> enemigoimg[6])  = al_load_bitmap("imagenes/Modelo-Estalactita_de_Hielo2.png");
	(variables -> enemigoimg[7])  = al_load_bitmap("imagenes/index.png");
				
	
	
	(variables -> fondoipimg) = al_load_bitmap("imagenes/meterip.png");
	(variables -> explosionimg)= al_load_bitmap("imagenes/sprite_explosiones.png");
	(variables -> bloqueimg)   = al_load_bitmap("imagenes/pared.png");
	(variables -> fondomenuimg) = al_load_bitmap("imagenes/menu.jpg");
	(variables -> opcionesmenuimg) = al_load_bitmap("imagenes/opciones.png");
	(variables -> jugarenlineaimg) = al_load_bitmap("imagenes/jugarenlinea.png");
	(variables -> monedaimg) = al_load_bitmap("imagenes/monedita.png");
	(variables -> volverimg) = al_load_bitmap("imagenes/volveralmenu.png");
	(variables -> muertofinimg)  = al_load_bitmap("imagenes/muerto.png");
	(variables -> mapasimg) = al_load_bitmap("imagenes/mapas.png");
	(variables -> mapasimg2) = al_load_bitmap("imagenes/mapas2.png");

	al_convert_mask_to_alpha((variables -> explosionimg), al_map_rgb(106, 76, 48));		//DA CORE DUMP NETBOOK MAX
	
	al_init_font_addon();
	al_init_ttf_addon();

// Fuentes
	
	(variables -> font) = al_load_font ("fuentes/Lato-Black.ttf" , 24 , 0);
	(variables -> font2) = al_load_font ("fuentes/Strings Theory.otf" , 48 , 0);
	
	if(!(variables -> fondoimg[0])) {
		al_show_native_message_box((variables -> display), "Error", "Error", "Failed to load image!", 
								NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display((variables -> display));
		return -1;
	}
	
	return 0;
	
}
