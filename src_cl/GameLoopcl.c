/*! \file GameLoopcl.c
    \brief GameLoop y sus funciones cliente.
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

#include "funcionesred.h"

	const int SCREEN_W = 1280;
	const int SCREEN_H = 720;
	const int BOUNCER_SIZE = 32;

	const int maxFrameExplosion = 10;	
	const int maxFrameMonedita= 4;

int menu (ini_var **mvar, auxpartida *mauxpar) {

	ini_var *mvariables;

	int mauxestadojuego = 1;
	int mauxopcionessalir,mauxopcionesjugar,mauxjugarenlinea;
	int mauxx, mauxy;	//mouse
	char maux3[11],maux4[11];
	
	
	bool mredraw = true;
	
	mvariables = *(mvar);

	al_start_timer((mvariables -> timer));
		
	al_wait_for_event((mvariables -> event_queue), &(mvariables -> ev));
	
	if(((mvariables -> ev).mouse.x > 0) && (((mvariables -> ev).mouse.x) < 1280) && (((mvariables -> ev).mouse.y) > 0) && ((mvariables -> ev).mouse.y < 720)){
		mauxx=(mvariables -> ev).mouse.x;
		mauxy=(mvariables -> ev).mouse.y;
	}
	
	sprintf(maux3, "%d", mauxx);
	sprintf(maux4, "%d", mauxy);
	
	
	
	if(mauxx > 454 && mauxx < 726 && mauxy > 499 && mauxy < 596) {
		
		mauxopcionesjugar=265;
		
	}
	
	else{
			mauxopcionesjugar=0;
	} 	
	if(mauxx > 354 && mauxx < 970 && mauxy > 610 && mauxy < 680) {
		
		mauxjugarenlinea=93;
		
	}
	
	else{
			mauxjugarenlinea=0;
	} 	
	
		
	
		if(mauxx > 1056 && mauxx < 1263 && mauxy > 637 && mauxy < 706) {

		mauxopcionessalir=215;
	}
	
	else{
		mauxopcionessalir=0;
	} 		
	
	

	

	
	

	if((mvariables -> ev).type == ALLEGRO_EVENT_TIMER) {
		mredraw = true;
	}
	else if((mvariables -> ev).type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return -1;
	}
	else if((mvariables -> ev).type == ALLEGRO_EVENT_MOUSE_AXES ||
			(mvariables -> ev).type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

		
	}
	else if((mvariables -> ev).type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		
		if(mauxx > 1056 && mauxx < 1263 && mauxy > 637 && mauxy < 706)
			return -1;
		if(mauxx > 454 && mauxx < 726 && mauxy > 499 && mauxy < 596){
				mauxestadojuego=0;
				
			}
		if(mauxx > 354 && mauxx < 970 && mauxy > 610 && mauxy < 680) {
			mauxestadojuego=3;
		}
		
		if(mauxx > 961 && mauxx < 1084 && mauxy > 122 && mauxy < 144) {
		
			(mvariables -> auxmapas)=0;
			(mauxpar -> map) = 0;
		
		}
		if(mauxx > 1139 && mauxx < 1269 && mauxy > 122 && mauxy < 144) {
		
			(mvariables -> auxmapas)=33;
			(mauxpar -> map) = 1;
		
		}
		
	}



	if(mredraw && al_is_event_queue_empty(mvariables -> event_queue)) {
		mredraw = false;

		al_clear_to_color(al_map_rgb(0,0,0));
		
				
		
		al_play_sample((mvariables -> temamenu), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		
		
		
		al_draw_bitmap((mvariables -> fondomenuimg),0,0,0);
	
		al_draw_bitmap_region((mvariables -> opcionesmenuimg),0+mauxopcionesjugar,0,260,95,457,500,0);
		
		al_draw_bitmap_region((mvariables -> jugarenlineaimg),0,0+mauxjugarenlinea,650,95,350,590,0);
		
		al_draw_bitmap_region((mvariables -> opcionesmenuimg),0+mauxopcionessalir,90,210,90,1050,625,0);


		/*al_draw_text((mvariables -> font), al_map_rgb(255, 0, 255), 50, 50, 0, maux3);
		al_draw_text((mvariables -> font), al_map_rgb(255, 0, 255), 10, 50, 0, "X:");
		al_draw_text((mvariables -> font), al_map_rgb(255, 0, 255), 50, 100, 0, maux4);
		al_draw_text((mvariables -> font), al_map_rgb(255, 0, 255), 10, 100, 0, "Y:");*/
		
		
		al_draw_bitmap_region((mvariables -> mapasimg2),0,0,500,40,950,80,0);
		al_draw_bitmap_region((mvariables -> mapasimg),0,7+(mvariables -> auxmapas),500,35,950,115,0);


		al_flip_display();
		
		
		
	}
	
	if (mauxestadojuego == 0){					// Antes de salir:
		
		al_stop_samples();						// Detiene la musica
	
	}
	
	return mauxestadojuego;
}

