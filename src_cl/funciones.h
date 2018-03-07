/*! \file funciones.h
    \brief Archivo cabecera de todas las funciones cliente.
*/

#include "datos.h"

int	Inicializar (ini_var **, auxpartida **, frameExplosion **, frameMonedita **);
int inicializar_cl (variablescliente *);

int Niveles (auxpartida **);

int	GameLoop (ini_var **, variablescliente **, auxpartida **, frameExplosion **, frameMonedita **);
int menu(ini_var **);
int partida (ini_var **, posicion *, auxpartida *, frameExplosion *, frameMonedita *, bool **, variablescliente *);
int fin (ini_var **, auxpartida *, variablescliente *);	
int cargar_ip (ini_var **, variablescliente **);
int send_pos (ini_var **, variablescliente *, posicion * , auxpartida *);

void Liberar (ini_var **, variablescliente **, auxpartida **, frameExplosion **, frameMonedita **);
