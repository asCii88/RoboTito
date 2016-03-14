/*
 * Globales.c
 *
 *  Created on: Feb 21, 2015
 *      Author: asCii
 */


#include "Globales.h"

/*
 * Variables globales
 * */
void vInicializar_globales(){
	xSem_OK = xSemaphoreCreateBinary();
	xSem_Fin_mov = xSemaphoreCreateBinary();
	xCola_mov = FRTOS1_xQueueCreate(MAX_MOVIMIENTOS, sizeof(uint8));
	xCola_US = FRTOS1_xQueueCreate(1, sizeof(portCHAR));
	sensar = FALSE;
	distancia_objeto = 999;
}