int cargar_ip (ini_var **cvar, variablescliente **cvarcl) {

	ini_var *cvariables;
	variablescliente *vcl;
	
	int cauxestadojuego = 3;
		
	int cauxopcionessalir;
	int cauxx, cauxy;	//mouse
	
	bool credraw = true;
	
	cvariables = *(cvar);
	vcl = *(cvarcl);
		
	al_wait_for_event((cvariables -> event_queue), &(cvariables -> ev));
	
	if(((cvariables -> ev).mouse.x > 0) && (((cvariables -> ev).mouse.x) < 1280) && (((cvariables -> ev).mouse.y) > 0) && ((cvariables -> ev).mouse.y < 720)){
		cauxx=(cvariables -> ev).mouse.x;
		cauxy=(cvariables -> ev).mouse.y;
	}
	

	//---------------------------------------------------------------------  parte del mouse para el boton


		
	
	if(cauxx > 1056 && cauxx < 1263 && cauxy > 637 && cauxy < 706) {

		cauxopcionessalir=215;
	}
	
	else
	{
		cauxopcionessalir=0;
	} 		

/*	if((cvariables -> ev).type == ALLEGRO_EVENT_TIMER) {
		credraw = true;
	}
*/ if((cvariables -> ev).type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return -1;
	}
	else if((cvariables -> ev).type == ALLEGRO_EVENT_MOUSE_AXES ||
			(cvariables -> ev).type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

		
	}
	else if((cvariables -> ev).type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		if(cauxx > 1056 && cauxx < 1263 && cauxy > 637 && cauxy < 706)
			cauxestadojuego= 1;
	}

  //------------------------------------------------------------------------
	
	
	if((vcl -> auxip3)!=1)
	{	
		(vcl -> auxip)=0;
		(vcl -> act)=0;
		(vcl -> auxip2)=0;

		memset((vcl -> ip2),0,33);
		
	}
	
	if((vcl -> auxip2)<16){					// Modificado para cargar localhost
				
		if((vcl -> auxip2)<15){

			if((cvariables -> key)[KEY_1] ) {
				(vcl -> auxip)='1';(vcl -> act)=1;
			}  	  
			
			if((cvariables -> key)[KEY_2] ) {
				(vcl -> auxip)='2';(vcl -> act)=1;
			}	
			
			if((cvariables -> key)[KEY_3] ) {
				(vcl -> auxip)='3';(vcl -> act)=1;
					}	

			if((cvariables -> key)[KEY_4] ) {
				(vcl -> auxip)='4';(vcl -> act)=1;
					}	

			if((cvariables -> key)[KEY_5] ) {
				(vcl -> auxip)='5';(vcl -> act)=1;
			}	

			if((cvariables -> key)[KEY_6] ) {
				(vcl -> auxip)='6';(vcl -> act)=1; 
			}	

			if((cvariables -> key)[KEY_7] ) {
				(vcl -> auxip)='7';(vcl -> act)=1;
				 
			}	

			if((cvariables -> key)[KEY_8] ) {
				(vcl -> auxip)='8';(vcl -> act)=1;
			}	

			if((cvariables -> key)[KEY_9] ) {
				(vcl -> auxip)='9';(vcl -> act)=1;
					}	

			if((cvariables -> key)[KEY_0] ) {
				(vcl -> auxip)='0';(vcl -> act)=1;
			}	

			if((cvariables -> key)[KEY_FULLSTOP] ) {
				(vcl -> auxip)='.';(vcl -> act)=1;
			}	
			if((cvariables -> key)[KEY_PAD_DELETE] ) {
				(vcl -> auxip)='.';(vcl -> act)=1;
			}
		}
		if((cvariables -> key)[KEY_ENTER] ) {
			(vcl -> auxip2)=16;
		}
		
		if((cvariables -> key)[KEY_BACKSPACE] ) {
			
			(vcl -> auxip)=0;
			
			(vcl -> act)=0;
			
			(vcl -> auxip2)=0;
			
			memset((vcl -> ip),0, 3);
			
			memset((vcl -> ip2),0,33);
		}	
		
		if((vcl -> tecla)!=1 && (vcl -> act)==1){
				
				
				(vcl -> auxip2)=(vcl -> auxip2)+1;
				if((vcl -> auxip3) != 1)
				{	
					sprintf((vcl -> ip), "%c",(vcl -> auxip));
					strcpy((vcl -> ip2),(vcl -> ip));
				}
				else {
		
				sprintf((vcl -> ip), "%c",(vcl -> auxip));
				strcat((vcl -> ip2),(vcl -> ip));
				
				}
			(vcl -> auxip3)=1;
			}
		(vcl -> tecla)=1;(vcl -> act)=0;

		
		if((cvariables -> ev).type == ALLEGRO_EVENT_KEY_DOWN) {
			switch((cvariables -> ev).keyboard.keycode) {
				
				case ALLEGRO_KEY_1:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_1] = true;
				break;
				case ALLEGRO_KEY_2:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_2] = true;
				break;
				case ALLEGRO_KEY_3:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_3] = true;
				break;
				case ALLEGRO_KEY_4:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_4] = true;
				break;
				case ALLEGRO_KEY_5:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_5] = true;
				break;
				case ALLEGRO_KEY_6:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_6] = true;
				break;
				case ALLEGRO_KEY_7:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_7] = true;
				break;
				case ALLEGRO_KEY_8:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_8] = true;
				break;
				case ALLEGRO_KEY_9:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_9] = true;
				break;
				case ALLEGRO_KEY_0:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_0] = true;
				break;
				case ALLEGRO_KEY_FULLSTOP:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_FULLSTOP] = true;
				break;
				case ALLEGRO_KEY_ENTER:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_ENTER] = true;
				break;
				case ALLEGRO_KEY_BACKSPACE:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_BACKSPACE] = true;
				break;
				case ALLEGRO_KEY_PAD_DELETE:
				(vcl -> tecla)=0;
				(cvariables -> key)[KEY_PAD_DELETE] = true;
				break;
			}
		}
		else if((cvariables -> ev).type == ALLEGRO_EVENT_KEY_UP) {
			
			switch((cvariables -> ev).keyboard.keycode) {
				
				case ALLEGRO_KEY_1:
				(cvariables -> key)[KEY_1] = false;
				break;
				
				case ALLEGRO_KEY_2:
				(cvariables -> key)[KEY_2] = false;
				break;
				case ALLEGRO_KEY_3:
				(cvariables -> key)[KEY_3] = false;
				break;
				case ALLEGRO_KEY_4:
				(cvariables -> key)[KEY_4] = false;
				break;
				case ALLEGRO_KEY_5:
				(cvariables -> key)[KEY_5] = false;
				break;
				case ALLEGRO_KEY_6:
				(cvariables -> key)[KEY_6] = false;
				break;
				case ALLEGRO_KEY_7:
				(cvariables -> key)[KEY_7] = false;
				break;
				case ALLEGRO_KEY_8:
				(cvariables -> key)[KEY_8] = false;
				break;
				case ALLEGRO_KEY_9:
				(cvariables -> key)[KEY_9] = false;
				break;
				case ALLEGRO_KEY_0:
				(cvariables -> key)[KEY_0] = false;
				break;
				case ALLEGRO_KEY_FULLSTOP:
				(cvariables -> key)[KEY_FULLSTOP] = false;
				break;
				case ALLEGRO_KEY_ENTER:
				(cvariables -> key)[KEY_ENTER] = false;
				break;
				case ALLEGRO_KEY_BACKSPACE:
				(cvariables -> key)[KEY_BACKSPACE] = false;
				break;
				case ALLEGRO_KEY_PAD_DELETE:
				(cvariables -> key)[KEY_PAD_DELETE] = false;
				break;
			}
		}
			
		else if((cvariables -> ev).type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return -1;
		}




		if(credraw && al_is_event_queue_empty(cvariables -> event_queue)) {
			credraw = false;

			al_clear_to_color(al_map_rgb(0,0,0));
			
			
			al_draw_bitmap((cvariables -> fondoipimg),-764,0,0);
			al_draw_bitmap((cvariables -> fondoipimg),200,0,0);
			al_draw_bitmap((cvariables -> fondoipimg),1224,0,0);
			al_draw_text((cvariables -> font2), al_map_rgb(0, 0, 255), 250, 100, 0, "Inserte su IP:");
			al_draw_text((cvariables -> font2), al_map_rgb(0, 0, 255), 250, 175, 0, "( exacta CON puntos y aprete enter )");
			al_draw_text((cvariables -> font2), al_map_rgb(0, 0, 255), 300, 325, 0, (vcl -> ip2));
			
			
				al_draw_bitmap_region((cvariables -> opcionesmenuimg),430-cauxopcionessalir,90,210,90,1050,625,0);
	

			al_flip_display();
		}

	} else {

		strcpy((vcl -> hostname), (vcl -> ip2));
				
		(vcl -> cx_stat) = inicializar_cl (vcl);
		
		if (vcl -> cx_stat) {
			
			(vcl -> netflag) = 1;				// Activa el flag de modo de red
			cauxestadojuego = 0;				// Si se conecta arranca la partida
			
		}
		
	}
	
	if (cauxestadojuego == 0){					// Antes de salir:
		
		al_stop_samples();						// Detiene la musica
			
		al_stop_timer((cvariables -> timer));	//  Frena el timer
	
	}	
	
	return cauxestadojuego;
}

/*	Funcion que manda todas las posiciones y velocidad por red
*
*	Manda en funcion del timer2 de un segundo. Entre envios de posiciones se demora para que no se sature el socket.
*/
int send_pos (ini_var **svar, variablescliente *svarcl, posicion *spos, auxpartida *sauxpar) {
	
	ini_var *svariables;	
	
	svariables = *(svar);

	if((svariables -> ev).type == ALLEGRO_EVENT_TIMER) {
		
		if((svariables -> ev).timer.source == (svariables -> timer2)) {
							
/*			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 0, (spos -> bouncer_x) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);                                                                                         
			                                                                                                         
*/			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 2, (spos -> bouncer_x2) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);                                                                                         
			                                                                                                         
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'y', 2, (spos -> bouncer_y2) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);                                                                                         
			                                                                                                         
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 31, (spos -> bouncer_x31) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);                                                                                         
			                                                                                                         
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 32, (spos -> bouncer_x32) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);   
			 
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 33, (spos -> bouncer_x33) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);                                                                                     
			                                                                                                         
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 34, (spos -> bouncer_x34) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);
			
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 35, (spos -> bouncer_x35) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);
			
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 36, (spos -> bouncer_x36) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);
			
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 37, (spos -> bouncer_x37) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);
			
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 38, (spos -> bouncer_x38) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);
			
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 39, (spos -> bouncer_x39) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);                                                                                         
			                                                                                                         
