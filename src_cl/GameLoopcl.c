// GameLoop y sus funciones cliente

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

int menu (ini_var **mvar, int *mvida, int *mscore,int *mnivel) {

	ini_var *mvariables;

	int mauxestadojuego = 1;
	int mauxopcionessalir,mauxopcionesjugar,mauxopcionesvolver,mauxjugarenlinea;	//No se usa volver
	int mauxx, mauxy;	//mouse
	char maux3[11],maux4[11];
	
	bool mredraw = true;
	
	mvariables = *(mvar);

	*(mvida) = 3;
	*(mscore) = 0;
	*(mnivel) =1;

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
		if(mauxx > 454 && mauxx < 726 && mauxy > 499 && mauxy < 596)
				mauxestadojuego=0;
		if(mauxx > 354 && mauxx < 970 && mauxy > 610 && mauxy < 680) {
			mauxestadojuego=3;
		}
	}



	if(mredraw && al_is_event_queue_empty(mvariables -> event_queue)) {
		mredraw = false;

		al_clear_to_color(al_map_rgb(0,0,0));
		
				
		
		//al_play_sample((mvariables -> temamenu), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		
		al_draw_bitmap((mvariables -> fondomenuimg),0,0,0);
	
		al_draw_bitmap_region((mvariables -> opcionesmenuimg),0+mauxopcionesjugar,0,260,95,457,500,0);
		
		al_draw_bitmap_region((mvariables -> jugarenlineaimg),0,0+mauxjugarenlinea,650,95,350,590,0);
		
		al_draw_bitmap_region((mvariables -> opcionesmenuimg),0+mauxopcionessalir,90,210,90,1050,625,0);//y625 x1050 y+35 x + 71

/*
		al_draw_text((mvariables -> font), al_map_rgb(255, 0, 255), 50, 50, 0, maux3);
		al_draw_text((mvariables -> font), al_map_rgb(255, 0, 255), 10, 50, 0, "X:");
		al_draw_text((mvariables -> font), al_map_rgb(255, 0, 255), 50, 100, 0, maux4);
		al_draw_text((mvariables -> font), al_map_rgb(255, 0, 255), 10, 100, 0, "Y:");*/


		al_flip_display();
	}
	
	return mauxestadojuego;
}

