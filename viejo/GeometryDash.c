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
#include "GeometryDash.h"


const float FPS = 60;
const int SCREEN_W = 1280;
const int SCREEN_H = 720;
const int BOUNCER_SIZE = 32;


enum MYKEYS {

   KEY_UP,KEY_SPACE
};
 
int main(int argc, char **argv){
 
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   //ALLEGRO_BITMAP *bouncer = NULL;
  
  
   ALLEGRO_BITMAP  *fondoimg   = NULL;//fondo
   ALLEGRO_BITMAP  *pisoimg   = NULL;//piso
   ALLEGRO_BITMAP  *cuboimg  = NULL;//cubo
   ALLEGRO_BITMAP  *enemigoimg   = NULL;//enemigo
   ALLEGRO_BITMAP  *explosionimg   = NULL;//explosion
   ALLEGRO_BITMAP  *bloqueimg   = NULL;//bloque
   ALLEGRO_BITMAP  *muertofinimg   = NULL; // muerto
   ALLEGRO_BITMAP  *monedaimg   = NULL; // moneda
   ALLEGRO_BITMAP  *volverimg   = NULL; // volver al menu
   
   
   ALLEGRO_SAMPLE *temajuego=NULL;  
   ALLEGRO_SAMPLE *explosionsfx=NULL;  
   ALLEGRO_SAMPLE *monedasfx=NULL;
   
   ALLEGRO_EVENT ev;
   
   // menu
   
   ALLEGRO_BITMAP  *fondomenuimg   = NULL; // fondo menu
   ALLEGRO_BITMAP  *opcionesmenuimg   = NULL; // opciones menu
   ALLEGRO_FONT   *font = NULL;
   ALLEGRO_FONT   *font2 = NULL;
   ALLEGRO_SAMPLE *temamenu=NULL;
   
   
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
 
   float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//piso
   
   float bouncer_x2 = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y2 = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//cubo
   
   float bouncer_x3 = SCREEN_W / 2.0 + 500 - BOUNCER_SIZE / 2.0;
   float bouncer_y3 = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//enemigo
   
   float bouncer_x4 = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y4 = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//fondo
   
   
   float bouncer_x5 = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y5 = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//materiales
   
   
   float bouncer_x6 = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y6 = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//MONEDA
   
   float bouncer_dx = -4.0, bouncer_dy = 4.0;//VELOCIDAD
  
   float auxpisox,auxfondox,auxcolision,auxspriteenemigo,auxspritecubox=0,auxspritecubov=0,auxspritecuboy=0;
   
   int auxopcionessalir,auxopcionesjugar,auxestadojuego=1,auxopcionesvolver;
   int auxx, auxy;//mouse
   char aux3[11],aux4[11];
   
   int vida =5;  
   char vidac[2]; 
   int verifvida=0;
   
   int score=0;
   char scores[10];
   
   
   
   int aux1, aux2;
   
   int auxmoneda1,auxmoneda2;
   
   bool redraw = true;
   bool key[2] = { false , false};
   bool doexit = false;
 
 
 
 
 
 
   if(!al_init()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
 
   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return 0;
   }
   
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
   
   if(!al_init_image_addon()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
   
   if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
   }
   
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
    temajuego= al_load_sample( "Forever Bound - Stereo Madness.wav" );
    explosionsfx = al_load_sample( "explosion.wav" );
    monedasfx = al_load_sample( "monedasfx.wav" );
    temamenu= al_load_sample( "DJVI - Back On Track.wav" );

   if (!temajuego){
      printf( "Audio clip sample not loaded!\n" ); 
      return -1;
   }
 
   display = al_create_display(1280,720);
   if(!display) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);                            
      al_destroy_timer(timer);
      return 0;
   }
   
   cuboimg = al_load_bitmap("cubos.png");
   if(!cuboimg) {
      al_show_native_message_box(display, "Error", "Error", "Failed to load image!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }
   al_set_target_bitmap(cuboimg);
 
   al_set_target_bitmap(al_get_backbuffer(display));
 
 
  /* bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   if(!bouncer) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }*/
  // al_set_target_bitmap(bouncer);
   al_clear_to_color(al_map_rgb(255, 0, 255));
 
 //  al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      //al_destroy_bitmap(bouncer);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   
   al_register_event_source(event_queue, al_get_mouse_event_source());

 
   al_register_event_source(event_queue, al_get_keyboard_event_source());
 
   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);
   
   fondoimg = al_load_bitmap("fondo1.png");
   pisoimg = al_load_bitmap("piso.png");
   enemigoimg  = al_load_bitmap("enemigo.png"); 
   explosionimg= al_load_bitmap("sprite_explosiones.png");
   bloqueimg   = al_load_bitmap("pared.png");
   fondomenuimg = al_load_bitmap("menu.jpg");
   opcionesmenuimg = al_load_bitmap("opciones.png");
   monedaimg = al_load_bitmap("monedita.png");
   volverimg = al_load_bitmap("volveralmenu.png");
   
   muertofinimg  = al_load_bitmap("muerto.png");
   al_convert_mask_to_alpha(explosionimg, al_map_rgb(106, 76, 48));
   
   al_init_font_addon();
   al_init_ttf_addon();
   
   font = al_load_font ("Lato-Black.ttf" , 24 , 0);
   font2 = al_load_font ("Strings Theory.otf" , 48 , 0);
 
   if(!fondoimg) {
      al_show_native_message_box(display, "Error", "Error", "Failed to load image!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }
   
   
   
 
  while(1)
   {
      
      if(auxestadojuego==1){
		  
		  vida=3;
		  score=0;
		  
      al_wait_for_event(event_queue, &ev);
      
     if(ev.mouse.x>0 && ev.mouse.x<1280&&ev.mouse.y>0 && ev.mouse.y<720){
      auxx=ev.mouse.x;
      auxy=ev.mouse.y;
	}
      
      sprintf(aux3, "%d", auxx);
      sprintf(aux4, "%d", auxy);
      
       if(auxx>454 && auxx<726&&auxy>499 && auxy<596)
  {
				auxopcionesjugar=265;
			}
			else{
					auxopcionesjugar=0;
				} 	
		
      
  if(auxx>485 && auxx<692&&auxy>602 && auxy<671)
  {
				auxopcionessalir=215;
			}
			else{
					auxopcionessalir=0;
				} 	
		
		
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
 
        
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		if(auxx>485 && auxx<692&&auxy>602 && auxy<671)
			 	break;
		 if(auxx>454 && auxx<726&&auxy>499 && auxy<596)
			 	auxestadojuego=0;
			
      }

 
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
 
         al_clear_to_color(al_map_rgb(0,0,0));
         
                  
        
		//al_play_sample(temamenu, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        
	    al_draw_bitmap(fondomenuimg,0,0,0);
	   
		al_draw_bitmap_region(opcionesmenuimg,0+auxopcionesjugar,0,260,95,457,500,0);
		al_draw_bitmap_region(opcionesmenuimg,0+auxopcionessalir,90,210,90,479,590,0);


		al_draw_text(font, al_map_rgb(255, 0, 255), 50, 50, 0, aux3);
		al_draw_text(font, al_map_rgb(255, 0, 255), 10, 50, 0, "X:");
		al_draw_text(font, al_map_rgb(255, 0, 255), 50, 100, 0, aux4);
		al_draw_text(font, al_map_rgb(255, 0, 255), 10, 100, 0, "Y:");
 
 
         al_flip_display();
      }
   }
   //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   else if(auxestadojuego==0){
      
      
      
      	 
      
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
		  
		  
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



			if(vida==0)
			{
				auxestadojuego=2;
				
				
				
				}


			score=score+1;
		//	bouncer_x2 -= 5;

		/*	if(bouncer_x2 <= 0 - frameWidthExplosion)
				bouncer_x2 = SCREEN_W;*/
            
            //-----------------------------------------------------------
          
 
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      } 
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
			 
			   case ALLEGRO_KEY_UP:
               key[KEY_UP] = true;
               break;
			 case ALLEGRO_KEY_SPACE:
               key[KEY_SPACE] = true;
               break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
			 
			   case ALLEGRO_KEY_UP:
               key[KEY_UP] = false;https://forums.warframe.com/topic/701033-argentenno-evento/
               break;
			 
			 case ALLEGRO_KEY_SPACE:
              key[KEY_SPACE] = false;
               break;
         }
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
		
		auxpisox=bouncer_x;
		auxfondox=bouncer_x4;
			
		sprintf(vidac, "%d", vida);
		sprintf(scores, "%d", score);
		
		
	

		
	    al_clear_to_color(al_map_rgb(0,0,0));
	    
        //al_play_sample(temajuego, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

	 //al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
	   al_draw_bitmap(fondoimg,auxfondox-800,0,0);
	   al_draw_bitmap(fondoimg,auxfondox+220,0,0);
	   al_draw_bitmap(fondoimg,auxfondox+1240,0,0);
	   
	   al_draw_bitmap(pisoimg,auxpisox,500,0);
	   al_draw_bitmap(pisoimg,auxpisox+256,500,0);
	   al_draw_bitmap(pisoimg,auxpisox+256*2,500,0);
	   al_draw_bitmap(pisoimg,auxpisox+256*3,500,0);
	   al_draw_bitmap(pisoimg,auxpisox+256*4,500,0);
	   al_draw_bitmap(pisoimg,auxpisox+256*5,500,0);
	   
