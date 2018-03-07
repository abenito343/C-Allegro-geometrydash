/*! \file funciones.h
    \brief Archivo cabecera de todas las funciones servidor.
*/

#include "datos.h"

int	Inicializar (ini_var **, auxpartida **, frameExplosion **, frameMonedita **);
int inicializar_sv (variablesservidor *);

int Niveles (auxpartida **);

int	GameLoop (ini_var **, variablesservidor *, auxpartida **, frameExplosion **, frameMonedita **);
int partida (ini_var **, posicion *, auxpartida *, frameExplosion *, frameMonedita *);
int fin (ini_var **, auxpartida *, variablesservidor *);	
int wait_cx (variablesservidor *);
int receive_data (ini_var **, variablesservidor *, posicion *, auxpartida *);

void Liberar (ini_var **, variablesservidor **, auxpartida **, frameExplosion **, frameMonedita **);
