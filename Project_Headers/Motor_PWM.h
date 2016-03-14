/*
 * Motor_PWM.h
 *
 *  Created on: Oct 4, 2014
 *      Author: lau-Desktop
 */

#ifndef MOTOR_PWM_H_
#define MOTOR_PWM_H_

void Motor_PWM_Arrancar(Motor *,uint8_t,uint8_t);
void MOTOR_PWM_setVelocidad(Motor *,uint8_t);
void MOTOR_PWM_setDireccion(Motor *,uint8_t);

#endif /* MOTOR_PWM_H_ */
