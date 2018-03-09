/*! \file GameLoopsv.c
    \brief GameLoop y sus funciones servidor.
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

int partida (ini_var **pvar, posicion *ppos, auxpartida *pauxpar, frameExplosion *pfE, frameMonedita *pfM) {

	ini_var *pvariables;

	bool predraw = true;	

	int pauxestadojuego = 0;
	
	pvariables = *(pvar);

	if(	(pauxpar -> t_nivel) >1000&&(pauxpar -> t_nivel) <2000)
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

/*	if((pauxpar -> score) == 1000 || (pauxpar -> score) == 2000 || (pauxpar -> score) == 3000 || (pauxpar -> score) == 4000)
	al_play_sample((pvariables -> levelsfx), 1.0, 0.0,1.2,ALLEGRO_PLAYMODE_ONCE,NULL);		//NO ANDA (Probar en distintas computadoras)
*/			

	if ( !((pvariables -> key)[KEY_P])){
		
		al_start_timer((pvariables -> timer));
		
	}

	al_wait_for_event((pvariables -> event_queue), &(pvariables -> ev));

// Pausa

	if ( (pvariables -> key)[KEY_P]){					
	
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
					(ppos -> bouncer_y2) += 8.0*10*((pauxpar -> nivel)*0.1);
				}
		}
		if((pauxpar -> aux1)==1){
			
		if( (ppos -> bouncer_y2) >= -110.0)
		{
			(ppos -> bouncer_y2) -= 8.0*10*((pauxpar -> nivel)*0.1);
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
	else if((pvariables -> ev).type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return -1;
	} 

	if(predraw && al_is_event_queue_empty((pvariables -> event_queue))) {
		predraw = false;
		
		(pauxpar -> auxpisox)=(ppos -> bouncer_x);
		(pauxpar -> auxfondox)=(ppos -> bouncer_x4);
			
		sprintf((pauxpar -> vidac), "%d", (pauxpar -> vida));
		
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
		al_draw_bitmap_region((pvariables -> enemigoimg[7]) ,0,0,140,150,(ppos -> bouncer_x37),-50,0);
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
		
			al_play_sample((pvariables -> explosionsfx), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			//al_play_sample((pvariables -> monedasfx), 1.0, 0.0,2.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			al_draw_bitmap_region((pvariables -> explosionimg), ((pfE -> curFrameExplosion) * (pfE -> frameWidthExplosion))-59, 0, (pfE -> frameWidthExplosion), (pfE -> frameHeightExplosion)+20,(ppos -> bouncer_x2)-300, (ppos -> bouncer_y2)+30, 0);
			
			(pauxpar -> auxspriteenemigo)=0;
			
			if((pauxpar -> verifvida)==0)
				{
//				(pauxpar -> vida) = (pauxpar -> vida) - 1;		// Colisiones desactivadas en el server
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

int fin (ini_var **fvar, auxpartida *fauxpar, variablesservidor *fvarsv) {

	ini_var *fvariables;

	bool fredraw = true;
		
	int fauxestadojuego = 2;
	int fauxx, fauxy;	//mouse
	char faux3[11], faux4[11];
		
	fvariables = *(fvar);

	if ((fvarsv -> flag) == true) {
		
		sprintf((fauxpar -> scorec), "%d", (fauxpar -> score)); 	// Actualiza el puntaje mostrado con lo ultimo recibido por red
		
		(fvarsv -> flag) = false;

	}
	
	al_start_timer((fvariables -> timer));


	al_wait_for_event((fvariables -> event_queue), &(fvariables -> ev));
	
	if((fvariables -> ev).mouse.x>0 && (fvariables -> ev).mouse.x<1280&&(fvariables -> ev).mouse.y>0 && (fvariables -> ev).mouse.y<720){
		fauxx=(fvariables -> ev).mouse.x;
		fauxy=(fvariables -> ev).mouse.y;
	}
	
	sprintf(faux3, "%d", fauxx);
	sprintf(faux4, "%d", fauxy);		
	
	if((fvariables -> ev).type == ALLEGRO_EVENT_TIMER) {
		fredraw = true;
	}
	else if((fvariables -> ev).type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return -1;
	}
	else if((fvariables -> ev).type == ALLEGRO_EVENT_MOUSE_AXES ||
			(fvariables -> ev).type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
	
		
	}
	
	sprintf((fauxpar -> scorec), "%d", (fauxpar -> score)); 	// Actualiza el puntaje mostrado
	
	
	if(fredraw && al_is_event_queue_empty((fvariables -> event_queue))) {
		fredraw = false;
	
		al_clear_to_color(al_map_rgb(0,0,0));
		
		
		al_draw_bitmap((fvariables -> fondoimg[6]),-600,0,0);
		al_draw_bitmap((fvariables -> fondoimg[6]),420,0,0);

		
			
		al_draw_bitmap((fvariables -> muertofinimg) ,790,330,0);
		
		
		al_draw_text((fvariables -> font2), al_map_rgb(255, 0, 0), 280, 50, 0, "TE QUEDASTE SIN VIDAS MANCO");
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 144), 750, 300, 0, (fauxpar -> scorec));
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 144), 380, 300, 0, "TU SCORE FINAL:");
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 255), 900, 150, 0, (fauxpar -> nivelc));
		
		al_draw_text((fvariables -> font2), al_map_rgb(0, 255, 255), 280, 150, 0, "LLEGASTE HASTA EL NIVEL:");
		
		al_flip_display();
	
	}
	
	if ((fauxpar -> vida) == VERDADERO) {				// Si recibe vida VERDADERO por red, vuelve a wait_cx
		
		fauxestadojuego = 1;
		
	}

	if ((fauxpar -> score) == VERDADERO) {				// Si recibe score VERDADERO por red, sale del juego
		
		fauxestadojuego = -1;
		
	}

	if (fauxestadojuego == 1){							// Antes de salir: 
	
		(fvarsv -> flag) = true;
		al_stop_timer((fvariables -> timer));			// Frena el timer

	}	
	
	return fauxestadojuego;
	
}

