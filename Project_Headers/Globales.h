/*
 * Globales.h
 *
 *  Created on: Feb 21, 2015
 *      Author: asCii
 */

#ifndef GLOBALES_H_
#define GLOBALES_H_

#include "PE_Types.h"
#include "FRTOS1.h"
#include "semphr.h"
#include "queue.h"

#define ADELANTE 1
#define ATRAS 0
#define DERECHA 1
#define IZQUIERDA 0

#define MAX_MOVIMIENTOS 10


xSemaphoreHandle xSem_OK;
xSemaphoreHandle xSem_Fin_mov;
xQueueHandle xCola_mov;
uint8 sensar;
xQueueHandle xCola_US;
uint16 distancia_objeto;

void vInicializar_globales();

#endif /* GLOBALES_H_ */
