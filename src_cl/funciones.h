#include "datos.h"

int	Inicializar (ini_var **, auxpartida **, frameExplosion **, frameMonedita **);
int inicializar_cl (variablescliente *);

int Niveles (niveles **);

int	GameLoop (ini_var **, variablescliente **, auxpartida **, frameExplosion **, frameMonedita **);
int menu(ini_var **);
int partida (ini_var **, posicion *, auxpartida *, frameExplosion *, frameMonedita *, bool **, variablescliente *);
int fin (ini_var **, auxpartida *, variablescliente *);	
int cargar_ip (ini_var **, variablescliente **);
int send_pos (ini_var **, variablescliente *, posicion * , auxpartida *);
