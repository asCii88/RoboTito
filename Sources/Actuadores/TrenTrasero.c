/*
 * TrenTrasero.c
 *
 *  Created on: Feb 7, 2015
 *      Author: asCii
 */

#include "Motor.h"
#include "TrenTrasero.h"

bool moviendose = FALSE;

void TrenTrasero_irHaciaAdelante(uint8_t cantVelocidad){
	if (!moviendose){
		Motor_Arrancar(Motor_getMotor(TRASERO),cantVelocidad, ADELANTE); //Direccion hacia adelante
		moviendose = TRUE;
	}
}

void TrenTrasero_irHaciaAtras(uint8_t cantVelocidad){
	if(!moviendose){
		Motor_Arrancar(Motor_getMotor(TRASERO),cantVelocidad, ATRAS); //Direccion hacia atras
		moviendose = TRUE;
	}
}

void TrenTrasero_VariarVelocidad(uint8_t cantVelocidad){
	if(moviendose){
		Motor_setVelocidad(Motor_getMotor(TRASERO),cantVelocidad);
	}
}

void TrenTrasero_Frenar(){
	if(moviendose){
		Motor_setVelocidad(Motor_getMotor(TRASERO),0);
		moviendose = FALSE;
	}	
}
