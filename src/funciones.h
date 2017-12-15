#include "datos.h"

int	Inicializar (ini_var **);

int	GameLoop (ini_var **);
int menu(ini_var **, int *, int *);
int partida (ini_var **,niveles** INI1, int *, int *, char **, posicion *, auxpartida *, frameExplosion *, frameMonedita *, bool **);
int fin (ini_var **, char **);	// REVISAR
int Niveles(niveles** INI1);