/*			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 4, (spos -> bouncer_x4) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);                                                                                         
			                                                                                                         
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 5, (spos -> bouncer_x5) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);                                                                                         
			                                                                                                         
*/			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'x', 6, (spos -> bouncer_x6) , (sauxpar -> score) , (sauxpar -> vida));
			al_rest(0.01);                                                                                         
			                                                                                                         
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'y', 6, (spos -> bouncer_y6) , (sauxpar -> score) , (sauxpar -> vida));
/*			al_rest(0.01);                                                                                         
			                                                                                                         
			put_network_data ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), (svarcl -> buffercl4), (svarcl -> buffercl5), VACIO, VACIO, 'd', 0, (spos -> bouncer_dx) , (sauxpar -> score) , (sauxpar -> vida));		// Velocidad
			al_rest(0.01);                                                                                         
*/				
		}
		
	}
	
	return 0;
}

int partida (ini_var **pvar, posicion *ppos, auxpartida *pauxpar, frameExplosion *pfE, frameMonedita *pfM, variablescliente *pvarcl) {

	ini_var *pvariables;

	bool predraw = true;	

	int pauxestadojuego = 0;
	
	int i;						// Contador para el for de envio de tecla 

	pvariables = *(pvar);	

// Niveles 

	if((pauxpar ->t_nivel ) >1000&&(pauxpar -> t_nivel) <2000)
	(pauxpar -> nivel)=2;
	if((pauxpar -> t_nivel) >2000&&(pauxpar -> t_nivel) <3000)
	(pauxpar -> nivel)=3;
	if((pauxpar -> t_nivel) >3000&&(pauxpar -> t_nivel) <4000)
	(pauxpar -> nivel)=4;
	if((pauxpar -> t_nivel) >4000&&(pauxpar -> t_nivel) <5000)
	(pauxpar -> nivel)=5;

// Deteccion de aparicion y altura de enemigos

	if(((pauxpar -> aux_niv) -> t_aparicion) == (pauxpar -> t_nivel)){
		switch((pauxpar -> aux_niv) -> clase){
			case 1:
				(pauxpar -> tipo1) = 1;
				(pauxpar -> aux_niv) = ((pauxpar -> aux_niv) -> sig);
				break;
			case 2:
				(pauxpar -> tipo2) = 1;
				(pauxpar -> aux_niv) = ((pauxpar -> aux_niv) -> sig);
				break;
			case 3:
				(pauxpar -> tipo3) = 1;
				(pauxpar -> aux_niv) = ((pauxpar -> aux_niv) -> sig);
				break;
			case 4:
				(pauxpar -> tipo4) = 1;
				(pauxpar -> aux_niv) = ((pauxpar -> aux_niv) -> sig);
				break;
			case 5:
				(pauxpar -> tipo5) = 1;
				(pauxpar -> aux_niv) = ((pauxpar -> aux_niv) -> sig);
				break;
			case 6:
				(pauxpar -> tipo6) = 1;
				(pauxpar -> aux_niv) = ((pauxpar -> aux_niv) -> sig);
				break;
			case 7:
				(pauxpar -> tipo7) = 1;
				(pauxpar -> aux_niv) = ((pauxpar -> aux_niv) -> sig);
				break;
			case 8:
				(pauxpar -> tipo8) = 1;
				(pauxpar -> aux_niv) = ((pauxpar -> aux_niv) -> sig);
				break;
			case 9:
				(pauxpar -> tipo9) = 1;
				(pauxpar -> aux_niv) = ((pauxpar -> aux_niv) -> sig);
				break;
			}
			
		if((pauxpar -> aux_niv) -> sig == NULL){
			pauxestadojuego = 2;
		}
		
	}

// Sonido Nivel
	
	if((pauxpar -> t_nivel) == 1000 || (pauxpar -> t_nivel) == 2000 || (pauxpar -> t_nivel) == 3000 || (pauxpar -> t_nivel) == 4000){

		al_play_sample((pvariables -> levelsfx), 1.0, 0.0,1.2,ALLEGRO_PLAYMODE_ONCE,NULL);
	}


	
	if ( !((pvariables -> key)[KEY_P])){
		
		al_start_timer((pvariables -> timer));
		
	}

	al_wait_for_event((pvariables -> event_queue), &(pvariables -> ev));

	if ( (pvariables -> key)[KEY_P]){					// Pausa
	
		al_stop_timer((pvariables -> timer));
	
	}

	if((pvariables -> ev).type == ALLEGRO_EVENT_TIMER) {
		
		if((pvariables -> ev).timer.source == (pvariables -> timer)) {
			
			
			//-----------------------------------------------------	
			
			
			
			if((pvariables -> key)[KEY_UP] ) {
				(pauxpar -> auxspritecubov)=(pauxpar -> auxspritecubov)+1;
				if((pauxpar -> auxspritecubov)==3){
					(pauxpar -> auxspritecubox)=(pauxpar -> auxspritecubox)+1;
					(pauxpar -> auxspritecubov)=12;	
					}
			}  	  
			else{
				(pauxpar -> auxspritecubov)=0;
				
			}
			if((pauxpar -> auxspritecubox)==12)
			{
				(pauxpar -> auxspritecubox)=0;
				(pauxpar -> auxspritecuboy)=(pauxpar -> auxspritecuboy)+1;
			}
			if((pauxpar -> auxspritecuboy)==5)
				(pauxpar -> auxspritecuboy)=0;
			
			
			
			
			if((pvariables -> key)[KEY_SPACE] ) 
			{
				if( (ppos -> bouncer_y2) >= 339.0)
				{		
					(pauxpar -> aux1)=1;
				}  		
			}
			else
			{
				(pauxpar -> aux1)=0;
			}
				
			if((pauxpar -> aux1)==0)
			{
				if( (ppos -> bouncer_y2) <= 336.0)
					{
						(ppos -> bouncer_y2) += 80.0*((pauxpar -> nivel)*0.1);
					}
					
			
					
					
				//while((ppos -> bouncer_y2) <= 339.0){(ppos -> bouncer_y2) += 40.0*((pauxpar -> nivel)*0.1);}
			}
			
			if((pauxpar -> aux1)==1)
			{	
				if( (ppos -> bouncer_y2) >= -110.0)
				{
					(ppos -> bouncer_y2) -= 80.0*((pauxpar -> nivel)*0.1);
				}
				else
				{
					(pauxpar -> aux1)=0;
				}   
			}
			//-------------------------------------------------
			
				
			if((ppos -> bouncer_x) < -256)              
				(ppos -> bouncer_x)= (ppos -> bouncer_x)+256; 
			(ppos -> bouncer_x) += (ppos -> bouncer_dx);
					
				
			if((ppos -> bouncer_x4) < -256)           
				(ppos -> bouncer_x4)= (ppos -> bouncer_x4)+1024; 
			(ppos -> bouncer_x4)+= (ppos -> bouncer_dx)/3;
							
			if((pauxpar -> tipo1) == 1){					
			if((ppos -> bouncer_x31) < -256) {                
				(ppos -> bouncer_x31)= (ppos -> bouncer_x31)+1556;
				(pauxpar -> tipo1) = 0;
			}
			(ppos -> bouncer_x31) += (ppos -> bouncer_dx)*10*((pauxpar -> nivel)*0.1);				
		}
		
		if((pauxpar -> tipo2) == 1){
			if((ppos -> bouncer_x32) < -256) {
				(ppos -> bouncer_x32)= (ppos -> bouncer_x32)+1556;
				(pauxpar -> tipo2) = 0;
			}
			(ppos -> bouncer_x32) += (ppos -> bouncer_dx)*10*((pauxpar -> nivel)*0.1);				
		}

		if((pauxpar -> tipo3) == 1){
			if((ppos -> bouncer_x33) < -256) {               
				(ppos -> bouncer_x33)= (ppos -> bouncer_x33)+1556;
				(pauxpar -> tipo3) = 0;
			}
			(ppos -> bouncer_x33) += (ppos -> bouncer_dx)*10*((pauxpar -> nivel)*0.1);
		}
		if((pauxpar -> tipo4) == 1){
			if((ppos -> bouncer_x34) < -256) {               
				(ppos -> bouncer_x34)= (ppos -> bouncer_x34)+1556;
				(pauxpar -> tipo4) = 0;
			}
			(ppos -> bouncer_x34) += (ppos -> bouncer_dx)*10*((pauxpar -> nivel)*0.1);
		}
		if((pauxpar -> tipo5) == 1){
			if((ppos -> bouncer_x35) < -256) {               
				(ppos -> bouncer_x35)= (ppos -> bouncer_x35)+1556;
				(pauxpar -> tipo5) = 0;
			}
			(ppos -> bouncer_x35) += (ppos -> bouncer_dx)*10*((pauxpar -> nivel)*0.1);
		}
		if((pauxpar -> tipo6) == 1){
			if((ppos -> bouncer_x36) < -256) {               
				(ppos -> bouncer_x36)= (ppos -> bouncer_x36)+1556;
				(pauxpar -> tipo6) = 0;
			}
			(ppos -> bouncer_x36) += (ppos -> bouncer_dx)*10*((pauxpar -> nivel)*0.1);
		}
		if((pauxpar -> tipo7) == 1){
			if((ppos -> bouncer_x37) < -256) {               
				(ppos -> bouncer_x37)= (ppos -> bouncer_x37)+1556;
				(pauxpar -> tipo7) = 0;
			}
			(ppos -> bouncer_x37) += (ppos -> bouncer_dx)*30*((pauxpar -> nivel)*0.1);
		}
		if((pauxpar -> tipo8) == 1){
			if((ppos -> bouncer_x38) < -256) {               
				(ppos -> bouncer_x38)= (ppos -> bouncer_x38)+1556;
				(pauxpar -> tipo8) = 0;
			}
			(ppos -> bouncer_x38) += (ppos -> bouncer_dx)*30*((pauxpar -> nivel)*0.1);
		}
		if((pauxpar -> tipo9) == 1){
			if((ppos -> bouncer_x39) < -256) {               
				(ppos -> bouncer_x39)= (ppos -> bouncer_x33)+1556;
				(pauxpar -> tipo9) = 0;
			}
			(ppos -> bouncer_x39) += (ppos -> bouncer_dx)*30*((pauxpar -> nivel)*0.1);
		}
			
			if((ppos -> bouncer_x5) < -956)                
				(ppos -> bouncer_x5)= (ppos -> bouncer_x5)+2056;
			(ppos -> bouncer_x5) += (ppos -> bouncer_dx);
			
			
			if((ppos -> bouncer_x6) < 0)                
				(ppos -> bouncer_x6)= (ppos -> bouncer_x6)+1500;
			(ppos -> bouncer_x6) += (ppos -> bouncer_dx);
			
			
				
			if( (ppos -> bouncer_y6) >= 339.0){
				(pauxpar -> auxmoneda1)=1;
			}  
			else{
				// (pauxpar -> auxmoneda1)=0;
				}
				
			if((pauxpar -> auxmoneda1)==0){
				if( (ppos -> bouncer_y6) <= 339.0)
					{
						(ppos -> bouncer_y6) += 8.0;
					}
			}
			if((pauxpar -> auxmoneda1)==1){
				
			if( (ppos -> bouncer_y6) >= 0.0)
			{
				(ppos -> bouncer_y6) -= 8.0;
				}
				else
				{
					(pauxpar -> auxmoneda1)=0;
				}   
			}
				
			//---------------------------------------------------- 
				
				if(++(pfE -> frameCountExplosion) >= (pfE -> frameDelayExplosion))
				{
					if(++(pfE -> curFrameExplosion) >= maxFrameExplosion)
						(pfE -> curFrameExplosion) = 0;
	
					(pfE -> frameCountExplosion) = 0;
				}
	
	
				if(++(pfM -> frameCountMonedita) >= (pfM -> frameDelayMonedita) )
				{
					if(++(pfM -> curFrameMonedita)  >= maxFrameMonedita )
						(pfM -> curFrameMonedita)  = 0;
	
					(pfM -> frameCountMonedita)  = 0;
				}
	
	
	
				if((pauxpar -> vida)==0)
				{
					pauxestadojuego=2;
					
					
					
					}
	
	
				(pauxpar -> score) = (pauxpar -> score) + 1;
				(pauxpar -> t_nivel) = (pauxpar -> t_nivel) + 1;
			//	(ppos -> bouncer_x2) -= 5;
	
			/*	if((ppos -> bouncer_x2) <= 0 - (pfE -> frameWidthExplosion))
					(ppos -> bouncer_x2) = (SCREEN_W);*/
				
				//-----------------------------------------------------------
			
	
			predraw = true;
			
		}
		
	}
	else if((pvariables -> ev).type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return -1;

/* ************************
 * Envio de teclas por red
 *************************/

	} else if((pvariables -> ev).type == ALLEGRO_EVENT_KEY_DOWN) {
		switch((pvariables -> ev).keyboard.keycode) {
			
			case ALLEGRO_KEY_UP:
			(pvariables -> key)[KEY_UP] = true;
			
			if ((pvarcl -> netflag) == 1){
				
				put_network_data((pvarcl -> sockfd), (pvarcl -> buffercl), (pvarcl -> buffercl2), (pvarcl -> buffercl3), (pvarcl -> buffercl4), (pvarcl -> buffercl5), KEY_UP, true, VACIO, VACIO, VACIO , (pauxpar -> score) , (pauxpar -> vida));		// Manda por red tecla arriba
				
			}
			
			break;
			
			case ALLEGRO_KEY_SPACE:
			(pvariables -> key)[KEY_SPACE] = true;
			
			if ((pvarcl -> netflag) == 1){
				
				put_network_data((pvarcl -> sockfd), (pvarcl -> buffercl), (pvarcl -> buffercl2), (pvarcl -> buffercl3), (pvarcl -> buffercl4), (pvarcl -> buffercl5), KEY_SPACE, true, VACIO, VACIO, VACIO , (pauxpar -> score) , (pauxpar -> vida));	// Manda por red barra espaciadora
				
			}			
			
			break;
			
			case ALLEGRO_KEY_P:
			
			if (!((pvariables -> key)[KEY_P])){
				(pvariables -> key)[KEY_P] = true;

				if ((pvarcl -> netflag) == 1){
				
					put_network_data((pvarcl -> sockfd), (pvarcl -> buffercl), (pvarcl -> buffercl2), (pvarcl -> buffercl3), (pvarcl -> buffercl4), (pvarcl -> buffercl5), KEY_P, true, VACIO, VACIO, VACIO , (pauxpar -> score) , (pauxpar -> vida));	// Manda por red tecla P
				
				}
			
			} else if ((pvariables -> key)[KEY_P]) {					// Si se vuelve a apretar devuelve falso
				(pvariables -> key)[KEY_P] = false;
			
				if ((pvarcl -> netflag) == 1){
				
					put_network_data((pvarcl -> sockfd), (pvarcl -> buffercl), (pvarcl -> buffercl2), (pvarcl -> buffercl3), (pvarcl -> buffercl4), (pvarcl -> buffercl5), KEY_P, false, VACIO, VACIO, VACIO , (pauxpar -> score) , (pauxpar -> vida));		// Manda por red tecla P
				
				}
			
			}
			
			break;
		}
	}
	else if((pvariables -> ev).type == ALLEGRO_EVENT_KEY_UP) {
		switch((pvariables -> ev).keyboard.keycode) {
			
			case ALLEGRO_KEY_UP:
			(pvariables -> key)[KEY_UP] = false;

			if ((pvarcl -> netflag) == 1){
				
				for (i = 0 ; i < 4 ; i ++) {				// Manda varias veces para evitar errores de socket
				
					put_network_data((pvarcl -> sockfd), (pvarcl -> buffercl), (pvarcl -> buffercl2), (pvarcl -> buffercl3), (pvarcl -> buffercl4), (pvarcl -> buffercl5), KEY_UP, false, VACIO, VACIO, VACIO , (pauxpar -> score) , (pauxpar -> vida));		// Manda por red tecla arriba
				
				}
				
			}
			
	
			break;
			
			case ALLEGRO_KEY_SPACE:
			(pvariables -> key)[KEY_SPACE] = false;

			if ((pvarcl -> netflag) == 1){
				
				for (i = 0 ; i < 4 ; i ++) {				// Manda varias veces para evitar errores de socket
					
					put_network_data((pvarcl -> sockfd), (pvarcl -> buffercl), (pvarcl -> buffercl2), (pvarcl -> buffercl3), (pvarcl -> buffercl4), (pvarcl -> buffercl5), KEY_SPACE, false, VACIO, VACIO, VACIO , (pauxpar -> score) , (pauxpar -> vida));	// Manda por red barra espaciadora
				
				}
		
			}			

			break;
		}
	}

	if(predraw && al_is_event_queue_empty((pvariables -> event_queue))) {
		predraw = false;
		
		(pauxpar -> auxpisox)=(ppos -> bouncer_x);
		(pauxpar -> auxfondox)=(ppos -> bouncer_x4);
			
		sprintf((pauxpar -> vidac), "%d", (pauxpar -> vida));
			
		
		//fprintf (stderr, "hasta aca anda \n");
		
		sprintf((pauxpar -> scorec), "%d", (pauxpar -> score)); //esto
		
			sprintf((pauxpar -> nivelc), "%d", (pauxpar -> nivel)); //esto
		
		
	

		
		al_clear_to_color(al_map_rgb(0,0,0));
		
		//al_play_sample((pvariables -> temajuego), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

	//al_draw_bitmap(bouncer, (ppos -> bouncer_x), bouncer_y, 0);
	al_draw_bitmap(	pvariables -> fondoimg[(pauxpar -> nivel)],(pauxpar -> auxfondox)-800,0,0);
	al_draw_bitmap(	pvariables -> fondoimg[(pauxpar -> nivel)],(pauxpar -> auxfondox)+220,0,0);
	al_draw_bitmap(	pvariables -> fondoimg[(pauxpar -> nivel)],(pauxpar -> auxfondox)+1240,0,0);
	
	al_draw_bitmap(pvariables -> pisoimg[(pauxpar -> nivel)],(pauxpar -> auxpisox),500,0);
	al_draw_bitmap(pvariables -> pisoimg[(pauxpar -> nivel)],(pauxpar -> auxpisox)+256,500,0);
	al_draw_bitmap(pvariables -> pisoimg[(pauxpar -> nivel)],(pauxpar -> auxpisox)+256*2,500,0);
	al_draw_bitmap(pvariables -> pisoimg[(pauxpar -> nivel)],(pauxpar -> auxpisox)+256*3,500,0);
	al_draw_bitmap(pvariables -> pisoimg[(pauxpar -> nivel)],(pauxpar -> auxpisox)+256*4,500,0);
	al_draw_bitmap(pvariables -> pisoimg[(pauxpar -> nivel)],(pauxpar -> auxpisox)+256*5,500,0);
	
/*	   al_draw_bitmap((pvariables -> bloqueimg)  ,(ppos -> bouncer_x5)+400,440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,(ppos -> bouncer_x5)+400+(62*1),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,(ppos -> bouncer_x5)+400+(62*2),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,(ppos -> bouncer_x5)+400+(62*3),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,(ppos -> bouncer_x5)+400+(62*4),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,(ppos -> bouncer_x5)+400+(62*5),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,(ppos -> bouncer_x5)+400+(62*6),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,(ppos -> bouncer_x5)+400+(62*7),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,(ppos -> bouncer_x5)+400+(62*8),440,100);
	*/
	
	//  al_draw_bitmap((pvariables -> enemigoimg), (ppos -> bouncer_x3),350,0);
	
	if((pauxpar -> tipo1) == 1){
		al_draw_bitmap_region((pvariables -> enemigoimg[(pauxpar -> nivel)]) ,0,0,140,150,(ppos -> bouncer_x31),355,0);
	}
    
    if((pauxpar -> tipo2) == 1){
		al_draw_bitmap_region((pvariables -> enemigoimg[(pauxpar -> nivel)]) ,0,0,140,150,(ppos -> bouncer_x32),355,0);
	}
    
    if((pauxpar -> tipo3) == 1){
		al_draw_bitmap_region((pvariables -> enemigoimg[(pauxpar -> nivel)]) ,0,0,140,150,(ppos -> bouncer_x33),355,0);
	}
	if((pauxpar -> tipo4) == 1){
		al_draw_bitmap_region((pvariables -> enemigoimg[6]) ,0,0,140,150,(ppos -> bouncer_x34),-15,0);
	}
	if((pauxpar -> tipo5) == 1){
		al_draw_bitmap_region((pvariables -> enemigoimg[6]) ,0,0,140,150,(ppos -> bouncer_x35),-15,0);
	}
	if((pauxpar -> tipo6) == 1){
		al_draw_bitmap_region((pvariables -> enemigoimg[6]) ,0,0,140,150,(ppos -> bouncer_x36),-15,0);
	}
	if((pauxpar -> tipo7) == 1){
		al_draw_bitmap_region((pvariables -> enemigoimg[7]) ,0,0,140,150,(ppos -> bouncer_x37),150,0);
	}
	if((pauxpar -> tipo8) == 1){
		al_draw_bitmap_region((pvariables -> enemigoimg[7]) ,0,0,140,150,(ppos -> bouncer_x38),150,0);
	}
	if((pauxpar -> tipo9) == 1){
		al_draw_bitmap_region((pvariables -> enemigoimg[7]) ,0,0,140,150,(ppos -> bouncer_x39),150,0);
	}
	
	//al_draw_bitmap_region((pvariables -> enemigoimg) ,(pauxpar -> auxspriteenemigo)*140,0,140,150,(ppos -> bouncer_x3),355,0);
		
	al_draw_bitmap_region((pvariables -> monedaimg), ((pfM -> curFrameMonedita) * (pfM -> frameWidthMonedita))-13, 0, (pfM -> frameWidthMonedita), (pfM -> frameHeightMonedita)+20,(ppos -> bouncer_x6),(ppos -> bouncer_y6), 0);
	
	al_draw_text((pvariables -> font), al_map_rgb(0, 255, 144), 580, 50, 0, (pauxpar -> scorec));
	
	al_draw_text((pvariables -> font), al_map_rgb(0, 255, 144), 880, 50, 0, (pauxpar -> nivelc));
		
	al_draw_bitmap_region((pvariables -> cuboimg),9+(97*(pauxpar -> auxspritecubox))-((pauxpar -> auxspritecubox)/4),55+(96*(pauxpar -> auxspritecuboy)),89,87,(ppos -> bouncer_x2)-200, (ppos -> bouncer_y2)+70,0);
	//al_draw_bitmap((pvariables -> cuboimg),(ppos -> bouncer_x2)-200, (ppos -> bouncer_y2)+115,0);
	
	if((ppos -> bouncer_x31)<(ppos -> bouncer_x2)-125&&(ppos -> bouncer_x31)>(ppos -> bouncer_x2)-330){	   
	if((ppos -> bouncer_y2)>150)		      	
			(pauxpar -> auxcolision)=1;	
	}
	if((ppos -> bouncer_x32)<(ppos -> bouncer_x2)-125&&(ppos -> bouncer_x32)>(ppos -> bouncer_x2)-330){	   
	if((ppos -> bouncer_y2)>150)		      	
			(pauxpar -> auxcolision)=1;	
	}
	if((ppos -> bouncer_x33)<(ppos -> bouncer_x2)-125&&(ppos -> bouncer_x33)>(ppos -> bouncer_x2)-330){	   
	if((ppos -> bouncer_y2)>150)		      	
			(pauxpar -> auxcolision)=1;	
	}
    if((ppos -> bouncer_x34)<(ppos -> bouncer_x2)-125&&(ppos -> bouncer_x34)>(ppos -> bouncer_x2)-330){	   
	if((ppos -> bouncer_y2)<-50)		      	
			(pauxpar -> auxcolision)=1;	
	}
	if((ppos -> bouncer_x35)<(ppos -> bouncer_x2)-125&&(ppos -> bouncer_x35)>(ppos -> bouncer_x2)-330){	   
	if((ppos -> bouncer_y2)<-50)		      	
			(pauxpar -> auxcolision)=1;	
	}
	if((ppos -> bouncer_x36)<(ppos -> bouncer_x2)-125&&(ppos -> bouncer_x36)>(ppos -> bouncer_x2)-330){	   
	if((ppos -> bouncer_y2)<-50)		      	
			(pauxpar -> auxcolision)=1;	
	}
    if((ppos -> bouncer_x37)<(ppos -> bouncer_x2)-125&&(ppos -> bouncer_x37)>(ppos -> bouncer_x2)-330){	   
	if((ppos -> bouncer_y2)>-10&&(ppos -> bouncer_y2)<190)		      	
			(pauxpar -> auxcolision)=1;	
	}
	if((ppos -> bouncer_x38)<(ppos -> bouncer_x2)-125&&(ppos -> bouncer_x38)>(ppos -> bouncer_x2)-330){	   
	if((ppos -> bouncer_y2)>-10&&(ppos -> bouncer_y2)<190)		      	
			(pauxpar -> auxcolision)=1;	
	}
	if((ppos -> bouncer_x39)<(ppos -> bouncer_x2)-125&&(ppos -> bouncer_x39)>(ppos -> bouncer_x2)-330){	   
	if((ppos -> bouncer_y2)>-10&&(ppos -> bouncer_y2)<190)		      	
			(pauxpar -> auxcolision)=1;	
	}
		
	if((pauxpar -> auxcolision)==1){
			//al_stop_samples();
			al_play_sample((pvariables -> explosionsfx), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			//al_play_sample((pvariables -> monedasfx), 1.0, 0.0,2.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			al_draw_bitmap_region((pvariables -> explosionimg), ((pfE -> curFrameExplosion) * (pfE -> frameWidthExplosion))-59, 0, (pfE -> frameWidthExplosion), (pfE -> frameHeightExplosion)+20,(ppos -> bouncer_x2)-300, (ppos -> bouncer_y2)+30, 0);
			

			(pauxpar -> auxspriteenemigo)=0;
			
			if((pauxpar -> verifvida)==0)
				{
				(pauxpar -> vida) = (pauxpar -> vida) - 1;
				(pauxpar -> verifvida)=1;	
				}
				(pauxpar -> verifvida)=1;
		}else
		{
			(pauxpar -> verifvida)=0;
			}
		
	if((pfE -> curFrameExplosion)==9)
	{      
		//al_destroy_sample((pvariables -> explosionsfx));

		(pauxpar -> auxcolision)=0;
		
		(pauxpar -> auxspriteenemigo)=1;
		
	}
		
		if((ppos -> bouncer_x6)<(ppos -> bouncer_x2)-100&&(ppos -> bouncer_x6)>(ppos -> bouncer_x2)-200){	   
		if((ppos -> bouncer_y6)<(ppos -> bouncer_y2)+100&&(ppos -> bouncer_y6)>(ppos -> bouncer_y2)){
			(pauxpar -> auxmoneda2)=1;
			
			
			}
		}
		if((pauxpar -> auxmoneda2)==1){   
			(pauxpar -> score) = (pauxpar -> score)+100; 
			(ppos -> bouncer_x6)= (ppos -> bouncer_x6)+1500;
			al_stop_samples();
			al_play_sample((pvariables -> monedasfx), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			//al_play_sample((pvariables -> explosionsfx), 1.0, 0.0,2.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			(pauxpar -> auxmoneda2)=0;
		}
		
		
		
		al_draw_text((pvariables -> font), al_map_rgb(0, 255, 0), 280, 50, 0, (pauxpar -> vidac));
		al_draw_text((pvariables -> font), al_map_rgb(0, 255, 0), 210, 50, 0, "Vidas:");
		al_draw_text((pvariables -> font), al_map_rgb(0, 255, 144), 580, 50, 0, (pauxpar -> scorec));
		al_draw_text((pvariables -> font), al_map_rgb(0, 255, 144), 510, 50, 0, "Score:");
		al_draw_text((pvariables -> font), al_map_rgb(0, 255, 255), 880, 50, 0, (pauxpar -> nivelc));
		al_draw_text((pvariables -> font), al_map_rgb(0, 255, 255), 810, 50, 0, "Nivel:");
		
		al_flip_display();
		
	}
	
	if (pauxestadojuego == 2){					// Antes de salir frena el timer
	
		al_stop_timer((pvariables -> timer));
	
	}
	
	return pauxestadojuego;

}

int fin (ini_var **fvar, auxpartida *fauxpar, variablescliente *fvarcl) {

	ini_var *fvariables;

	bool fredraw = true;
		
	int fauxestadojuego = 2;
	int fauxopcionessalir,fauxopcionesvolver;
	int fauxx, fauxy;	//mouse
	char faux3[11], faux4[11];
	
	int j;						// Contador para el for de envio de vida 
		
	fvariables = *(fvar);
	
	al_stop_samples();
	
	al_start_timer((fvariables -> timer));

	al_wait_for_event((fvariables -> event_queue), &(fvariables -> ev));
	
	if((fvariables -> ev).mouse.x>0 && (fvariables -> ev).mouse.x<1280&&(fvariables -> ev).mouse.y>0 && (fvariables -> ev).mouse.y<720){
		fauxx=(fvariables -> ev).mouse.x;
		fauxy=(fvariables -> ev).mouse.y;
	}
	
	sprintf(faux3, "%d", fauxx);
	sprintf(faux4, "%d", fauxy);
		
	if(fauxx>355 && fauxx<750&&fauxy>400 && fauxy<560) {
		fauxopcionesvolver=400;
	}
	else{
		fauxopcionesvolver=0;
	} 	
			
		
	if(fauxx>406 && fauxx<613 && fauxy>602 && fauxy<671)
	{
					fauxopcionessalir=215;
				}
				else{
						fauxopcionessalir=0;
					} 	
			
			
	
	if((fvariables -> ev).type == ALLEGRO_EVENT_TIMER) {
		fredraw = true;
	}
	else if((fvariables -> ev).type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return -1;
	}
	else if((fvariables -> ev).type == ALLEGRO_EVENT_MOUSE_AXES ||
			(fvariables -> ev).type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
	
		
	}
	else if((fvariables -> ev).type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		if(fauxx>406 && fauxx<613&&fauxy>602 && fauxy<671)
				fauxestadojuego = -1;
		if(fauxx>355 && fauxx<750&&fauxy>400 && fauxy<560)
				fauxestadojuego = 1;
			
	}
	
	
	
	if(fredraw && al_is_event_queue_empty((fvariables -> event_queue))) {
		fredraw = false;
	
		al_clear_to_color(al_map_rgb(0,0,0));
		
		//al_play_sample((fvariables -> temamenu), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		
		// al_draw_bitmap((fvariables -> fondomenuimg),0,0,0);
	
		//al_draw_bitmap_region((fvariables -> opcionesmenuimg),0+fauxopcionesjugar,0,260,95,457,500,0);
		
		al_draw_bitmap((fvariables -> fondoimg[6]),-600,0,0);
		al_draw_bitmap((fvariables -> fondoimg[6]),420,0,0);
			
		al_draw_bitmap((fvariables -> muertofinimg) ,790,330,0);
		
		al_draw_bitmap_region((fvariables -> volverimg),0+fauxopcionesvolver,0,400,400,350,390,0);
		al_draw_bitmap_region((fvariables -> opcionesmenuimg),0+fauxopcionessalir,90,210,90,400,590,0);
		
		/*al_draw_text((fvariables -> font), al_map_rgb(255, 0, 255), 50, 50, 0, faux3);
		al_draw_text((fvariables -> font), al_map_rgb(255, 0, 255), 10, 50, 0, "X:");
		al_draw_text((fvariables -> font), al_map_rgb(255, 0, 255), 50, 100, 0, faux4);
		al_draw_text((fvariables -> font), al_map_rgb(255, 0, 255), 10, 100, 0, "Y:");*/
		
		al_draw_text((fvariables -> font2), al_map_rgb(255, 0, 0), 280, 50, 0, "TE QUEDASTE SIN VIDAS MANCO");
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 144), 750, 300, 0, (fauxpar -> scorec));
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 144), 380, 300, 0, "TU SCORE FINAL:");
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 255), 900, 150, 0, (fauxpar -> nivelc));
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 255), 280, 150, 0, "LLEGASTE HASTA EL NIVEL:");
		
		al_flip_display();
	
	}

	if((fvariables -> ev).type == ALLEGRO_EVENT_TIMER) {
		
		if((fvariables -> ev).timer.source == (fvariables -> timer2)) {
	
			if ((fvarcl -> netflag) == 1){
								
				put_network_data((fvarcl -> sockfd), (fvarcl -> buffercl), (fvarcl -> buffercl2), (fvarcl -> buffercl3), (fvarcl -> buffercl4), (fvarcl -> buffercl5), VERDADERO, VERDADERO, VERDADERO, VERDADERO, VERDADERO , (fauxpar -> score) , (fauxpar -> vida));	// Manda por red fin del juego y puntaje final
			
			}
			
		}
		
	}	
	
	if (fauxestadojuego == -1){							// Antes de salir:
		
		if ((fvarcl -> netflag) == 1){

			for (j = 0 ; j < 4 ; j ++) {				// Manda varias veces para evitar errores de socket
			
				put_network_data((fvarcl -> sockfd), (fvarcl -> buffercl), (fvarcl -> buffercl2), (fvarcl -> buffercl3), (fvarcl -> buffercl4), (fvarcl -> buffercl5), VERDADERO, VERDADERO, VERDADERO, VERDADERO, VERDADERO , VERDADERO , VACIO);	// Manda por red volver a jugar
			
			}
		}		
		
	}
	
	if (fauxestadojuego == 1){							// Antes de salir:
	
		al_stop_timer((fvariables -> timer));			// Frena el timer
		
		if ((fvarcl -> netflag) == 1){

			for (j = 0 ; j < 4 ; j ++) {				// Manda varias veces para evitar errores de socket
			
				put_network_data((fvarcl -> sockfd), (fvarcl -> buffercl), (fvarcl -> buffercl2), (fvarcl -> buffercl3), (fvarcl -> buffercl4), (fvarcl -> buffercl5), VERDADERO, VERDADERO, VERDADERO, VERDADERO, VERDADERO , VACIO , VERDADERO);	// Manda por red volver a jugar
			
			}
		
		}
	
	}	
	
	return fauxestadojuego;
	
}

