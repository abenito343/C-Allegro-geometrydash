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

int menu (ini_var *mvariables, int *mvida, int *mscore) {

	int mauxestadojuego = 1;
	int mauxopcionessalir,mauxopcionesjugar,mauxopcionesvolver;
	int mauxx, mauxy;	//mouse
	char maux3[11],maux4[11];
	
	bool mredraw = true;


	*(mvida) = 3;
	*(mscore) = 0;
		
	al_wait_for_event((mvariables -> event_queue), &(mvariables -> ev));
	
	if((mvariables -> ev).mouse.x>0 && (mvariables -> ev).mouse.x<1280&&(mvariables -> ev).mouse.y>0 && (mvariables -> ev).mouse.y<720){
	mauxx=(mvariables -> ev).mouse.x;
	mauxy=(mvariables -> ev).mouse.y;
	}
	
	sprintf(maux3, "%d", mauxx);
	sprintf(maux4, "%d", mauxy);
	
	if(mauxx>454 && mauxx<726&&mauxy>499 && mauxy<596) {
		
		mauxopcionesjugar=265;
		
	}
	
	else{
			mauxopcionesjugar=0;
	} 	
		
	
	if(mauxx>485 && mauxx<692&&mauxy>602 && mauxy<671) {

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
		if(mauxx>485 && mauxx<692&&mauxy>602 && mauxy<671)
			return -1;
		if(mauxx>454 && mauxx<726&&mauxy>499 && mauxy<596)
				mauxestadojuego=0;
			
	}



	if(mredraw && al_is_event_queue_empty((mvariables -> event_queue))) {
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

int partida (ini_var *pvariables, int *pvida, int *pscore, char *pscores[]) {

	bool predraw = true;
	bool key[2] = { false , false};	

	int pauxestadojuego = 0;
	int pauxopcionessalir,pauxopcionesjugar,pauxopcionesvolver;
	int pauxx, pauxy;	//mouse
	char paux3[11],paux4[11];

	char vidac[2];
	int verifvida=0;
	
	int aux1, aux2;
	
	int auxmoneda1,auxmoneda2;

	const int maxFrameExplosion = 10;
	int curFrameExplosion = 0;
	int frameCountExplosion = 0;
	int frameDelayExplosion = 5;
	int frameWidthExplosion = 283;
	int frameHeightExplosion = 300;
	
	const int maxFrameMonedita= 4;
	int curFrameMonedita = 0;
	int frameCountMonedita = 0;
	int frameDelayMonedita = 10;
	int frameWidthMonedita = 46;
	int frameHeightMonedita = 46;

	float bouncer_x = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
	float bouncer_y = (SCREEN_H) / 2.0 - (BOUNCER_SIZE) / 2.0;//piso
	
	float bouncer_x2 = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
	float bouncer_y2 = (SCREEN_H) / 2.0 - (BOUNCER_SIZE) / 2.0;//cubo
	
	float bouncer_x3 = (SCREEN_W) / 2.0 + 500 - (BOUNCER_SIZE) / 2.0;
	float bouncer_y3 = (SCREEN_H) / 2.0 - (BOUNCER_SIZE) / 2.0;//enemigo
	
	float bouncer_x4 = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
	float bouncer_y4 = (SCREEN_H) / 2.0 - (BOUNCER_SIZE) / 2.0;//fondo
	
	
	float bouncer_x5 = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
	float bouncer_y5 = (SCREEN_H) / 2.0 - (BOUNCER_SIZE) / 2.0;//materiales
	
	
	float bouncer_x6 = (SCREEN_W) / 2.0 - (BOUNCER_SIZE) / 2.0;
	float bouncer_y6 = (SCREEN_H) / 2.0 - (BOUNCER_SIZE) / 2.0;//MONEDA
	
	float bouncer_dx = -4.0, bouncer_dy = 4.0;//VELOCIDAD
	
	float auxpisox,auxfondox,auxcolision,auxspriteenemigo,auxspritecubox=0,auxspritecubov=0,auxspritecuboy=0;



	al_wait_for_event((pvariables -> event_queue), &(pvariables -> ev));

	if((pvariables -> ev).type == ALLEGRO_EVENT_TIMER) {
		
		
		//-----------------------------------------------------	
		
		
		
		if(key[KEY_UP] ) {
			auxspritecubov=auxspritecubov+1;
			if(auxspritecubov==3){
				auxspritecubox=auxspritecubox+1;
				auxspritecubov=12;	
				}
		}  	  
		else{
			auxspritecubov=0;
			
		}
		if(auxspritecubox==12)
		{
			auxspritecubox=0;
			auxspritecuboy=auxspritecuboy+1;
		}
		if(auxspritecuboy==5)
			auxspritecuboy=0;
		
		if(key[KEY_SPACE] ) {
			if( bouncer_y2 >= 339.0){
				aux1=1;
			}  
				
		}
		else{
			aux1=0;
			}
		if(aux1==0){
			if( bouncer_y2 <= 339.0)
				{
					bouncer_y2 += 8.0;
				}
		}
		if(aux1==1){
			
		if( bouncer_y2 >= -110.0)
		{
			bouncer_y2 -= 8.0;
			}
			else
			{
				aux1=0;
			}   
		}
		//-------------------------------------------------
		
		
		
		
		
		
		//---------------------------------------------------
		
			
		if(bouncer_x < -256)              
			bouncer_x= bouncer_x+256; 
		bouncer_x += bouncer_dx;
				
			
		if(bouncer_x4 < -256)           
			bouncer_x4= bouncer_x4+1024; 
		bouncer_x4+= bouncer_dx/3;
						
			
		if(bouncer_x3 < -256)                
			bouncer_x3= bouncer_x3+1556;
		bouncer_x3 += bouncer_dx*2;
		
		
		if(bouncer_x5 < -956)                
			bouncer_x5= bouncer_x5+2056;
		bouncer_x5 += bouncer_dx;
		
		
		if(bouncer_x6 < 0)                
			bouncer_x6= bouncer_x6+1500;
		bouncer_x6 += bouncer_dx;
		
		
			
		if( bouncer_y6 >= 339.0){
			auxmoneda1=1;
		}  
		else{
			// auxmoneda1=0;
			}
			
		if(auxmoneda1==0){
			if( bouncer_y6 <= 339.0)
				{
					bouncer_y6 += 8.0;
				}
		}
		if(auxmoneda1==1){
			
		if( bouncer_y6 >= 0.0)
		{
			bouncer_y6 -= 8.0;
			}
			else
			{
				auxmoneda1=0;
			}   
		}
			
		//---------------------------------------------------- 
			
			if(++frameCountExplosion >= frameDelayExplosion)
			{
				if(++curFrameExplosion >= maxFrameExplosion)
					curFrameExplosion = 0;

				frameCountExplosion = 0;
			}


			if(++frameCountMonedita >= frameDelayMonedita )
			{
				if(++curFrameMonedita  >= maxFrameMonedita )
					curFrameMonedita  = 0;

				frameCountMonedita  = 0;
			}



			if(*(pvida)==0)
			{
				pauxestadojuego=2;
				
				
				
				}


			*(pscore) = *(pscore) + 1;
		//	bouncer_x2 -= 5;

		/*	if(bouncer_x2 <= 0 - frameWidthExplosion)
				bouncer_x2 = (SCREEN_W);*/
			
			//-----------------------------------------------------------
		

		predraw = true;
	}
	else if((pvariables -> ev).type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return -1;
	} 
	else if((pvariables -> ev).type == ALLEGRO_EVENT_KEY_DOWN) {
		switch((pvariables -> ev).keyboard.keycode) {
			
			case ALLEGRO_KEY_UP:
			key[KEY_UP] = true;
			break;
			case ALLEGRO_KEY_SPACE:
			key[KEY_SPACE] = true;
			break;
		}
	}
	else if((pvariables -> ev).type == ALLEGRO_EVENT_KEY_UP) {
		switch((pvariables -> ev).keyboard.keycode) {
			
			case ALLEGRO_KEY_UP:
			key[KEY_UP] = false;https://forums.warframe.com/topic/701033-argentenno-evento/
			break;
			
			case ALLEGRO_KEY_SPACE:
			key[KEY_SPACE] = false;
			break;
		}
	}

	if(predraw && al_is_event_queue_empty((pvariables -> event_queue))) {
		predraw = false;
		
		auxpisox=bouncer_x;
		auxfondox=bouncer_x4;
			
		sprintf(vidac, "%d", *(pvida));
		sprintf(*(pscores), "%d", *(pscore));
		
		
	

		
		al_clear_to_color(al_map_rgb(0,0,0));
		
		//al_play_sample((pvariables -> temajuego), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

	//al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
	al_draw_bitmap((pvariables -> fondoimg),auxfondox-800,0,0);
	al_draw_bitmap((pvariables -> fondoimg),auxfondox+220,0,0);
	al_draw_bitmap((pvariables -> fondoimg),auxfondox+1240,0,0);
	
	al_draw_bitmap((pvariables -> pisoimg),auxpisox,500,0);
	al_draw_bitmap((pvariables -> pisoimg),auxpisox+256,500,0);
	al_draw_bitmap((pvariables -> pisoimg),auxpisox+256*2,500,0);
	al_draw_bitmap((pvariables -> pisoimg),auxpisox+256*3,500,0);
	al_draw_bitmap((pvariables -> pisoimg),auxpisox+256*4,500,0);
	al_draw_bitmap((pvariables -> pisoimg),auxpisox+256*5,500,0);
	
/*	   al_draw_bitmap((pvariables -> bloqueimg)  ,bouncer_x5+400,440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,bouncer_x5+400+(62*1),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,bouncer_x5+400+(62*2),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,bouncer_x5+400+(62*3),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,bouncer_x5+400+(62*4),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,bouncer_x5+400+(62*5),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,bouncer_x5+400+(62*6),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,bouncer_x5+400+(62*7),440,100);
	al_draw_bitmap((pvariables -> bloqueimg)  ,bouncer_x5+400+(62*8),440,100);
	*/
	
	//  al_draw_bitmap((pvariables -> enemigoimg), bouncer_x3,350,0);
	
		al_draw_bitmap_region((pvariables -> enemigoimg) ,auxspriteenemigo*140,0,140,150,bouncer_x3,355,0);
		
	al_draw_bitmap_region((pvariables -> monedaimg), (curFrameMonedita * frameWidthMonedita)-13, 0, frameWidthMonedita, frameHeightMonedita+20,bouncer_x6,bouncer_y6, 0);
	//	al_draw_text(font, al_map_rgb(0, 255, 144), 580, 50, 0, *(pscores));
		
		al_draw_bitmap_region((pvariables -> cuboimg),9+(97*auxspritecubox)-(auxspritecubox/4),55+(96*auxspritecuboy),89,87,bouncer_x2-200, bouncer_y2+70,0);
	//al_draw_bitmap((pvariables -> cuboimg),bouncer_x2-200, bouncer_y2+115,0);
	
		if(bouncer_x3<bouncer_x2-125&&bouncer_x3>bouncer_x2-330){	   
		if(bouncer_y2>150){   
			curFrameExplosion==0;			      	
				auxcolision=1;
				auxspriteenemigo=0;
				if(verifvida==0)
				{
				*(pvida) = *(pvida) - 1;
				verifvida=1;	
					}
				verifvida=1;
				
			
			}
		}
		
	if(auxcolision==1){
				al_play_sample((pvariables -> explosionsfx), 1.0, 0.0,2.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		al_draw_bitmap_region((pvariables -> explosionimg), (curFrameExplosion * frameWidthExplosion)-59, 0, frameWidthExplosion, frameHeightExplosion+20,bouncer_x2-300, bouncer_y2+30, 0);
		
		}
	if(curFrameExplosion==9)
	{      
		//al_destroy_sample((pvariables -> explosionsfx));
		curFrameExplosion==0;
		auxcolision=0;
		
		auxspriteenemigo=1;
		verifvida=0;
		}
		
		if(bouncer_x6<bouncer_x2-100&&bouncer_x6>bouncer_x2-200){	   
		if(bouncer_y6<bouncer_y2+100&&bouncer_y6>bouncer_y2){
			auxmoneda2=1;
			
			
			}
		}
		if(auxmoneda2==1){   
			*(pscore) = *(pscore)+100;
			bouncer_x6= bouncer_x6+1500;
			al_play_sample((pvariables -> monedasfx), 1.0, 0.0,2.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			auxmoneda2=0;
		}
		
		
		
		al_draw_text((pvariables -> font), al_map_rgb(0, 255, 0), 280, 50, 0, vidac);
		al_draw_text((pvariables -> font), al_map_rgb(0, 255, 0), 210, 50, 0, "Vidas:");
		al_draw_text((pvariables -> font), al_map_rgb(0, 255, 144), 580, 50, 0, *(pscores));
		al_draw_text((pvariables -> font), al_map_rgb(0, 255, 144), 510, 50, 0, "Score:");
		
		al_flip_display();
		
	}
	
	return pauxestadojuego;

}

int fin (ini_var *fvariables, char *fscores[]) {

	bool fredraw = true;
		
	int fauxestadojuego = 2;
	int fauxopcionessalir,fauxopcionesjugar,fauxopcionesvolver;
	int fauxx, fauxy;	//mouse
	char faux3[11], faux4[11];

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
		
		al_draw_bitmap((fvariables -> fondoimg),-600,0,0);
		al_draw_bitmap((fvariables -> fondoimg),420,0,0);
		
			
		al_draw_bitmap((fvariables -> muertofinimg) ,790,330,0);
		
		al_draw_bitmap_region((fvariables -> volverimg),0+fauxopcionesvolver,0,400,400,350,390,0);
		al_draw_bitmap_region((fvariables -> opcionesmenuimg),0+fauxopcionessalir,90,210,90,400,590,0);
		
		al_draw_text((fvariables -> font), al_map_rgb(255, 0, 255), 50, 50, 0, faux3);
		al_draw_text((fvariables -> font), al_map_rgb(255, 0, 255), 10, 50, 0, "X:");
		al_draw_text((fvariables -> font), al_map_rgb(255, 0, 255), 50, 100, 0, faux4);
		al_draw_text((fvariables -> font), al_map_rgb(255, 0, 255), 10, 100, 0, "Y:");
		
		al_draw_text((fvariables -> font2), al_map_rgb(255, 0, 0), 280, 50, 0, "TE QUEDASTE SIN VIDAS MANCO");
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 144), 750, 300, 0, *(fscores));
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 144), 380, 300, 0, "TU SCORE FINAL:");
		
		al_flip_display();
	
	}
	
	return fauxestadojuego;
	
}

