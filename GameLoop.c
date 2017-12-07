// GameLoop y sus funciones

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
#include "datos.h"

	const int SCREEN_W = 1280;
	const int SCREEN_H = 720;
	const int BOUNCER_SIZE = 32;

int menu (ini_var **mvar, int *mvida, int *mscore,int *mnivel) {

	ini_var *mvariables;

	int mauxestadojuego = 1;
	int mauxopcionessalir,mauxopcionesjugar,mauxopcionesvolver;	//No se usa volver
	int mauxx, mauxy;	//mouse
	char maux3[11],maux4[11];
	
	bool mredraw = true;
	
	mvariables = *(mvar);

	*(mvida) = 3;
	*(mscore) = 0;
	*(mnivel) =1;
		
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
		
	
	if(mauxx > 485 && mauxx < 692 && mauxy > 602 && mauxy < 671) {

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
		if(mauxx > 485 && mauxx < 692 && mauxy > 602 && mauxy < 671)
			return -1;
		if(mauxx > 454 && mauxx < 726 && mauxy > 499 && mauxy < 596)
				mauxestadojuego=0;
			
	}



	if(mredraw && al_is_event_queue_empty(mvariables -> event_queue)) {
		mredraw = false;

		al_clear_to_color(al_map_rgb(0,0,0));
		
				
		
		//al_play_sample((mvariables -> temamenu), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		
		al_draw_bitmap((mvariables -> fondomenuimg),0,0,0);
	
		al_draw_bitmap_region((mvariables -> opcionesmenuimg),0+mauxopcionesjugar,0,260,95,457,500,0);
		al_draw_bitmap_region((mvariables -> opcionesmenuimg),0+mauxopcionessalir,90,210,90,479,590,0);


		al_draw_text((mvariables -> font), al_map_rgb(255, 0, 255), 50, 50, 0, maux3);
		al_draw_text((mvariables -> font), al_map_rgb(255, 0, 255), 10, 50, 0, "X:");
		al_draw_text((mvariables -> font), al_map_rgb(255, 0, 255), 50, 100, 0, maux4);
		al_draw_text((mvariables -> font), al_map_rgb(255, 0, 255), 10, 100, 0, "Y:");


		al_flip_display();
	}
	
	return mauxestadojuego;
}

