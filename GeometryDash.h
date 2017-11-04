#include <stdio.h> 
#include <allegro5/allegro.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

#define PUERTO 9123
#define MY_EVENT_TYPE ALLEGRO_GET_EVENT_TYPE('S','O','C','K')

enum MYKEYS {
	
   KEY_UP,KEY_SPACE,KEY_EXIT
};

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int put_network_data(int sockfd, char *buffer, int k, char s) {
    int n;

    memset((void *) buffer, '\0', 256);

    switch(k) {
        case KEY_UP:
            strcpy(buffer,"KEY_UP;");
            break;
        case KEY_SPACE:
            strcpy(buffer,"KEY_SPACE;"); 
            break;
        case KEY_EXIT:
            strcpy(buffer,"KEY_EXIT;");
            break;
        }

    switch(s) {
        case true:
            strcat(buffer,"true\0");
            break;
        case false:
            strcat(buffer,"false\0");
            break;
        }

    //DBG - printf("Buffer: %s",buffer);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) error("ERROR writing to socket");

    return n;
}

int get_network_data(int sockfd, char *buffer, int *s, int *k) {
    int n;
    char *key, *status;

    // Me fijo si llegó via red
    memset((void *) buffer, '\0', 256);
    n = recv(sockfd,buffer,255,MSG_DONTWAIT);
    //DBG - printf("Buffer: %s / n: %d",buffer,n);

    if(n>0) {
        key = strtok(buffer,";");
        status = strtok(NULL,";");
        //DBG - printf("key: %s / status: %s\n",key,status);

        if(!strcmp(status,"true")) {
            *s=true;
        } else if(!strcmp(status,"false")) {
            *s=false;
        } else {
            printf("Error recepción. Buffer: %s",buffer);
            return 0;
        }

        if(!strcmp(key,"KEY_UP")) {
            *k=KEY_UP;
        } else if(!strcmp(key,"KEY_SPACE")) {
            *k=KEY_SPACE;
        } else if(!strcmp(key,"KEY_EXIT")) {
            *k=KEY_EXIT;
        } else {
            printf("Error recepción. Buffer: %s",buffer);
            return 0;
        }

        // Data saved (s+k), can return
        //DBG - printf("key: %d / status: %d\n",*k,*s);
        return 1;
    } else {
        return 0;
    }
}

/*

float contador(float bouncer_x,float bouncer_y,float bouncer_dx,float bouncer_dy  ){
	 
          if(bouncer_x < -256)  {
			   //bouncer_dx = -bouncer_dx;
			  //bouncer_dx = 6.0;         
			  bouncer_x= bouncer_x+256; 
		  }
		  bouncer_x += bouncer_dx;
		  
		  
}
*/