int	GameLoop (ini_var *variables) {

	
	int auxestadojuego = 1;		// Arranca en el menu

	int *vida = malloc (sizeof (int)); //*(vida) =5;  // inicializa en 5?
	int *score = malloc (sizeof (int)); *(score) =0;	
	char *scores[10];	

	bool doexit = false;	//AL PEDO


		
	while(1) {			// Si alguna etapa devuelve -1 cierra el juego
		
		if(auxestadojuego == 1){
			
			auxestadojuego = menu (variables, vida, score);
		
			if (auxestadojuego == -1) {
			
				break;
			
			}

		}

		else if(auxestadojuego == 0){
			
			auxestadojuego = partida (variables, vida, score, scores);
		
			if (auxestadojuego == -1) {
			
				break;
			
			}
		
		} 
		
		else if(auxestadojuego == 2) {
			
			auxestadojuego = fin (variables, scores);
			
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
	
	al_destroy_bitmap(variables -> fondoimg);
	al_destroy_bitmap(variables -> pisoimg);
	al_destroy_bitmap(variables -> cuboimg);
	al_destroy_bitmap(variables -> enemigoimg );
	al_destroy_bitmap(variables -> explosionimg);
	al_destroy_bitmap(variables -> bloqueimg);
	
	return 0;
	
	}
