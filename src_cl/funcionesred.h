/*! \file funcionesdered.h
    \brief Funciones de red Cliente.
*/

#include "datos.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int put_network_data(int sockfd, char *buffer, char *buffer2, char *buffer3, char *buffer4, char *buffer5, int k, char s, char e, int num, float v, int puntos, int life) {
    int n;

    memset((void *) buffer, '\0', 256);
    memset((void *) buffer2, '\0', 256);
    memset((void *) buffer3, '\0', 256);

	if (k != VACIO && k != VERDADERO) {
			
		switch(k) {
			case KEY_UP:
				strcpy(buffer,"KEY_UP;");
				break;
			case KEY_DOWN:
				strcpy(buffer,"KEY_DOWN;"); 
				break;
			case KEY_LEFT:
				strcpy(buffer,"KEY_LEFT;");
				break;
			case KEY_RIGHT:
				strcpy(buffer,"KEY_RIGHT;");
				break;
			case KEY_EXIT:
				strcpy(buffer,"KEY_EXIT;");
				break;
			case KEY_SPACE:
				strcpy(buffer,"KEY_SPACE;"); 
				break;    
			case KEY_P:
				strcpy(buffer,"KEY_P;"); 
				break; 
			}
	
		switch(s) {
			case true:
				strcat(buffer,"true;");
				break;
			case false:
				strcat(buffer,"false;");
				break;           
			}
			
		} else if (k == VACIO) {
			
			strcpy(buffer, "VACIO;");
			strcat(buffer, "VACIO;");
			
		}

	if (num != VACIO && num != VERDADERO) {

		if (e == 'd') {
			strcat(buffer,"d;x;");
		
		} else {
				
			switch(e) {
				case 'x':
					strcat(buffer,"x;");
					break;          
							
				case 'y':
					strcat(buffer,"y;");
					break;      
						
			}
			
			sprintf(buffer2, "%i;", num);
			strcat(buffer, buffer2);
		}
		
		sprintf(buffer3, "%f;", v);
		strcat(buffer, buffer3);
		
	} else if (num == VACIO) {
		
		strcat(buffer, "VACIO;");
		strcat(buffer, "VACIO;");
		strcat(buffer, "VACIO;");
		
	}
	
	if (num != VACIO && k == VERDADERO && num == VERDADERO) {
		
		strcat(buffer, "VERDADERO;");
		strcat(buffer, "VERDADERO;");
		strcat(buffer, "VERDADERO;");
		strcat(buffer, "VERDADERO;");
		strcat(buffer, "VERDADERO;");
		
	}
	
	sprintf(buffer4, "%i;", puntos);
	strcat(buffer, buffer4);
	sprintf(buffer5, "%i;\0", life);
	strcat(buffer, buffer5);

    //DBG - printf("Buffer: %s",buffer);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) error("ERROR writing to socket");

    return n;
}
