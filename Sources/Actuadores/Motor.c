/*
 * Motor.c
 *
 *  Created on: Oct 4, 2014
 *      Author: lau-Desktop
 */

#include "Motor.h"
#include "Motor_PWM.h"
#include "PWM_TraccionTrasera.h"
#include "PWM_TraccionDelantera.h"
#include "TraccionTrasera_Direccion.h"
#include "TraccionDelantera_Direccion.h"

//#include "PWM1.h"

#define VELOCIDADDEFAULT 90
#define VELOCIDADMIN 0
#define VELOCIDADMAX 95

static Motor motorTrasero,motorDelantero;

/**
 * Le mandas la velocidad que querés al comienzo y una direccion. Hace todo de una. 
 * */
void Motor_Arrancar(Motor *m,uint8_t cantVelocidad,uint8_t dir){
	m->direccion = 	dir;
	if(cantVelocidad > VELOCIDADMAX){
		m->velocidad = VELOCIDADMAX;
		Motor_PWM_Arrancar(m,VELOCIDADMAX,dir);
	}else{
		if(cantVelocidad < VELOCIDADMIN){
			m->velocidad = VELOCIDADMIN;
			Motor_PWM_Arrancar(m,VELOCIDADMIN,dir);
		}else{
			Motor_PWM_Arrancar(m,cantVelocidad,dir);
		}
	}
}

void Motor_setDireccion(Motor *m,uint8_t dir){
	m->direccion = dir;
	MOTOR_PWM_setDireccion(m,dir);

}

void Motor_cambiarDireccion(Motor *m){
	m->direccion = !(m->direccion);
	MOTOR_PWM_setDireccion(m,m->direccion);
}

/**
 * Hace que se mueva una vez que ya seteamos los otros parámetros
 * */
void Motor_setVelocidad(Motor *m,uint8_t cantVelocidad){
	if(cantVelocidad > VELOCIDADMAX){
		m->velocidad = VELOCIDADMAX;
		MOTOR_PWM_setVelocidad(m,VELOCIDADMAX);
	}else{
		if(cantVelocidad < VELOCIDADMIN){
			m->velocidad = VELOCIDADMIN;
			MOTOR_PWM_setVelocidad(m,VELOCIDADMIN);
		}else{
			m->velocidad = cantVelocidad;
			MOTOR_PWM_setVelocidad(m,cantVelocidad);
		}
	}
}


void Motor_Parar(Motor *m){
	Motor_setVelocidad(m,0);
}

Motor * Motor_getMotor(TIPO_MOTOR tipoMotor){
	if(tipoMotor == TRASERO){
		return &motorTrasero;
	}else{
		return &motorDelantero;
	}
}

void Motor_Init(){
	//Se inicializa Motor Trasero
	motorTrasero.PWMdeviceData = PWM_TraccionTrasera_Init(NULL);
	motorTrasero.SetRatio16 = PWM_TraccionTrasera_SetRatio16;
	motorTrasero.DIRdeviceData = TraccionTrasera_Direccion_Init(NULL);
	motorTrasero.DirPutVal = TraccionTrasera_Direccion_PutVal;
	//Se inicializa Motor Delantero
	motorDelantero.PWMdeviceData = PWM_TraccionDelantera_Init(NULL);
	motorDelantero.SetRatio16 = PWM_TraccionDelantera_SetRatio16;
	motorDelantero.DIRdeviceData = TraccionDelantera_Direccion_Init(NULL);
	motorDelantero.DirPutVal = TraccionDelantera_Direccion_PutVal;
    //Se activan los PWM
	PWM_TraccionDelantera_Enable(motorDelantero.PWMdeviceData);
	PWM_TraccionTrasera_Enable(motorTrasero.PWMdeviceData);
    Motor_Arrancar(&motorTrasero,0,1);
    Motor_Arrancar(&motorDelantero,0,1);
}