int partida (ini_var **pvar, int *pvida, int *pscore, int *pnivel, posicion *ppos, auxpartida *pauxpar, frameExplosion *pfE, frameMonedita *pfM) {

	ini_var *pvariables;

	bool predraw = true;	

	int pauxestadojuego = 0;
	int pauxnivel;
	
	int auximagen;
	
	if(	*(pscore) >1000&&*(pscore) <2000)
	*(pnivel)=2;
	if(*(pscore) >2000&&*(pscore) <3000)
	*(pnivel)=3;
	if(*(pscore) >3000&&*(pscore) <4000)
	*(pnivel)=4;
	if(*(pscore) >4000&&*(pscore) <5000)
	*(pnivel)=5;
	
	

/*	
    if(	*(pscore) <1000)
		pauxnivel = 1;
	if(	*(pscore)>1000 && 	*(pscore) <2000)
		pauxnivel = 2;
	if(	*(pscore)>2000 && 	*(pscore) <300)
		pauxnivel = 3;
	if(	*(pscore)>3000 && 	*(pscore)<4000)
		pauxnivel = 4;
	if(	*(pscore)>4000 )
		pauxnivel = 5;
		*/
		
	
			switch(pauxnivel){	
		case 1:
			auximagen=0;
			break;
		case 2:
			auximagen=1;
			break;
		case 3:
			auximagen=2;
			break;
		case 4:
			auximagen=3;
			break;
		case 5:
			auximagen=4;
			break;
			}
	
	 
	

	const int maxFrameExplosion = 10;
	
	const int maxFrameMonedita= 4;
			
	pvariables = *(pvar);

	al_wait_for_event((pvariables -> event_queue), &(pvariables -> ev));

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
					(ppos -> bouncer_y2) += 8.0;
				}
		}
		if((pauxpar -> aux1)==1){
			
		if( (ppos -> bouncer_y2) >= -110.0)
		{
			(ppos -> bouncer_y2) -= 8.0;
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
						
			
		if((ppos -> bouncer_x3) < -256)                
			(ppos -> bouncer_x3)= (ppos -> bouncer_x3)+1556;
		(ppos -> bouncer_x3) += (ppos -> bouncer_dx)*2;
		
		
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
	} 
	else if((pvariables -> ev).type == ALLEGRO_EVENT_KEY_DOWN) {
		switch((pvariables -> ev).keyboard.keycode) {
			
			case ALLEGRO_KEY_UP:
			(pvariables -> key)[KEY_UP] = true;
			break;
			case ALLEGRO_KEY_SPACE:
			(pvariables -> key)[KEY_SPACE] = true;
			break;
		}
	}
	else if((pvariables -> ev).type == ALLEGRO_EVENT_KEY_UP) {
		switch((pvariables -> ev).keyboard.keycode) {
			
			case ALLEGRO_KEY_UP:
			(pvariables -> key)[KEY_UP] = false;
			break;
			
			case ALLEGRO_KEY_SPACE:
			(pvariables -> key)[KEY_SPACE] = false;
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
	
		al_draw_bitmap_region((pvariables -> enemigoimg) ,(pauxpar -> auxspriteenemigo)*140,0,140,150,(ppos -> bouncer_x3),355,0);
		
	al_draw_bitmap_region((pvariables -> monedaimg), ((pfM -> curFrameMonedita) * (pfM -> frameWidthMonedita))-13, 0, (pfM -> frameWidthMonedita), (pfM -> frameHeightMonedita)+20,(ppos -> bouncer_x6),(ppos -> bouncer_y6), 0);
	
	al_draw_text((pvariables -> font), al_map_rgb(0, 255, 144), 580, 50, 0, (pauxpar -> scorec));
	
	al_draw_text((pvariables -> font), al_map_rgb(0, 255, 144), 880, 50, 0, (pauxpar -> nivelc));
		
		al_draw_bitmap_region((pvariables -> cuboimg),9+(97*(pauxpar -> auxspritecubox))-((pauxpar -> auxspritecubox)/4),55+(96*(pauxpar -> auxspritecuboy)),89,87,(ppos -> bouncer_x2)-200, (ppos -> bouncer_y2)+70,0);
	//al_draw_bitmap((pvariables -> cuboimg),(ppos -> bouncer_x2)-200, (ppos -> bouncer_y2)+115,0);
	
		if((ppos -> bouncer_x3)<(ppos -> bouncer_x2)-125&&(ppos -> bouncer_x3)>(ppos -> bouncer_x2)-330){	   
		if((ppos -> bouncer_y2)>150){   
			(pfE -> curFrameExplosion)==0;			      	
				(pauxpar -> auxcolision)=1;
				(pauxpar -> auxspriteenemigo)=0;
				if((pauxpar -> verifvida)==0)
				{
				*(pvida) = *(pvida) - 1;
				(pauxpar -> verifvida)=1;	
					}
				(pauxpar -> verifvida)=1;
				
			
			}
		}
		
	if((pauxpar -> auxcolision)==1){
				al_play_sample((pvariables -> explosionsfx), 1.0, 0.0,2.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		al_draw_bitmap_region((pvariables -> explosionimg), ((pfE -> curFrameExplosion) * (pfE -> frameWidthExplosion))-59, 0, (pfE -> frameWidthExplosion), (pfE -> frameHeightExplosion)+20,(ppos -> bouncer_x2)-300, (ppos -> bouncer_y2)+30, 0);
		
		}
	if((pfE -> curFrameExplosion)==9)
	{      
		//al_destroy_sample((pvariables -> explosionsfx));
		(pfE -> curFrameExplosion)==0;
		(pauxpar -> auxcolision)=0;
		
		(pauxpar -> auxspriteenemigo)=1;
		(pauxpar -> verifvida)=0;
		}
		
		if((ppos -> bouncer_x6)<(ppos -> bouncer_x2)-100&&(ppos -> bouncer_x6)>(ppos -> bouncer_x2)-200){	   
		if((ppos -> bouncer_y6)<(ppos -> bouncer_y2)+100&&(ppos -> bouncer_y6)>(ppos -> bouncer_y2)){
			(pauxpar -> auxmoneda2)=1;
			
			
			}
		}
		if((pauxpar -> auxmoneda2)==1){   
			*(pscore) = *(pscore)+100; 
			(ppos -> bouncer_x6)= (ppos -> bouncer_x6)+1500;
			//al_play_sample((pvariables -> monedasfx), 1.0, 0.0,2.0,ALLEGRO_PLAYMODE_ONCE,NULL);
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
		
		al_draw_text((fvariables -> font), al_map_rgb(255, 0, 255), 50, 50, 0, faux3);
		al_draw_text((fvariables -> font), al_map_rgb(255, 0, 255), 10, 50, 0, "X:");
		al_draw_text((fvariables -> font), al_map_rgb(255, 0, 255), 50, 100, 0, faux4);
		al_draw_text((fvariables -> font), al_map_rgb(255, 0, 255), 10, 100, 0, "Y:");
		
		al_draw_text((fvariables -> font2), al_map_rgb(255, 0, 0), 280, 50, 0, "TE QUEDASTE SIN VIDAS MANCO");
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 144), 750, 300, 0, (pauxpar -> scorec));
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 144), 380, 300, 0, "TU SCORE FINAL:");
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 255), 900, 150, 0, (pauxpar -> nivelc));
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 255), 280, 150, 0, "LLEGASTE HASTA EL NIVEL:");
		
		al_flip_display();
	
	}
	
	return fauxestadojuego;
	
}

