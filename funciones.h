#include "datos.h"

int	Inicializar (ini_var **);
int inicializar_cl (variablescliente *);

int	GameLoop (ini_var **, variablescliente *);
int menu(ini_var **, int *, int *);
int partida (ini_var **, int *, int *, char **, posicion *, auxpartida *, frameExplosion *, frameMonedita *, bool **, variablescliente *);
int fin (ini_var **, char **);	
int cargar_ip (ini_var **, variablescliente *);
