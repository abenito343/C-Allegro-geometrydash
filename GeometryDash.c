#include <stdio.h> 
#include <allegro5/allegro.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"




const float FPS = 60;
const int SCREEN_W = 924;
const int SCREEN_H = 640;
const int BOUNCER_SIZE = 32;


enum MYKEYS {

   KEY_SPACE
};
 
int main(int argc, char **argv){
 
 
 
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *bouncer = NULL;
   
   

  
   ALLEGRO_BITMAP  *image   = NULL;//fondo
   ALLEGRO_BITMAP  *image2   = NULL;//piso
   ALLEGRO_BITMAP  *image3   = NULL;//cubo
   ALLEGRO_BITMAP  *image4   = NULL;//enemigo
   ALLEGRO_BITMAP  *image5   = NULL;//explosion
   
 
   float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//piso
   float bouncer_dx = -4.0, bouncer_dy = 4.0;
   float i,i2,i3;

   bool redraw = true;
   
   float bouncer_x2 = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y2 = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//cubo
   
   float bouncer_x3 = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y3 = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//enemigo
   
   float bouncer_x4 = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y4 = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//fondo
   
   
   
   int aux1, aux2;

	bool key[1] = { false };
  
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
 
   display = al_create_display(924,640);
 
   if(!display) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
                                 
                                 
      al_destroy_timer(timer);
      return 0;
   }
   
   
   image3 = al_load_bitmap("cubo.png");
 
   if(!image3) {
      al_show_native_message_box(display, "Error", "Error", "Failed to load image!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }
   al_set_target_bitmap(image3);
   // al_set_target_bitmap(image5);



 
   al_set_target_bitmap(al_get_backbuffer(display));
 
 
bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);

   if(!bouncer) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
   
  // al_set_target_bitmap(bouncer);
 
   al_clear_to_color(al_map_rgb(255, 0, 255));
 
 //  al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(bouncer);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));

 
   al_register_event_source(event_queue, al_get_keyboard_event_source());
 
   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);
   
   image = al_load_bitmap("fondo1.png");
   image2 = al_load_bitmap("piso.png");
   image4 = al_load_bitmap("enemigo.png"); 
   image5 = al_load_bitmap("explosion.png");
 
   if(!image) {
      al_show_native_message_box(display, "Error", "Error", "Failed to load image!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }
   
   
   
 
  while(1)
   {
	   
   
   
 
	   
	   
	   
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
		  
		  
		  //------------------------------------------------------
		  	  
		 if(key[KEY_SPACE] ) {
			 if( bouncer_y2 >= 300.0){
				aux1=1;
			}  
				
			/* if( bouncer_y >= 100.0)
		   {
            bouncer_y -= 8.0;
			}*/
			 
		 }
		 else{
			 aux1=0;
			 }
		 if(aux1==0){
			 if( bouncer_y2 <= 300.0)
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

 
     //   redraw = true;
      
		  
		  		  //-------------------------------------------------
		  
		  
		  
         if(bouncer_x < -256)  {
           //bouncer_dx = -bouncer_dx;
          //bouncer_dx = 6.0;         
          bouncer_x= bouncer_x+256; }
            bouncer_x += bouncer_dx;
            
              
         if(bouncer_x4 < -256)  {
           //bouncer_dx = -bouncer_dx;
          //bouncer_dx = 6.0;         
          bouncer_x4= bouncer_x4+1024; }
            bouncer_x4+= bouncer_dx/3;
            
            
            
            
         if(bouncer_x3 < -256)  {
                   
          bouncer_x3= bouncer_x+1256;
         }
            bouncer_x3 += bouncer_dx*2;
            
            
      /*   if( bouncer_x > SCREEN_W - BOUNCER_SIZE)
         {
			 bouncer_dx = -bouncer_dx;
			 
			 }*/
       /*  if(bouncer_y < 0 || bouncer_y > SCREEN_H - BOUNCER_SIZE) {
            bouncer_dy = -bouncer_dy;
            bouncer_dy = -4.0;
             
         }*/
       //  bouncer_y += bouncer_dy;
          
          
 
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      } 
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
			 
			 case ALLEGRO_KEY_SPACE:
               key[KEY_SPACE] = true;
               break;
			 

         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
			 
			 case ALLEGRO_KEY_SPACE:
              key[KEY_SPACE] = false;
               break;

         }
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
		
		i=bouncer_x;
		i2=bouncer_x4;
		/*i2=bouncer_x/2;
		
		
		 if(i2 > 0)  {
                   
          i2= i2+768;
           }*/
		
         al_clear_to_color(al_map_rgb(0,0,0));
         
   
  
         
         
			al_draw_bitmap(image,i2-800,0,0);
			al_draw_bitmap(image,i2+220,0,0);
		   al_draw_bitmap(image2,i,500,0);
		   al_draw_bitmap(image2,i+256,500,0);
		   al_draw_bitmap(image2,i+256*2,500,0);
		   al_draw_bitmap(image2,i+256*3,500,0);
		   al_draw_bitmap(image2,i+256*4,500,0);
		   al_draw_bitmap(image2,i+256*5,500,0);
		   
		   al_draw_bitmap(image4,bouncer_x3,350,0);
		   
		   // 
		   al_draw_bitmap(image3,bouncer_x2-200, bouncer_y2+115,0);
		   
		   
		  if(bouncer_x3<bouncer_x2-125&&bouncer_x3>bouncer_x2-330){
		   //bouncer_x3<bouncer_x2-120&&
		   
			   if(bouncer_y2>150)
			  al_draw_bitmap(image5,bouncer_x2-250, bouncer_y2+50,0);
		   
		   
		    
			}
         //al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
 
         al_flip_display();
         
         

      // al_rest(50);
      }
      


   }
   

 
 
  
 
   al_destroy_bitmap(bouncer);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 



 
   al_destroy_display(display);
   al_destroy_bitmap(image);
   al_destroy_bitmap(image2);
   
   al_destroy_bitmap(image3);
      al_destroy_bitmap(image4);
      al_destroy_bitmap(image5);
 
   return 0;
}
