#include "datos.h"

int	Inicializar (ini_var **);
int inicializar_sv (variablesservidor *);

int	GameLoop (ini_var **, variablesservidor *);
int partida (ini_var **, posicion *, auxpartida *, frameExplosion *, frameMonedita *);
int fin (ini_var **, auxpartida *, variablesservidor *);	
int wait_cx (variablesservidor *);
int receive_data (ini_var **, variablesservidor *, posicion *, auxpartida *);

