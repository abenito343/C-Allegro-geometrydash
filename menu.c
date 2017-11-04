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


 
const float FPS = 60;
const int SCREEN_W = 1280;
const int SCREEN_H = 720;
const int BOUNCER_SIZE = 32;


 
int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP  *image   = NULL;
   ALLEGRO_BITMAP  *image2   = NULL;
   ALLEGRO_FONT   *font = NULL;
   ALLEGRO_SAMPLE *sample=NULL;
  
   float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
   int i1,i2;
   int auxx, auxy;
   
   char aux1[11],aux2[11];
   bool redraw = true;
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
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
   
   
    if(!al_init_image_addon()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
	
   if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
   }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }
	
   sample = al_load_sample( "DJVI - Back On Track.wav" );

   if (!sample){
      printf( "Audio clip sample not loaded!\n" ); 
      return -1;
   }
 
 
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }
    
   image = al_load_bitmap("menu.jpg");
   image2 = al_load_bitmap("opciones.png");
   if(!image) {
      al_show_native_message_box(display, "Error", "Error", "No carga la imagen!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }
   al_init_font_addon();
	al_init_ttf_addon();
 /* if(!al_init_ttf_addon()) {
	  fprintf(stderr, "se pudrio todo\n");
	  
	}*/
   
			int score =0;
			
         
          
          
 
          
        font = al_load_font ("Lato-Black.ttf" , 24 , 0);
 
 
 /*  bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   if(!bouncer) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }*/
 
   //al_set_target_bitmap(bouncer);
 
   al_clear_to_color(al_map_rgb(255, 0, 255));
 
   al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
   //   al_destroy_bitmap(bouncer);
      al_destroy_bitmap(image);
      al_destroy_bitmap(image2);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_mouse_event_source());
 
   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);
 
   while(1)
   {
	   
	   
	   
	   
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
      
     if(ev.mouse.x>0 && ev.mouse.x<1280&&ev.mouse.y>0 && ev.mouse.y<720){
      auxx=ev.mouse.x;
      auxy=ev.mouse.y;
	}
      //itoa(auxx,aux1,10);
      //itoa(auxy,aux2,10);
      sprintf(aux1, "%d", auxx);
      sprintf(aux2, "%d", auxy);
      
       if(auxx>454 && auxx<726&&auxy>499 && auxy<596)
  {
				i2=265;
			}
			else{
					i2=0;
				} 	
		
      
  if(auxx>485 && auxx<692&&auxy>602 && auxy<671)
  {
				i1=215;
			}
			else{
					i1=0;
				} 	
		
		
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
 
        //bouncer_x = ev.mouse.x;
        // bouncer_y = ev.mouse.y;
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		if(auxx>485 && auxx<692&&auxy>602 && auxy<671)
			 	break;
			
      }
 
	
	   
 
 
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
 
         al_clear_to_color(al_map_rgb(0,0,0));
         
         
         
         
		
          
        
		al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
        
          score +=10;
          
          
           al_draw_bitmap(image,0,0,0);
           
           	al_draw_bitmap_region(image2,0+i2,0,260,95,457,500,0);
           	al_draw_bitmap_region(image2,0+i1,90,210,90,479,590,0);
 
 
			al_draw_text(font, al_map_rgb(255, 0, 255), 50, 50, 0, aux1);
			al_draw_text(font, al_map_rgb(255, 0, 255), 10, 50, 0, "X:");
			al_draw_text(font, al_map_rgb(255, 0, 255), 50, 100, 0, aux2);
			al_draw_text(font, al_map_rgb(255, 0, 255), 10, 100, 0, "Y:");
 
     //    al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
 
         al_flip_display();
      }
   }
 
   //al_destroy_bitmap(bouncer);
   al_destroy_font(font);
   al_destroy_sample(sample);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   al_destroy_bitmap(image);
   al_destroy_bitmap(image2);
 
   return 0;
}
