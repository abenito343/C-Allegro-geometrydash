#include <stdio.h> 
#include <allegro5/allegro.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "GeometryDash.h"


const float FPS = 60;
const int SCREEN_W = 924;
const int SCREEN_H = 640;
const int BOUNCER_SIZE = 32;


enum MYKEYS {

   KEY_UP,KEY_SPACE
};
 
int main(int argc, char **argv){
 
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   //ALLEGRO_BITMAP *bouncer = NULL;
  
  
   ALLEGRO_BITMAP  *image   = NULL;//fondo
   ALLEGRO_BITMAP  *image2   = NULL;//piso
   ALLEGRO_BITMAP  *image3   = NULL;//cubo
   ALLEGRO_BITMAP  *image4   = NULL;//enemigo
   ALLEGRO_BITMAP  *image5   = NULL;//explosion
   ALLEGRO_BITMAP  *image6   = NULL;//explosion
   
	const int maxFrame = 10;
	int curFrame = 0;
	int frameCount = 0;
	int frameDelay = 5;
	int frameWidth = 283;
	int frameHeight = 300;
 
   float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//piso
   
   float bouncer_x2 = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y2 = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//cubo
   
   float bouncer_x3 = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y3 = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//enemigo
   
   float bouncer_x4 = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y4 = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//fondo
   
   
   float bouncer_x5 = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y5 = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//materiales
   
   float bouncer_dx = -4.0, bouncer_dy = 4.0;
  
   float i,i2,i3,i4,i5=0,i6=0,i7=0;
   int aux1, aux2;
   
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
 
   display = al_create_display(924,640);
   if(!display) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);                            
      al_destroy_timer(timer);
      return 0;
   }
   
   image3 = al_load_bitmap("cubos.png");
   if(!image3) {
      al_show_native_message_box(display, "Error", "Error", "Failed to load image!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }
   al_set_target_bitmap(image3);
 
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

 
   al_register_event_source(event_queue, al_get_keyboard_event_source());
 
   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);
   
   image = al_load_bitmap("fondo1.png");
   image2 = al_load_bitmap("piso.png");
   image4 = al_load_bitmap("enemigo.png"); 
   image5 = al_load_bitmap("sprite_explosiones.png");
   image6 = al_load_bitmap("pared.png");
   al_convert_mask_to_alpha(image5, al_map_rgb(106, 76, 48));
 
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
		  
		  
		  //-----------------------------------------------------	
		  
		  
		  
		  if(key[KEY_UP] ) {
			 i6=i6+1;
			 if(i6==3){
				i5=i5+1;
				i6=12;	
				}
		 }  	  
		 else{
			 i6=0;
			 
		 }
		 if(i5==12)
		 {
			 i5=0;
			 i7=i7+1;
		 }
		 if(i7==5)
			i7=0;
		 
		 if(key[KEY_SPACE] ) {
			 if( bouncer_y2 >= 300.0){
				aux1=1;
			}  
				
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
  		  //-------------------------------------------------
  		  
  		  
  		  
  		  
  		  
		 
		 //---------------------------------------------------
		  
		 	  
         if(bouncer_x < -256)              
			bouncer_x= bouncer_x+256; 
		bouncer_x += bouncer_dx;
                 
              
         if(bouncer_x4 < -256)           
			bouncer_x4= bouncer_x4+1024; 
	     bouncer_x4+= bouncer_dx/3;
                        
            
         if(bouncer_x3 < -256)                
			bouncer_x3= bouncer_x3+1256;
         bouncer_x3 += bouncer_dx*2;
         
         
         if(bouncer_x5 < -956)                
			bouncer_x5= bouncer_x5+2056;
         bouncer_x5 += bouncer_dx;
           
           //---------------------------------------------------- 
            
            if(++frameCount >= frameDelay)
			{
				if(++curFrame >= maxFrame)
					curFrame = 0;

				frameCount = 0;
			}

		//	bouncer_x2 -= 5;

		/*	if(bouncer_x2 <= 0 - frameWidth)
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
               key[KEY_UP] = false;
               break;
			 
			 case ALLEGRO_KEY_SPACE:
              key[KEY_SPACE] = false;
               break;
         }
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
		
		i=bouncer_x;
		i2=bouncer_x4;
		

		
	    al_clear_to_color(al_map_rgb(0,0,0));
         
     
	 //al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
	   al_draw_bitmap(image,i2-800,0,0);
	   al_draw_bitmap(image,i2+220,0,0);
	   
	   al_draw_bitmap(image2,i,500,0);
	   al_draw_bitmap(image2,i+256,500,0);
	   al_draw_bitmap(image2,i+256*2,500,0);
	   al_draw_bitmap(image2,i+256*3,500,0);
	   al_draw_bitmap(image2,i+256*4,500,0);
	   al_draw_bitmap(image2,i+256*5,500,0);
	   
	   al_draw_bitmap(image6,bouncer_x5+400,440,100);
	   al_draw_bitmap(image6,bouncer_x5+400+(62*1),440,100);
	   al_draw_bitmap(image6,bouncer_x5+400+(62*2),440,100);
	   al_draw_bitmap(image6,bouncer_x5+400+(62*3),440,100);
	   al_draw_bitmap(image6,bouncer_x5+400+(62*4),440,100);
	   al_draw_bitmap(image6,bouncer_x5+400+(62*5),440,100);
	   al_draw_bitmap(image6,bouncer_x5+400+(62*6),440,100);
	   al_draw_bitmap(image6,bouncer_x5+400+(62*7),440,100);
	   al_draw_bitmap(image6,bouncer_x5+400+(62*8),440,100);
	 
	   
	 //  al_draw_bitmap(image4,bouncer_x3,350,0);
	   
	   	al_draw_bitmap_region(image4,i4*140,0,140,150,bouncer_x3,355,0);
	   	
	   	
	   	al_draw_bitmap_region(image3,9+(97*i5)-(i5/4),55+(96*i7),89,87,bouncer_x2-200, bouncer_y2+109,0);
	   //al_draw_bitmap(image3,bouncer_x2-200, bouncer_y2+115,0);
	   
	    if(bouncer_x3<bouncer_x2-125&&bouncer_x3>bouncer_x2-330){	   
		   if(bouncer_y2>150){   
			   curFrame==0;			      	
				i3=1;
				i4=0;
			
			}
		}
	   if(i3==1){
		al_draw_bitmap_region(image5, (curFrame * frameWidth)-59, 0, frameWidth, frameHeight+20,bouncer_x2-300, bouncer_y2+30, 0);
		}
       if(curFrame==9)
       {   
		   curFrame==0;
		   i3=0;
		   i4=1;
		   }
         al_flip_display();
         
      }
   }
      
   
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   al_destroy_display(display);
   
   //al_destroy_bitmap(bouncer);
   al_destroy_bitmap(image);
   al_destroy_bitmap(image2);
   al_destroy_bitmap(image3);
   al_destroy_bitmap(image4);
   al_destroy_bitmap(image5);
   al_destroy_bitmap(image6);
 
   return 0;
}
