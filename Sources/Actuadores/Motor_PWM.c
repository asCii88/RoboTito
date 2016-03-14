/*
 * Motor_PWM.c
 *
 *  Created on: Oct 4, 2014
 *      Author: lau-Desktop
 */

#include "Motor.h"
#include "Motor_PWM.h"
#include "PE_Types.h"

void Motor_PWM_Arrancar(Motor *m,uint8_t cantVelocidad,uint8_t dir){
	uint16_t ratio;

	/* La velocidad de 0 a 100 y el ratio es de 0 a 0xFFFF = 65535
		 * Con ratio = 0 se tiene 100 % PWM
		 * Con ratio = 65535 se tiene 0 % PWM
		 */
	ratio = ((100-cantVelocidad)*65535)/100;
	m->SetRatio16(m->PWMdeviceData,ratio);
	m->DirPutVal(m->DIRdeviceData,dir); //Adelante dir = 1, Atras dir = 0
}

void MOTOR_PWM_setVelocidad(Motor *m,uint8_t cantVelocidad){
	uint32_t ratio;

	/* La velocidad de 0 a 100 y el ratio es de 0 a 0xFFFF = 65535
	 * Con ratio = 0 se tiene 100 % PWM
	 * Con ratio = 65535 se tiene 0 % PWM
	 */
	ratio = ((100-cantVelocidad)*65535)/100;
	m->SetRatio16(m->PWMdeviceData,(uint16_t)ratio);
}

void MOTOR_PWM_setDireccion(Motor *m,uint8_t direccion){
	m->DirPutVal(m->DIRdeviceData,direccion); //Adelante dir = 1, Atras dir = 0
}