// Funcion de inicializacion Cliente

int inicializar_cl (variablescliente *varcl){
	
	(varcl -> netflag) = 0;
	(varcl -> cx_stat) = 0;

/*    if ((varcl -> cantarg) < 2) {
       fprintf(stderr,"usage %s hostname\n", (varcl -> strarg)[0]);
       exit(0);
    }
*/
    (varcl -> sockfd) = socket(AF_INET, SOCK_STREAM, 0);

    if ((varcl -> sockfd) < 0) 
        error("ERROR opening socket");

    (varcl -> server) = gethostbyname((varcl -> hostname));

    if ((varcl -> server) == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    memset((void *) &(varcl -> serv_addr), '\0', sizeof(varcl -> serv_addr));

    (varcl -> serv_addr).sin_family = AF_INET;

    bcopy((char *)(varcl -> server)->h_addr, 
         (char *)&(varcl -> serv_addr).sin_addr.s_addr,
         (varcl -> server) -> h_length);

    (varcl -> serv_addr).sin_port = htons(PUERTO);

    if (connect((varcl -> sockfd),(struct sockaddr *) &(varcl -> serv_addr),sizeof((varcl -> serv_addr))) < 0){
		 
		error("ERROR connecting");
		
		return 0;
		
	}

	return 1;				// Si logro la cx devuelve 1
	
}

int Niveles (auxpartida **naxpartida) {
	
	FILE *fp[2];
		
	auxpartida *nauxpar;
	niveles *aux_new, *aux_ant;
	
	int m;
	
	char buffer[30];
	
	nauxpar = *(naxpartida);
	
	fp[0] = fopen("N","r");					// Mapa 1
	if (!fp[0]) return -1;

	fp[1] = fopen("N2","r");				// Mapa 2
	if (!fp[1]) return -1;
	
	 //NIVEL
	for (m = 0 ; m < 2 ; m ++) {
		
		memset (buffer , 0 , 30);
		
		while (fgets(buffer , 30 , fp[m]) != NULL){ 
			
			if((nauxpar -> INI_niv[m]) == NULL){
				 
				aux_new = calloc (1, sizeof (niveles));
				aux_new -> t_aparicion = atoi (strtok(buffer,","));
				aux_new -> clase = atoi (strtok(NULL,","));
				aux_new -> sig = NULL;
				(nauxpar -> INI_niv[m]) = aux_new;
			}
			else { 
				aux_ant = (nauxpar -> INI_niv[m]);
				aux_new = calloc (1, sizeof (niveles));
				aux_new -> t_aparicion = atoi (strtok(buffer,","));
				aux_new -> clase = atoi (strtok(NULL,","));
				while (aux_ant -> sig != NULL){
						aux_ant = (aux_ant -> sig);
						}
				aux_new -> sig = NULL;
				aux_ant -> sig = aux_new;
					}
					
				memset (buffer, 0, 30);
				
			}

			fclose (fp[m]);
			
		}

	return 0;
				
	}

void Liberar (ini_var **lvar, variablescliente **lvarcl, auxpartida **laxpartida, frameExplosion **lfEx, frameMonedita **lfMo) {

	ini_var *lvariables;
	variablescliente *lvarcliente;
	auxpartida *lauxpar;
	frameExplosion *lfE;
	frameMonedita *lfM;

	niveles *laux;
	niveles *laux_ant;
	
	int lm;
	
	lvariables = *(lvar);
	lvarcliente = *(lvarcl);
	lauxpar = *(laxpartida);
	lfE = *(lfEx);
	lfM = *(lfMo);

// Libera lista de enemigos

	for (lm = 0 ; lm < 2 ; lm ++) {
		
		laux = (lauxpar -> INI_niv[lm]);
		
		while ((laux -> sig) != NULL){
			laux_ant = laux;
			free (laux_ant);
			laux = (laux -> sig);
			
		}
	
	}

// Libera variables de allegro
		
	al_destroy_timer(lvariables -> timer);
	al_destroy_display(lvariables -> display);
	al_destroy_event_queue(lvariables -> event_queue);
	
	al_destroy_sample(lvariables -> temamenu);
	al_destroy_sample(lvariables -> explosionsfx);
	al_destroy_sample(lvariables -> monedasfx);
	al_destroy_sample(lvariables -> levelsfx);	
	
	al_destroy_bitmap(lvariables -> fondoimg[0]);
	al_destroy_bitmap(lvariables -> fondoimg[1]);
	al_destroy_bitmap(lvariables -> fondoimg[2]);
	al_destroy_bitmap(lvariables -> fondoimg[3]);
	al_destroy_bitmap(lvariables -> fondoimg[4]);
	al_destroy_bitmap(lvariables -> fondoimg[5]);
	
	al_destroy_bitmap(lvariables -> pisoimg[0]);
	al_destroy_bitmap(lvariables -> pisoimg[1]);
	al_destroy_bitmap(lvariables -> pisoimg[2]);
	al_destroy_bitmap(lvariables -> pisoimg[3]);
	al_destroy_bitmap(lvariables -> pisoimg[4]);
	
	al_destroy_bitmap(lvariables -> cuboimg);
	
	al_destroy_bitmap(lvariables -> enemigoimg[0]);
	al_destroy_bitmap(lvariables -> enemigoimg[1]);
	al_destroy_bitmap(lvariables -> enemigoimg[2]);
	al_destroy_bitmap(lvariables -> enemigoimg[3]);
	al_destroy_bitmap(lvariables -> enemigoimg[4]);
	al_destroy_bitmap(lvariables -> enemigoimg[5]);
	al_destroy_bitmap(lvariables -> enemigoimg[6]);
	al_destroy_bitmap(lvariables -> enemigoimg[7]);
	 
	al_destroy_bitmap(lvariables -> muertofinimg);
	al_destroy_bitmap(lvariables -> monedaimg); 
	al_destroy_bitmap(lvariables -> volverimg);
	al_destroy_bitmap(lvariables -> explosionimg);
	al_destroy_bitmap(lvariables -> bloqueimg);
	
	al_destroy_bitmap(lvariables -> fondomenuimg);   
	al_destroy_bitmap(lvariables -> fondoipimg);
	al_destroy_bitmap(lvariables -> opcionesmenuimg);
	al_destroy_bitmap(lvariables -> jugarenlineaimg);
	
	al_destroy_font(lvariables -> font);
	al_destroy_font(lvariables -> font2);
	
	free (lvariables);
	free (lvarcliente);
	free (lauxpar);
	free (lfE);
	free (lfM);

}

int	GameLoop (ini_var **var, variablescliente **varcl, auxpartida **axpartida, frameExplosion **fEx, frameMonedita **fMo) {

	ini_var *variables;
	variablescliente *varcliente;
	auxpartida *auxpar;
	frameExplosion *fE;
	frameMonedita *fM;
	posicion *pos = malloc (sizeof (posicion));

	int r;						// Repetidor de red
			
	int auxestadojuego = 1;		// Arranca en el menu
	
	variables = *(var);
	varcliente = *(varcl);
	auxpar = *(axpartida);
	fE = *(fEx);
	fM = *(fMo);
			
	while (auxestadojuego != -1) {			// Si alguna etapa devuelve -1 cierra el juego
		
		while (auxestadojuego == 1){
			
			auxestadojuego = menu (&variables, auxpar);

		}

// Inicializacion de variables cargar_ip
		
		if (auxestadojuego == 3) {

			(varcliente -> tecla) = 0;
			(varcliente -> auxip) = 0;			
			(varcliente -> auxip2) = 0;
			(varcliente -> auxip3) = 0;
			(varcliente -> act) = 0;

			memset ((varcliente -> ip), 0, strlen (varcliente -> ip));
			memset ((varcliente -> ip2), 0, strlen (varcliente -> ip2));
			(variables -> key)[KEY_ENTER] = false;

		}
		
		while (auxestadojuego == 3){
			
			auxestadojuego = cargar_ip (&variables, &varcliente);

		}


		if (auxestadojuego != -1){
		
// Inicializacion de variables de posicion inicial

			(pos -> bouncer_x)= (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_y2)= (SCREEN_H) / 2.0 - (BOUNCER_SIZE) / 2.0;//piso
		
			(pos -> bouncer_x2) = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
		
			(pos -> bouncer_x31) = (SCREEN_W) / 2.0 + 900 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_x32) = (SCREEN_W) / 2.0 + 900 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_x33) = (SCREEN_W) / 2.0 + 900 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_x34) = (SCREEN_W) / 2.0 + 900 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_x35) = (SCREEN_W) / 2.0 + 900 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_x36) = (SCREEN_W) / 2.0 + 900 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_x37) = (SCREEN_W) / 2.0 + 900 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_x38) = (SCREEN_W) / 2.0 + 900 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_x39) = (SCREEN_W) / 2.0 + 900 - (BOUNCER_SIZE) / 2.0;
		
			(pos -> bouncer_x4) = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
		
			(pos -> bouncer_x5) = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;

			(pos -> bouncer_x6) = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_y6) = (SCREEN_H) / 2.0 - (BOUNCER_SIZE) / 2.0;//MONEDA
		
			(pos -> bouncer_dx) = -4.0;

			(variables -> key)[KEY_SPACE] = false;
			
