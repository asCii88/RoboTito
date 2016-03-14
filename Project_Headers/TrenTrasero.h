/*
 * TrenTrasero.h
 *
 *  Created on: Feb 7, 2015
 *      Author: asCii
 */

#ifndef TRENTRASERO_H_
#define TRENTRASERO_H_

#include "PE_Types.h"

#ifndef GLOBALES_H_
#define ADELANTE 1
#define ATRAS 0
#endif

void TrenTrasero_irHaciaAdelante(uint8_t cantVelocidad);
void TrenTrasero_irHaciaAtras(uint8_t cantVelocidad);
void TrenTrasero_Frenar(void);
void TrenTrasero_VariarVelocidad(uint8_t cantVelocidad);

#endif /* TRENTRASERO_H_ */