// Funcion de inicializacion Cliente

int wait_cx (variablesservidor *varsv, ini_var **wvar){


	ini_var *wvariables;
	
	wvariables = *(wvar);

    printf("Esperando jugador en red...\n");
    
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap((wvariables -> fondomenuimg),0,0,0);	
    al_draw_bitmap_region((wvariables -> esperandoimg),0,0,930,95,150,550,0);
    al_flip_display();
	
    // Llamado bloqueante a accept()
    (varsv -> newsockfd) = accept(varsv -> sockfd, (struct sockaddr *) &(varsv -> cli_addr), &(varsv -> clilen));
    if ((varsv -> newsockfd) < 0) error("ERROR on accept");
    printf("Conexion jugador aceptada!\n");

	return 0;				// Si logro la cx devuelve 0
	
}

int receive_data (ini_var **rvar, variablesservidor *varsv2, posicion *p, auxpartida *rauxpar) {

	ini_var *rvariables;
	
	rvariables = *(rvar);	

	(varsv2 -> net) = get_network_data((varsv2 -> newsockfd), (varsv2 -> buffersv), &(varsv2 -> status), &(varsv2 -> sentkey) , &(varsv2 -> eje), &(varsv2 -> number), &(varsv2 -> valpos) , &(varsv2 -> puntos) , &(varsv2 -> life));
																																													
																																													
	if((varsv2 -> net) == 1) {

// Recibe teclas por red
		
		switch(varsv2 -> sentkey) {
			case KEY_UP:
				if(varsv2 -> status){
					(rvariables -> key)[KEY_UP] = true;
				}
				else {
					(rvariables -> key)[KEY_UP] = false;
				}
				break;
				
			case KEY_SPACE:
				if(varsv2 -> status){
					(rvariables -> key)[KEY_SPACE] = true;
				}
				else {
					(rvariables -> key)[KEY_SPACE] = false;
				}
				break;
				
			case KEY_P:											// El cliente manda verdadero o falso por red
				if(varsv2 -> status){
					(rvariables -> key)[KEY_P] = true;
				}
				else {

					(rvariables -> key)[KEY_P] = false;
				}
				break;
				
/*			case KEY_EXIT:
				doexit = true;
				break;               
*/		}

// Recibe posicion por red

		switch(varsv2 -> eje) {
			case 'x':
				switch (varsv2 -> number) {
					
					case 0:
				
					(p -> bouncer_x) = (varsv2 -> valpos);
					break;
					
					case 2:
				
					(p -> bouncer_x2) = (varsv2 -> valpos);	
					break;				

					case 31:
				
					(p -> bouncer_x31) = (varsv2 -> valpos);	
					break;	

					case 32:
					
					(p -> bouncer_x32) = (varsv2 -> valpos);	
					break;	

					case 33:
					
					(p -> bouncer_x33) = (varsv2 -> valpos);	
					break;
					case 34:
					
					(p -> bouncer_x34) = (varsv2 -> valpos);	
					break;
					case 35:
					
					(p -> bouncer_x35) = (varsv2 -> valpos);	
					break;
					case 36:
					
					(p -> bouncer_x36) = (varsv2 -> valpos);	
					break;
					case 37:
					
					(p -> bouncer_x37) = (varsv2 -> valpos);	
					break;
					case 38:
					
					(p -> bouncer_x38) = (varsv2 -> valpos);	
					break;
					
					case 39:
					
					(p -> bouncer_x39) = (varsv2 -> valpos);	
					break;	

					case 4:
				
					(p -> bouncer_x4) = (varsv2 -> valpos);	
					break;	
					
					case 5:
				
					(p -> bouncer_x5) = (varsv2 -> valpos);	
					break;	
					
					case 6:
				
					(p -> bouncer_x6) = (varsv2 -> valpos);	
					break;	
					
				}
					
				break;
				
			case 'y':
			
				switch (varsv2 -> number) {
				
					case 2:
				
					(p -> bouncer_y2) = (varsv2 -> valpos);
					break;	
					
					case 6:
				
					(p -> bouncer_y6) = (varsv2 -> valpos);	
					break;		
				}								
				
				break;
				
			case 'd':
				
				(p -> bouncer_dx) = (varsv2 -> valpos);	
									
				break;				
				
		}
		
// Recibe los puntos y vida

		(rauxpar -> vida) = (varsv2 -> life);
		(rauxpar -> score) = (varsv2 -> puntos);		
			
	}

    return 0;
        
}

