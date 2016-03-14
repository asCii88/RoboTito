/*
 * TrenDelantero.c
 *
 *  Created on: Feb 7, 2015
 *      Author: asCii
 */

#include "TrenDelantero.h"
#include "EncoderDelantero.h"
#include "Motor.h"

#define VELOCIDAD_ARRANQUE_GIRO 90
#define VELOCIDAD_FIN_GIRO 50

void TrenDelantero_Girar(TIPO_GIRO tipoGiro){
	switch(tipoGiro){
	case GIRO_IZQUIERDA : {
		if (EncDel_getPos() > -40){
			Motor_Arrancar(Motor_getMotor(DELANTERO),VELOCIDAD_ARRANQUE_GIRO,IZQUIERDA); //Inicia el movimiento con mayor velocidad
			while(EncDel_getPos() > -20);
			Motor_setVelocidad(Motor_getMotor(DELANTERO),VELOCIDAD_FIN_GIRO); //Luego la disminuye
			while(EncDel_getPos() > -40);
			Motor_Parar(Motor_getMotor(DELANTERO));
		}
		break;
	}
	case GIRO_DERECHA : {
		if (EncDel_getPos() < 40){
			Motor_Arrancar(Motor_getMotor(DELANTERO),VELOCIDAD_ARRANQUE_GIRO,DERECHA);
			while(EncDel_getPos() < 20);
			Motor_setVelocidad(Motor_getMotor(DELANTERO),VELOCIDAD_FIN_GIRO);
			while(EncDel_getPos() < 40);
			Motor_Parar(Motor_getMotor(DELANTERO));
		}
		break;
	}
	case CENTRAR : {
		if (EncDel_getPos() > 0){ //Está a la derecha
			if(EncDel_getPos() >= 40){
				Motor_Arrancar(Motor_getMotor(DELANTERO),VELOCIDAD_ARRANQUE_GIRO,IZQUIERDA);
				while(EncDel_getPos() > 20);
				Motor_setVelocidad(Motor_getMotor(DELANTERO),VELOCIDAD_FIN_GIRO);
			}
			while(EncDel_getPos() != 0);
			Motor_Parar(Motor_getMotor(DELANTERO));
			TrenDelantero_Girar(CENTRAR); //Corrige por si se pasó de largo
		} else if (EncDel_getPos() < 0){ //Esta a la izquierda
			if(EncDel_getPos() <= -40){
				Motor_Arrancar(Motor_getMotor(DELANTERO),VELOCIDAD_ARRANQUE_GIRO,DERECHA);
				while(EncDel_getPos() < -20);
				Motor_setVelocidad(Motor_getMotor(DELANTERO),VELOCIDAD_FIN_GIRO);
			}
			while(EncDel_getPos() != 0);
			Motor_Parar(Motor_getMotor(DELANTERO));
			TrenDelantero_Girar(CENTRAR); //Corrige por si se pasó de largo
		}
		break;
	}
	}
}
