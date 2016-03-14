/*
 * Motor.h
 *
 *  Created on: Oct 4, 2014
 *      Author: lau-Desktop
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "PE_Types.h"
#include "UTIL1.h"

struct Motor_{
	uint8_t id;
	uint8_t direccion;
	uint8_t velocidad; /* La velocidad en un rango de [0..100] */
	LDD_TDeviceData *PWMdeviceData; /* LDD device para controlar PWM */
	LDD_TError (*SetRatio16)(LDD_TDeviceData*, uint16_t); /* Funcion para setear el ratio */
	LDD_TDeviceData *DIRdeviceData; /* LDD device para controlar la Direccion */
	void (*DirPutVal)(LDD_TDeviceData *, bool); /* Funcion para setear la Direccion */
};


typedef struct Motor_ Motor;

typedef enum TIPO_MOTOR_ {DELANTERO,TRASERO} TIPO_MOTOR;

/*
 * Se arranca el motor: 
 * 
 * Velocidad = VelocidadDefault
 * Direccion = Adelante
 * 
 */
//void Motor_ArrancarDefault(Motor *m);

/*
 *  Se arranca el motor
 *  
 *  Velocidad
 *  Direccion
 */
void Motor_Arrancar(Motor *,uint8_t,uint8_t);

/*
 * Se cambia la direccion del motor
 * 
 */
void Motor_setDireccion(Motor *,uint8_t);

/*
 * Se cambia la direccion al motor
 * 
 */
void Motor_cambiarDireccion(Motor *);

/*
 * 
 * Se setea la velocidad al motor
 * 
 */
void Motor_setVelocidad(Motor *,uint8_t cantVelocidad);

/*
 * 
 * Se devuelve la corriente del motor
 *   **Todavia no esta implementado**
 * 
 */
int Motor_getCorriente();


Motor * Motor_getMotor(TIPO_MOTOR);

/*
 * Se para el motor
 * 
 */
void Motor_Parar(Motor *m);

void Motor_Init();


#endif /* MOTOR_H_ */
