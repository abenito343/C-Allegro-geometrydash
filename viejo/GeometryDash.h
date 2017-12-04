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






float contador(float bouncer_x,float bouncer_y,float bouncer_dx,float bouncer_dy  ){
	 
          if(bouncer_x < -256)  {
			   //bouncer_dx = -bouncer_dx;
			  //bouncer_dx = 6.0;         
			  bouncer_x= bouncer_x+256; 
		  }
		  bouncer_x += bouncer_dx;
		  
		  
}