int Niveles (auxpartida **naxpartida) {
	
	FILE *fp;
	
	auxpartida *nauxpar;
	niveles *aux_new, *aux_ant;
	
	char buffer[30];
	
	nauxpar = *(naxpartida);
	
	fp = fopen("N","r");
	if (!fp) return -1;
	
	 //NIVEL
		memset (buffer,0,30);
		while (fgets(buffer,30,fp) != NULL){ 
			
			if((nauxpar -> INI_niv) == NULL){
				 
				aux_new = calloc (1, sizeof (niveles));
				aux_new -> t_aparicion = atoi (strtok(buffer,","));
				aux_new -> clase = atoi (strtok(NULL,","));
				aux_new -> sig = NULL;
				(nauxpar -> INI_niv) = aux_new;
			}
			else { 
				aux_ant = (nauxpar -> INI_niv);
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

	fclose (fp);

	return 0;
				
	}

void Liberar (ini_var **lvar, variablesservidor **lvarsv, auxpartida **laxpartida, frameExplosion **lfEx, frameMonedita **lfMo) {

	ini_var *lvariables;
	variablesservidor *lvarservidor;
	auxpartida *lauxpar;
	frameExplosion *lfE;
	frameMonedita *lfM;

	niveles *laux;
	niveles *laux_ant;
	
	lvariables = *(lvar);
	lvarservidor = *(lvarsv);
	lauxpar = *(laxpartida);
	lfE = *(lfEx);
	lfM = *(lfMo);

// Libera lista de enemigos
		
	laux = (lauxpar -> INI_niv);
	
	while ((laux -> sig) != NULL){
		laux_ant = laux;
		free (laux_ant);
		laux = (laux -> sig);
		
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
	free (lvarservidor);
	free (lauxpar);
	free (lfE);
	free (lfM);

}

int	GameLoop (ini_var **var, variablesservidor *varservidor, auxpartida **axpartida, frameExplosion **fEx, frameMonedita **fMo) {

	ini_var *variables;

	posicion *pos = malloc (sizeof (posicion));
	auxpartida *auxpar = malloc (sizeof (auxpartida));
	frameExplosion *fE = malloc (sizeof (frameExplosion));
	frameMonedita *fM = malloc (sizeof (frameMonedita));
		
	int auxestadojuego = 1;		// Arranca esperando la cx

	(varservidor -> flag) = true;
	
	variables = *(var);
	auxpar = *(axpartida);
	fE = *(fEx);
	fM = *(fMo);
		
	while (auxestadojuego != -1) {			// Si alguna etapa devuelve -1 cierra el juego
		
		while (auxestadojuego == 1){

			
			auxestadojuego = wait_cx (varservidor,&variables);
		
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
			(auxpar -> score) = 0;	    // Puntaje comienza en 0
			(auxpar -> nivel) = 1;      // Dificultad inicial
			(auxpar -> t_nivel) = 0;	// Tiempo del nivel comienza en 0
// Inicializacion de enemigos

			(auxpar -> aux_niv) = (auxpar -> INI_niv);			
			
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
			
			auxestadojuego = partida (&variables, pos, auxpar, fE, fM);
			
			receive_data (&variables, varservidor, pos, auxpar);
					
		} 
		
		while (auxestadojuego == 2){
			
			receive_data (&variables, varservidor, pos, auxpar);
			
			auxestadojuego = fin (&variables, auxpar, varservidor);

		}
		
	}

	free (pos);
		
	close (varservidor -> sockfd);						// Cierra el socket	
	
	return 0;
	
}