int cargar_ip (ini_var **cvar, variablescliente *vcl) {

	ini_var *cvariables;
	
	
	int cauxestadojuego = 3;
	
	int tecla; // "tecla": Ind. que impide que hagas letras de mas.
	char *ip;
	char ip2[33];
	
	char auxip;
	int auxip2,auxip3,auxip4,act;//numero|cantidad de numeros|indicador prim. vez|?|indicador de tecla|
	
	if(auxip3!=1)
	{	
		auxip=0;
		act=0;
		auxip2=0;

		memset(ip2,0,33);
		
	}
	if(auxip2<9){					// Modificado para cargar localhost
			
			
		bool credraw = true;
		
		cvariables = *(cvar);

			
		al_wait_for_event((cvariables -> event_queue), &(cvariables -> ev));
		
		
		if((cvariables -> ev).type == ALLEGRO_EVENT_TIMER) {
			credraw = true;
				
			
			if((cvariables -> key)[KEY_1] ) {
				auxip='1';act=1;
			}  	  
			
			if((cvariables -> key)[KEY_2] ) {
				auxip='2';act=1;
			}	
			
			if((cvariables -> key)[KEY_3] ) {
				auxip='3';act=1;
					}	

			if((cvariables -> key)[KEY_4] ) {
				auxip='4';act=1;
					}	

			if((cvariables -> key)[KEY_5] ) {
				auxip='5';act=1;
			}	

			if((cvariables -> key)[KEY_6] ) {
				auxip='6';act=1; 
			}	

			if((cvariables -> key)[KEY_7] ) {
				auxip='7';act=1;
				 
			}	

			if((cvariables -> key)[KEY_8] ) {
				auxip='8';act=1;
			}	

			if((cvariables -> key)[KEY_9] ) {
				auxip='9';act=1;
					}	

			if((cvariables -> key)[KEY_0] ) {
				auxip='0';act=1;
			}	

			if((cvariables -> key)[KEY_FULLSTOP] ) {
				auxip='.';act=1;
			}	
			
			if(tecla!=1 && act==1){
					
					
					auxip2=auxip2+1;
					if(auxip3!=1)
					{	
						sprintf(ip, "%c",auxip);
						strcpy(ip2,ip);
					}
					else{
			
					sprintf(ip, "%c",auxip);
					strcat(ip2,ip);}
					auxip3=1;
				}tecla=1;act=0;

		}
			else if((cvariables -> ev).type == ALLEGRO_EVENT_KEY_DOWN) {
			switch((cvariables -> ev).keyboard.keycode) {
				
				case ALLEGRO_KEY_1:
				tecla=0;
				(cvariables -> key)[KEY_1] = true;
				break;
				case ALLEGRO_KEY_2:
				tecla=0;
				(cvariables -> key)[KEY_2] = true;
				break;
				case ALLEGRO_KEY_3:
				tecla=0;
				(cvariables -> key)[KEY_3] = true;
				break;
				case ALLEGRO_KEY_4:
				tecla=0;
				(cvariables -> key)[KEY_4] = true;
				break;
				case ALLEGRO_KEY_5:
				tecla=0;
				(cvariables -> key)[KEY_5] = true;
				break;
				case ALLEGRO_KEY_6:
				tecla=0;
				(cvariables -> key)[KEY_6] = true;
				break;
				case ALLEGRO_KEY_7:
				tecla=0;
				(cvariables -> key)[KEY_7] = true;
				break;
				case ALLEGRO_KEY_8:
				tecla=0;
				(cvariables -> key)[KEY_8] = true;
				break;
				case ALLEGRO_KEY_9:
				tecla=0;
				(cvariables -> key)[KEY_9] = true;
				break;
				case ALLEGRO_KEY_0:
				tecla=0;
				(cvariables -> key)[KEY_0] = true;
				break;
				case ALLEGRO_KEY_FULLSTOP:
				tecla=0;
				(cvariables -> key)[KEY_FULLSTOP] = true;
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
			al_draw_text((cvariables -> font2), al_map_rgb(0, 0, 255), 280, 100, 0, "Inserte su IP:");
			al_draw_text((cvariables -> font2), al_map_rgb(0, 0, 255), 300, 250, 0, ip2);
			//+(auxip2*30),

			al_flip_display();
		}

	} else {

		strcpy((vcl -> hostname), ip2);
				
		(vcl -> cx_stat) = inicializar_cl (vcl);
		
		if (vcl -> cx_stat) {
			
			(vcl -> netflag) = 1;				// Activa el flag de modo de red
			cauxestadojuego = 0;				// Si se conecta arranca la partida
			
		}
		
	}
	
	if (cauxestadojuego == 0){					// Antes de salir frena el timer
	
		al_stop_timer((cvariables -> timer));
	
	}	
	
	return cauxestadojuego;
}

/*	Funcion que manda todas las posiciones y velocidad por red
*
*	Manda en funcion del timer2 de un segundo. Entre envios de posiciones se demora para que no se sature el socket.
*/
int send_pos (ini_var **svar, variablescliente *svarcl, posicion *spos) {
	
	ini_var *svariables;	
	
	svariables = *(svar);

//	al_wait_for_event((svariables -> event_queue2), &(svariables -> ev2));
	
//	if((svariables -> ev2).type == (svariables -> timer2)) {

	if((svariables -> ev).type == ALLEGRO_EVENT_TIMER) {
						
		put_network_data2 ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), 'x', 0, (spos -> bouncer_x));
		al_rest(0.00001);
		put_network_data2 ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), 'x', 2, (spos -> bouncer_x2));
		al_rest(0.00001);
		put_network_data2 ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), 'y', 2, (spos -> bouncer_y2));
		al_rest(0.00001);
		put_network_data2 ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), 'x', 31, (spos -> bouncer_x31));
		al_rest(0.00001);
		put_network_data2 ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), 'x', 32, (spos -> bouncer_x32));
		al_rest(0.00001);
		put_network_data2 ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), 'x', 33, (spos -> bouncer_x33));
		al_rest(0.00001);
		put_network_data2 ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), 'x', 4, (spos -> bouncer_x4));
		al_rest(0.00001);
		put_network_data2 ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), 'x', 5, (spos -> bouncer_x5));
		al_rest(0.00001);
		put_network_data2 ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), 'x', 6, (spos -> bouncer_x6));
		al_rest(0.00001);
		put_network_data2 ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), 'y', 6, (spos -> bouncer_y6));
		al_rest(0.00001);
		put_network_data2 ((svarcl -> sockfd),(svarcl -> buffercl), (svarcl -> buffercl2), (svarcl -> buffercl3), 'd', 0, (spos -> bouncer_dx));		// Velocidad
	
	}
	
	return 0;
}

