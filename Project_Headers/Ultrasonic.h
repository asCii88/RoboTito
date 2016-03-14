/*
 * Ultrasonic.h
 *
 *  Created on: Dec 30, 2012
 *      Author: Erich Styger
 *      Driver for the HC-SR04 and FRDM-KL25Z board
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "PE_LDD.h"
#include "PE_Types.h"

typedef enum {
  ECHO_IDLE, /* El dispositivo no está en uso */
  ECHO_TRIGGERED, /* Se envió el pulso de trigger */
  ECHO_MEASURE, /* Midiendo el eco */
  ECHO_OVERFLOW, /* La medición tomó demasiado */
  ECHO_FINISHED /* La medición finalizo */
} US_EchoState;

typedef struct {
  LDD_TDeviceData *trigDevice; /* Manejador para el pin de trigger */
  LDD_TDeviceData *echoDevice; /* Dispositivo de captura de entrada para el pin de eco */
  volatile US_EchoState state; /* estado */
  TPM_US_TValueType capture; /* valor de entrada capturado */
  void (*TRIG_SetVal) (LDD_TDeviceData *); /*Funciones pin de trigger*/
  void (*TRIG_ClrVal) (LDD_TDeviceData *); /*Funciones pin de trigger*/
  uint8_t echoChannelNr; /*Canal del tpm que usa*/
} US_DeviceType;

US_DeviceType * get_US(bool direccion);

int US_Measure(bool direccion);

/* 
 * Llamada en caso de overflow durante la captura. Esta fucnion es llamada desde una interrupción
 */
void US_EventEchoOverflow();

/*
 * Función llamada por la interrupción del TPM para los flancos de subida y bajada en el pin de eco
 */
void US_EventEchoCapture(bool direccion);

/* 
 * Convertir los microsegundos a centímetros
 */
uint16_t US_usToCentimeters(uint16 microseconds, uint8 temperatureCelsius);


uint16 US_Measure_us(bool direccion);

/*
 * Rutina de inicializacion
 */
void US_Init(void);


#endif /* ULTRASONIC_H_ */