int	GameLoop (ini_var **var) {

	ini_var *variables;

	posicion *pos = malloc (sizeof (posicion));
	auxpartida *auxpar = malloc (sizeof (auxpartida));
	frameExplosion *fE = malloc (sizeof (frameExplosion));
	frameMonedita *fM = malloc (sizeof (frameMonedita));
		
	int auxestadojuego = 1;		// Arranca en el menu

	int *vida = malloc (sizeof (int)); //*(vida) =5;  // inicializa en 5?
	int *score = malloc (sizeof (int)); *(score) =0;	
	char *scores[10];	
	int *nivel = malloc (sizeof (int)); *(nivel) =1;

// Inicializacion de variables partidas

	(pos -> bouncer_x)= (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
	(pos -> bouncer_y2)= (SCREEN_H) / 2.0 - (BOUNCER_SIZE) / 2.0;//piso

	(pos -> bouncer_x2) = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;

	(pos -> bouncer_x3) = (SCREEN_W) / 2.0 + 500 - (BOUNCER_SIZE) / 2.0;

	(pos -> bouncer_x4) = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;

	(pos -> bouncer_x5) = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;

	(pos -> bouncer_x6) = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
	(pos -> bouncer_y6) = (SCREEN_H) / 2.0 - (BOUNCER_SIZE) / 2.0;//MONEDA

	(pos -> bouncer_dx) = -4.0;
	
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
		
	while(1) {			// Si alguna etapa devuelve -1 cierra el juego
		
		if(auxestadojuego == 1){
			
			auxestadojuego = menu (&variables, vida, score,nivel);
		
			if (auxestadojuego == -1) {
			
				break;
			
			}

		}

		else if(auxestadojuego == 0){
			
			auxestadojuego = partida (&variables, vida, score,nivel, pos, auxpar, fE, fM);
		
			if (auxestadojuego == -1) {
			
				break;
			
			}
		
		} 
		
		else if(auxestadojuego == 2) {
			
			auxestadojuego = fin (&variables, auxpar);
			
			if (auxestadojuego == -1) {
			
				break;
			
			}

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
