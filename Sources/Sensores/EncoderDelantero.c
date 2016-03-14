/*
 * EncoderDelantero.c
 *
 *  Created on: Feb 5, 2015
 *      Author: asCii
 */

#include "EncDel1.h"
#include "EncDel2.h"
#include "EncDel3.h"
#include "EncDel4.h"
#include "PORT_PDD.h"

void EncDel_Init(){
	PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR,16, PORT_PDD_PULL_UP);
	PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR,16,PORT_PDD_PULL_ENABLE);
	PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR,17, PORT_PDD_PULL_UP);
	PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR,17,PORT_PDD_PULL_ENABLE);
}

/*Devuelve el ángulo en grados respecto al centro*/
int8_t EncDel_getPos(){
	//Pone en 0 las señales
	EncDel1_SetVal();
	EncDel2_SetVal();
	
	//Se fija si está a la izquierda
	EncDel1_ClrVal();
	if (EncDel4_GetVal() == 0){ //Está a la izquierda a mas de 20
		EncDel2_ClrVal();
		if(EncDel3_GetVal() == 0){ //Está a mas de 40 hacia la izq
			EncDel2_SetVal();
			EncDel1_SetVal();
			return -40;
		} else { //Entre 20 y 40 a la izq.
			EncDel2_SetVal();
			EncDel1_SetVal();
			return -20;	
		}
		EncDel2_SetVal();
	}
	EncDel1_SetVal();
	
	//Se fija si está a la derecha
	EncDel2_ClrVal();
	if (EncDel4_GetVal() == 0){//Está a la derecha a mas de 20
		EncDel1_ClrVal();
		if(EncDel3_GetVal() == 0){ //Está a más de 40 hacia la der
			EncDel2_SetVal();
			EncDel1_SetVal();
			return 40;
		} else { //Entre 20 y 40 a la der.
			EncDel2_SetVal();
			EncDel1_SetVal();
			return 20;
		}
		EncDel2_SetVal();
	}
	EncDel1_SetVal();
	
	//Esta centrado
	return 0;
}
