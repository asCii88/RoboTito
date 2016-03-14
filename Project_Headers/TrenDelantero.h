/*
 * TrenDelantero.h
 *
 *  Created on: Feb 7, 2015
 *      Author: asCii
 */

#ifndef TRENDELANTERO_H_
#define TRENDELANTERO_H_

#ifndef GLOBALES_H_
#define DERECHA 1
#define IZQUIERDA 0
#endif

typedef enum TIPO_GIRO_ {GIRO_DERECHA,GIRO_IZQUIERDA, CENTRAR} TIPO_GIRO;

void TrenDelantero_Girar(TIPO_GIRO);

#endif /* TRENDELANTERO_H_ */