int partida (ini_var **pvar, int *pvida, int *pscore, int *pnivel, posicion *ppos, auxpartida *pauxpar, frameExplosion *pfE, frameMonedita *pfM, variablescliente *pvarcl) {

	ini_var *pvariables;

	bool predraw = true;	

	int pauxestadojuego = 0;

	pvariables = *(pvar);
	
	if(	*(pscore) >1000&&*(pscore) <2000)
	*(pnivel)=2;
	if(*(pscore) >2000&&*(pscore) <3000)
	*(pnivel)=3;
	if(*(pscore) >3000&&*(pscore) <4000)
	*(pnivel)=4;
	if(*(pscore) >4000&&*(pscore) <5000)
	*(pnivel)=5;
	
	if(*(pscore) == 1000 || *(pscore) == 2000 || *(pscore) == 3000 || *(pscore) == 4000)
	al_play_sample((pvariables -> levelsfx), 1.0, 0.0,1.2,ALLEGRO_PLAYMODE_ONCE,NULL);


	
	if ( !((pvariables -> key)[KEY_P])){
		
		al_start_timer((pvariables -> timer));
		
	}

	al_wait_for_event((pvariables -> event_queue), &(pvariables -> ev));

	if ( (pvariables -> key)[KEY_P]){					// Pausa
	
		al_stop_timer((pvariables -> timer));
	
	}

	if((pvariables -> ev).type == ALLEGRO_EVENT_TIMER) {
		
		
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
		
		if((pvariables -> key)[KEY_SPACE] ) {
			if( (ppos -> bouncer_y2) >= 339.0){
				(pauxpar -> aux1)=1;
			}  
				
		}
		else{
			(pauxpar -> aux1)=0;
			}
		if((pauxpar -> aux1)==0){
			if( (ppos -> bouncer_y2) <= 339.0)
				{
					(ppos -> bouncer_y2) += 8.0*10*(*(pnivel)*0.1);
				}
		}
		if((pauxpar -> aux1)==1){
			
		if( (ppos -> bouncer_y2) >= -110.0)
		{
			(ppos -> bouncer_y2) -= 8.0*10*(*(pnivel)*0.1);
			}
			else
			{
				(pauxpar -> aux1)=0;
			}   
		}
		//-------------------------------------------------
		
		
		
		
		
		
		//---------------------------------------------------
		
			
		if((ppos -> bouncer_x) < -256)              
			(ppos -> bouncer_x)= (ppos -> bouncer_x)+256; 
		(ppos -> bouncer_x) += (ppos -> bouncer_dx);
				
			
		if((ppos -> bouncer_x4) < -256)           
			(ppos -> bouncer_x4)= (ppos -> bouncer_x4)+1024; 
		(ppos -> bouncer_x4)+= (ppos -> bouncer_dx)/3;
						
			
		if((ppos -> bouncer_x31) < -256)                
			(ppos -> bouncer_x31)= (ppos -> bouncer_x31)+1556;
		(ppos -> bouncer_x31) += (ppos -> bouncer_dx)*20*(*(pnivel)*0.1);
		
        if((ppos -> bouncer_x32) < -256)                
			(ppos -> bouncer_x32)= (ppos -> bouncer_x32)+1556;
		(ppos -> bouncer_x32) += (ppos -> bouncer_dx)*10*(*(pnivel)*0.1);

        if((ppos -> bouncer_x33) < -256)                
			(ppos -> bouncer_x33)= (ppos -> bouncer_x33)+1556;
		(ppos -> bouncer_x33) += (ppos -> bouncer_dx)*5*(*(pnivel)*0.1);
		
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



			if(*(pvida)==0)
			{
				pauxestadojuego=2;
				
				
				
				}


			*(pscore) = *(pscore) + 1;
		//	(ppos -> bouncer_x2) -= 5;

		/*	if((ppos -> bouncer_x2) <= 0 - (pfE -> frameWidthExplosion))
				(ppos -> bouncer_x2) = (SCREEN_W);*/
			
			//-----------------------------------------------------------
		

		predraw = true;
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
				
				put_network_data((pvarcl -> sockfd), (pvarcl -> buffercl), KEY_UP, true);		// Manda por red tecla arriba
				
			}
			
			break;
			
			case ALLEGRO_KEY_SPACE:
			(pvariables -> key)[KEY_SPACE] = true;
			
			if ((pvarcl -> netflag) == 1){
				
				put_network_data((pvarcl -> sockfd), (pvarcl -> buffercl), KEY_SPACE, true);	// Manda por red barra espaciadora
				
			}			
			
			break;
			
			case ALLEGRO_KEY_P:
			
			if (!((pvariables -> key)[KEY_P])){
				(pvariables -> key)[KEY_P] = true;

				if ((pvarcl -> netflag) == 1){
				
					put_network_data((pvarcl -> sockfd), (pvarcl -> buffercl), KEY_P, true);	// Manda por red tecla P
				
				}
			
			} else if ((pvariables -> key)[KEY_P]) {					// Si se vuelve a apretar devuelve falso
				(pvariables -> key)[KEY_P] = false;
			
				if ((pvarcl -> netflag) == 1){
				
					put_network_data((pvarcl -> sockfd), (pvarcl -> buffercl), KEY_P, false);		// Manda por red tecla P
				
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
				
				put_network_data((pvarcl -> sockfd), (pvarcl -> buffercl), KEY_UP, false);		// Manda por red tecla arriba
				
			}
			
	
			break;
			
			case ALLEGRO_KEY_SPACE:
			(pvariables -> key)[KEY_SPACE] = false;

			if ((pvarcl -> netflag) == 1){
				
				put_network_data((pvarcl -> sockfd), (pvarcl -> buffercl), KEY_SPACE, false);	// Manda por red barra espaciadora
				
			}			

			break;
		}
	}

	if(predraw && al_is_event_queue_empty((pvariables -> event_queue))) {
		predraw = false;
		
		(pauxpar -> auxpisox)=(ppos -> bouncer_x);
		(pauxpar -> auxfondox)=(ppos -> bouncer_x4);
			
		sprintf((pauxpar -> vidac), "%d", *(pvida));
			
		
		//fprintf (stderr, "hasta aca anda \n");
		
		sprintf((pauxpar -> scorec), "%d", *(pscore)); //esto
		
			sprintf((pauxpar -> nivelc), "%d", *(pnivel)); //esto
		
		
	

		
		al_clear_to_color(al_map_rgb(0,0,0));
		
		//al_play_sample((pvariables -> temajuego), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

	//al_draw_bitmap(bouncer, (ppos -> bouncer_x), bouncer_y, 0);
	al_draw_bitmap(	pvariables -> fondoimg[*(pnivel)],(pauxpar -> auxfondox)-800,0,0);
	al_draw_bitmap(	pvariables -> fondoimg[*(pnivel)],(pauxpar -> auxfondox)+220,0,0);
	al_draw_bitmap(	pvariables -> fondoimg[*(pnivel)],(pauxpar -> auxfondox)+1240,0,0);
	
	al_draw_bitmap(pvariables -> pisoimg[*(pnivel)],(pauxpar -> auxpisox),500,0);
	al_draw_bitmap(pvariables -> pisoimg[*(pnivel)],(pauxpar -> auxpisox)+256,500,0);
	al_draw_bitmap(pvariables -> pisoimg[*(pnivel)],(pauxpar -> auxpisox)+256*2,500,0);
	al_draw_bitmap(pvariables -> pisoimg[*(pnivel)],(pauxpar -> auxpisox)+256*3,500,0);
	al_draw_bitmap(pvariables -> pisoimg[*(pnivel)],(pauxpar -> auxpisox)+256*4,500,0);
	al_draw_bitmap(pvariables -> pisoimg[*(pnivel)],(pauxpar -> auxpisox)+256*5,500,0);
	
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
	
	al_draw_bitmap_region((pvariables -> enemigoimg[*(pnivel)]) ,0,0,140,150,(ppos -> bouncer_x31),355,0);
    al_draw_bitmap_region((pvariables -> enemigoimg[*(pnivel)]) ,0,0,140,150,(ppos -> bouncer_x32),-10,0);
    al_draw_bitmap_region((pvariables -> enemigoimg[*(pnivel)]) ,0,0,140,150,(ppos -> bouncer_x33),150,0);
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
	if((ppos -> bouncer_y2)<-50)		      	
			(pauxpar -> auxcolision)=1;	
	}
    if((ppos -> bouncer_x33)<(ppos -> bouncer_x2)-125&&(ppos -> bouncer_x33)>(ppos -> bouncer_x2)-330){	   
	if((ppos -> bouncer_y2)>-10&&(ppos -> bouncer_y2)<190)		      	
			(pauxpar -> auxcolision)=1;	
	}
		
	if((pauxpar -> auxcolision)==1){
		
			al_play_sample((pvariables -> explosionsfx), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			//al_play_sample((pvariables -> monedasfx), 1.0, 0.0,2.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			al_draw_bitmap_region((pvariables -> explosionimg), ((pfE -> curFrameExplosion) * (pfE -> frameWidthExplosion))-59, 0, (pfE -> frameWidthExplosion), (pfE -> frameHeightExplosion)+20,(ppos -> bouncer_x2)-300, (ppos -> bouncer_y2)+30, 0);
			
			(pfE -> curFrameExplosion)==0;
			(pauxpar -> auxspriteenemigo)=0;
			
			if((pauxpar -> verifvida)==0)
				{
				*(pvida) = *(pvida) - 1;
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
		(pfE -> curFrameExplosion)==0;
		(pauxpar -> auxcolision)=0;
		
		(pauxpar -> auxspriteenemigo)=1;
		
	}
		
		if((ppos -> bouncer_x6)<(ppos -> bouncer_x2)-100&&(ppos -> bouncer_x6)>(ppos -> bouncer_x2)-200){	   
		if((ppos -> bouncer_y6)<(ppos -> bouncer_y2)+100&&(ppos -> bouncer_y6)>(ppos -> bouncer_y2)){
			(pauxpar -> auxmoneda2)=1;
			
			
			}
		}
		if((pauxpar -> auxmoneda2)==1){   
			*(pscore) = *(pscore)+100; 
			(ppos -> bouncer_x6)= (ppos -> bouncer_x6)+1500;
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

int fin (ini_var **fvar, auxpartida *pauxpar) {

	ini_var *fvariables;

	bool fredraw = true;
		
	int fauxestadojuego = 2;
	int fauxopcionessalir,fauxopcionesjugar,fauxopcionesvolver;
	int fauxx, fauxy;	//mouse
	char faux3[11], faux4[11];
		
	fvariables = *(fvar);

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
				return -1;
		if(fauxx>355 && fauxx<750&&fauxy>400 && fauxy<560)
				fauxestadojuego=1;
			
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
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 144), 750, 300, 0, (pauxpar -> scorec));
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 144), 380, 300, 0, "TU SCORE FINAL:");
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 255), 900, 150, 0, (pauxpar -> nivelc));
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 255), 280, 150, 0, "LLEGASTE HASTA EL NIVEL:");
		
		al_flip_display();
	
	}
	
	if (fauxestadojuego == 1){					// Antes de salir frena el timer
	
		al_stop_timer((fvariables -> timer));
	
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

/*
// Pantalla para ingresar la ip del servidor

int cargar_ip (ini_var **cvar, variablescliente *vcl) {		
	
	int cauxestadojuego = 3;
	
	(vcl -> cx_stat) = inicializar_cl (vcl);
	
	if (vcl -> cx_stat) {
		
		(vcl -> netflag) = 1;				// Activa el flag de modo de red
		cauxestadojuego = 0;				// Si se conecta arranca la partida
		
	}
	
	return cauxestadojuego;
	
}
*/
int	GameLoop (ini_var **var, variablescliente *varcliente) {

	ini_var *variables;

	posicion *pos = malloc (sizeof (posicion));
	auxpartida *auxpar = malloc (sizeof (auxpartida));
	frameExplosion *fE = malloc (sizeof (frameExplosion));
	frameMonedita *fM = malloc (sizeof (frameMonedita));
		
	int auxestadojuego = 1;		// Arranca en el menu

	int *vida = malloc (sizeof (int)); //*(vida) =5;  // inicializa en 5?
	int *score = malloc (sizeof (int)); *(score) =0;	
//	char *scores[10];	//No se usa mas
	int *nivel = malloc (sizeof (int)); *(nivel) =1;

// Inicializacion de variables partidas

	(auxpar -> verifvida) =0;
	
	(auxpar -> auxspriteenemigo) = 0;
	(auxpar -> auxspritecubox) = 0;
	(auxpar -> auxspritecubov) = 0;
	(auxpar -> auxspritecuboy) = 0;
	
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
	
	bool doexit = false;	//AL PEDO
	
	variables = *(var);
		
	while (auxestadojuego != -1) {			// Si alguna etapa devuelve -1 cierra el juego
		
		while (auxestadojuego == 1){
			
			auxestadojuego = menu (&variables, vida, score,nivel);

		}
		
		while (auxestadojuego == 3){
			
			auxestadojuego = cargar_ip (&variables, varcliente);

		}

		if (auxestadojuego != -1){
		
// Inicializacion de variables de posicion inicial

			(pos -> bouncer_x)= (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_y2)= (SCREEN_H) / 2.0 - (BOUNCER_SIZE) / 2.0;//piso
		
			(pos -> bouncer_x2) = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
		
			(pos -> bouncer_x31) = (SCREEN_W) / 2.0 + 900 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_x32) = (SCREEN_W) / 2.0 + 900 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_x33) = (SCREEN_W) / 2.0 + 900 - (BOUNCER_SIZE) / 2.0;
		
			(pos -> bouncer_x4) = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
		
			(pos -> bouncer_x5) = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;

			(pos -> bouncer_x6) = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
			(pos -> bouncer_y6) = (SCREEN_H) / 2.0 - (BOUNCER_SIZE) / 2.0;//MONEDA
		
			(pos -> bouncer_dx) = -4.0;
		
		}
			
		while (auxestadojuego == 0){
			
			auxestadojuego = partida (&variables, vida, score, nivel, pos, auxpar, fE, fM, varcliente);

			if ((varcliente -> netflag) == 1){
							
				send_pos (&variables, varcliente, pos);
			
			}
			
		} 
		
		while (auxestadojuego == 2){
			
			auxestadojuego = fin (&variables, auxpar);

		}
		
	}
	
	al_destroy_timer(variables -> timer);
	al_destroy_display(variables -> display);
	al_destroy_event_queue(variables -> event_queue);
	al_destroy_display(variables -> display);
	al_destroy_sample(variables -> temajuego);
	//al_destroy_bitmap(variables -> bouncer);
	
	/*al_destroy_bitmap(variables -> fondoimg1);
	al_destroy_bitmap(variables -> fondoimg2);
	al_destroy_bitmap(variables -> fondoimg3);
	al_destroy_bitmap(variables -> fondoimg4);
	al_destroy_bitmap(variables -> fondoimg5);*/
	
	/*al_destroy_bitmap(variables -> pisoimg1);
	al_destroy_bitmap(variables -> pisoimg2);
	al_destroy_bitmap(variables -> pisoimg3);
	al_destroy_bitmap(variables -> pisoimg4);
	al_destroy_bitmap(variables -> pisoimg5);*/
	al_destroy_bitmap(variables -> cuboimg);
	al_destroy_bitmap(variables -> enemigoimg );
	al_destroy_bitmap(variables -> explosionimg);
	al_destroy_bitmap(variables -> bloqueimg);
	
	return 0;
	

}
