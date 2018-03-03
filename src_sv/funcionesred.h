// Funciones de red

#include "datos.h"


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int get_network_data(int sockfd, char *buffer, int *s, int *k, char *l, int *num, float *p, int *pt, int *v) {
    int n;
    char *key, *status, *letra, *numero, *pos, *ptos, *liv;
    bool recv_tecla = true;
    bool recv_pos = true;    

    // Me fijo si llegó via red
    memset((void *) buffer, '\0', 256);
    n = recv(sockfd,buffer,255,MSG_DONTWAIT);
    //DBG - printf("Buffer: %s / n: %d",buffer,n);

    if(n>0) {
        key = strtok(buffer,";");
        status = strtok(NULL,";");
        letra = strtok(NULL,";");
        numero = strtok(NULL,";");
        pos = strtok(NULL,";");
        ptos = strtok(NULL,";");
        liv = strtok(NULL,";");
        
        //DBG - printf("key: %s / status: %s\n",key,status);
        //DBG - printf("Eje: %s / numero: %s / posicion: %s\n",letra,numero,pos);
        //DBG - printf("Puntos: %s / Vida: %s\n",ptos,liv);

// Recibe los puntos y vida

		*pt = atoi (ptos);
		*v = atoi (liv);

// Si recibe teclas:

        if(!strcmp(status,"true")) {
            *s=true;
        } else if(!strcmp(status,"false")) {
            *s=false;
		} else if (!strcmp(status,"VACIO")) {
			recv_tecla = false;
		} else if (!strcmp(status,"VERDADERO")) {
			recv_tecla = true;
        } else {											
            printf("Error recepción. Buffer: %s",buffer);		
            return 0;
        }

        if(!strcmp(key,"KEY_UP")) {
            *k=KEY_UP;
        } else if(!strcmp(key,"KEY_DOWN")) {
            *k=KEY_DOWN;
        } else if(!strcmp(key,"KEY_LEFT")) {
            *k=KEY_LEFT;
        } else if(!strcmp(key,"KEY_RIGHT")) {
            *k=KEY_RIGHT;
        } else if(!strcmp(key,"KEY_EXIT")) {
            *k=KEY_EXIT;
        } else if(!strcmp(key,"KEY_SPACE")) {
			*k=KEY_SPACE;
        } else if(!strcmp(key,"KEY_P")) {
			*k=KEY_P;
		} else if (!strcmp(key,"VACIO")) {
			recv_tecla = false;			
		} else if (!strcmp(key,"VERDADERO")) {
			recv_tecla = true;
        } else {											
            printf("Error recepción. Buffer: %s",buffer);
            return 0;
        }

 
// Si recibe posiciones:
 
        if(!strcmp(letra,"d")) {
            *l='d';
        } else if(!strcmp(letra,"x")) {
            *l='x';
        } else if(!strcmp(letra,"y")) {
            *l='y';
		} else if (!strcmp(letra,"VACIO")) {
			recv_pos = false;            
		} else if (!strcmp(letra,"VERDADERO")) {
			recv_pos = true;
        } else {											
            printf("Error recepción. Buffer: %s",buffer);		
            return 0;
        }

		if (!strcmp(numero,"VACIO")) {
			recv_pos = false;		
		} else if (!strcmp(numero,"VERDADERO")) {
			recv_pos = true;
		} else if (*l != 'd') {
			*num = atoi (numero);
		}

		if (!strcmp(pos,"VACIO")) {
			recv_pos = false;	
		} else if (!strcmp(pos,"VERDADERO")) {
			recv_pos = true;
		} else	if (pos == NULL) {
			return 0;	
		} else {
			*p = atof (pos);
		}

        // Data saved (s+k), can return
        //DBG - printf("key: %d / status: %d\n",*k,*s);
        if (recv_tecla || recv_pos) {
			return 1;
		} else {
			return 0;
		}
    } else {
        return 0;
    }
}