// 	Inicializacion de vida y puntaje		
			
			(auxpar -> vida) = 3;		// Vida inicial
			(auxpar -> score) = 0;		// Puntaje comienza en 0
			(auxpar -> nivel) = 1;		// Dificultad inicial
			(auxpar -> t_nivel) = 0;	// Tiempo del nivel comienza en 0
			
// Inicializacion de enemigos

			(auxpar -> aux_niv) = (auxpar -> INI_niv[(auxpar -> map)]);			
			
			(auxpar -> tipo1) = 0;
			(auxpar -> tipo2) = 0;
			(auxpar -> tipo3) = 0;
			(auxpar -> tipo4) = 0;
			(auxpar -> tipo5) = 0;
			(auxpar -> tipo6) = 0;		
			(auxpar -> tipo7) = 0;
			(auxpar -> tipo8) = 0;
			(auxpar -> tipo9) = 0;
		}
			
		while (auxestadojuego == 0){
			
			auxestadojuego = partida (&variables, pos, auxpar, fE, fM, varcliente);

			if ((varcliente -> netflag) == 1){
							
				send_pos (&variables, varcliente, pos , auxpar);
			
			}
			
		} 
		
		while (auxestadojuego == 2){
			
			auxestadojuego = fin (&variables, auxpar, varcliente);

		}
		
	}
	
	free (pos);
	
	if ((varcliente -> netflag) == 1){
		
		close (varcliente -> sockfd);						// Cierra el socket
	
	}

	return 0;
	
}