/*	   al_draw_bitmap(bloqueimg  ,bouncer_x5+400,440,100);
	   al_draw_bitmap(bloqueimg  ,bouncer_x5+400+(62*1),440,100);
	   al_draw_bitmap(bloqueimg  ,bouncer_x5+400+(62*2),440,100);
	   al_draw_bitmap(bloqueimg  ,bouncer_x5+400+(62*3),440,100);
	   al_draw_bitmap(bloqueimg  ,bouncer_x5+400+(62*4),440,100);
	   al_draw_bitmap(bloqueimg  ,bouncer_x5+400+(62*5),440,100);
	   al_draw_bitmap(bloqueimg  ,bouncer_x5+400+(62*6),440,100);
	   al_draw_bitmap(bloqueimg  ,bouncer_x5+400+(62*7),440,100);
	   al_draw_bitmap(bloqueimg  ,bouncer_x5+400+(62*8),440,100);
	 */
	   
	 //  al_draw_bitmap(enemigoimg, bouncer_x3,350,0);
	   
	   	al_draw_bitmap_region(enemigoimg ,auxspriteenemigo*140,0,140,150,bouncer_x3,355,0);
	   	
	   al_draw_bitmap_region(monedaimg, (curFrameMonedita * frameWidthMonedita)-13, 0, frameWidthMonedita, frameHeightMonedita+20,bouncer_x6,bouncer_y6, 0);
	   //	al_draw_text(font, al_map_rgb(0, 255, 144), 580, 50, 0, scores);
	   	
	   	al_draw_bitmap_region(cuboimg,9+(97*auxspritecubox)-(auxspritecubox/4),55+(96*auxspritecuboy),89,87,bouncer_x2-200, bouncer_y2+70,0);
	   //al_draw_bitmap(cuboimg,bouncer_x2-200, bouncer_y2+115,0);
	   
	    if(bouncer_x3<bouncer_x2-125&&bouncer_x3>bouncer_x2-330){	   
		   if(bouncer_y2>150){   
			   curFrameExplosion==0;			      	
				auxcolision=1;
				auxspriteenemigo=0;
				if(verifvida==0)
				{
				vida=vida-1;
				verifvida=1;	
					}
				verifvida=1;
				
			
			}
		}
		
	   if(auxcolision==1){
		        al_play_sample(explosionsfx, 1.0, 0.0,2.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		al_draw_bitmap_region(explosionimg, (curFrameExplosion * frameWidthExplosion)-59, 0, frameWidthExplosion, frameHeightExplosion+20,bouncer_x2-300, bouncer_y2+30, 0);
		
		}
       if(curFrameExplosion==9)
       {      
		   //al_destroy_sample(explosionsfx);
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
			 score=score+100;
			 bouncer_x6= bouncer_x6+1500;
			  al_play_sample(monedasfx, 1.0, 0.0,2.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			  auxmoneda2=0;
		  }
		
		
		
		al_draw_text(font, al_map_rgb(0, 255, 0), 280, 50, 0, vidac);
		al_draw_text(font, al_map_rgb(0, 255, 0), 210, 50, 0, "Vidas:");
		al_draw_text(font, al_map_rgb(0, 255, 144), 580, 50, 0, scores);
		al_draw_text(font, al_map_rgb(0, 255, 144), 510, 50, 0, "Score:");
		
         al_flip_display();
         
      }
   }else if(auxestadojuego==2) //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   {
	   
	   
	    al_wait_for_event(event_queue, &ev);
      
     if(ev.mouse.x>0 && ev.mouse.x<1280&&ev.mouse.y>0 && ev.mouse.y<720){
      auxx=ev.mouse.x;
      auxy=ev.mouse.y;
	}
      
      sprintf(aux3, "%d", auxx);
      sprintf(aux4, "%d", auxy);
      
  if(auxx>355 && auxx<750&&auxy>400 && auxy<560)
  {
				auxopcionesvolver=400;
			}
			else{
					auxopcionesvolver=0;
				} 	
		
     
  if(auxx>406 && auxx<613 && auxy>602 && auxy<671)
  {
				auxopcionessalir=215;
			}
			else{
					auxopcionessalir=0;
				} 	
		
		
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
 
        
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		 if(auxx>406 && auxx<613&&auxy>602 && auxy<671)
			 	break;
		 if(auxx>355 && auxx<750&&auxy>400 && auxy<560)
			 	auxestadojuego=1;
			
      }

 
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
 
         al_clear_to_color(al_map_rgb(0,0,0));
         
                  
        
		//al_play_sample(temamenu, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        
	   // al_draw_bitmap(fondomenuimg,0,0,0);
	   
		//al_draw_bitmap_region(opcionesmenuimg,0+auxopcionesjugar,0,260,95,457,500,0);
		


	
 
 
         
	   al_draw_bitmap(fondoimg,-600,0,0);
	   al_draw_bitmap(fondoimg,420,0,0);
	   
	    
	    al_draw_bitmap(muertofinimg ,790,330,0);
	     
	    al_draw_bitmap_region(volverimg,0+auxopcionesvolver,0,400,400,350,390,0);
		al_draw_bitmap_region(opcionesmenuimg,0+auxopcionessalir,90,210,90,400,590,0);
	     
	    al_draw_text(font, al_map_rgb(255, 0, 255), 50, 50, 0, aux3);
		al_draw_text(font, al_map_rgb(255, 0, 255), 10, 50, 0, "X:");
		al_draw_text(font, al_map_rgb(255, 0, 255), 50, 100, 0, aux4);
		al_draw_text(font, al_map_rgb(255, 0, 255), 10, 100, 0, "Y:");
	    
		al_draw_text(font2, al_map_rgb(255, 0, 0), 280, 50, 0, "TE QUEDASTE SIN VIDAS MANCO");
		al_draw_text(font2, al_map_rgb(0, 255, 144), 750, 300, 0, scores);
		al_draw_text(font2, al_map_rgb(0, 255, 144), 380, 300, 0, "TU SCORE FINAL:");
	   
	   al_flip_display();
	   }
	   }
  }
   
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   al_destroy_display(display);
   al_destroy_sample(temajuego);
   //al_destroy_bitmap(bouncer);
   
   al_destroy_bitmap(fondoimg);
   al_destroy_bitmap(pisoimg);
   al_destroy_bitmap(cuboimg);
   al_destroy_bitmap(enemigoimg );
   al_destroy_bitmap(explosionimg);
   al_destroy_bitmap(bloqueimg);
 
   return 0;
}
