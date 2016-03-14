/*
 * Ultrasonic.c
 *
 *  Created on: Dec 30, 2012
 *      Author: Erich Styger
 *      Driver for the HC-SR04 and FRDM-KL25Z board
 */
#include "Ultrasonic.h"
#include "TPM_US.h"
#include "WAIT1.h"
#include "Ultrasonic.h"
#include "Globales.h"
#include "FRTOS1.h"

static US_DeviceType usDevice_DEL; /* Manejadores del dispositivos de ultrasonido */
static US_DeviceType usDevice_TRA;

US_DeviceType * get_US(bool direccion){
	US_DeviceType * retval;
	if (direccion == ADELANTE){
		retval = &usDevice_DEL;
	} else if (direccion == ATRAS){
		retval = &usDevice_TRA;
	} 
	return retval;
}

int US_Measure(bool direccion) {
	int us, cm;
	uint8_t buf[8];

	us = US_Measure_us(direccion);
	if (us != 0){
		UTIL1_Num16uToStrFormatted(buf, sizeof(buf), us, ' ', 5);
		cm = US_usToCentimeters(us, 20);
		UTIL1_Num16uToStrFormatted(buf, sizeof(buf), cm, ' ', 5);
	} else {
		cm = 0;
	}
	return cm;
}


void US_EventEchoOverflow() {
	//Hizo overflow cualquiera sea que estuviera funcionando en este momento
	usDevice_DEL.state = ECHO_OVERFLOW;
	usDevice_TRA.state = ECHO_OVERFLOW;
}

void US_EventEchoCapture(bool direccion) {
	US_DeviceType *ptr = get_US(direccion);

	if (ptr->state==ECHO_TRIGGERED) { /* Primer flanco. Flanco de subida. Comienza la medición. */
		TPM_US_ResetCounter(ptr->echoDevice);
		ptr->state = ECHO_MEASURE;
	} else if (ptr->state==ECHO_MEASURE) { /* Segundo flanco. Flanco de bajada. Se utiliza el valor. */
		(void)TPM_US_GetCaptureValue(ptr->echoDevice, ptr->echoChannelNr, &ptr->capture);
		ptr->state = ECHO_FINISHED;
	}
}

static uint16_t calcAirspeed_dms(uint8 temperatureCelsius) {
	/* Devuelve la velocidad del aire de acuerdo con la temperatura en decímetros por segundo */
	unsigned int airspeed; /* Decímetros por segundo */

	airspeed = 3313 + (6 * temperatureCelsius); /* aire seco, 0% de humedad, ver http://en.wikipedia.org/wiki/Speed_of_sound */
	airspeed -= (airspeed/100)*17; /* factor en una humedad relativa de ~40% */ 
	return airspeed;
}

uint16_t US_usToCentimeters(uint16 microseconds, uint8 temperatureCelsius) {
	return (microseconds*100UL)/calcAirspeed_dms(temperatureCelsius)/2; /* 2 por la da */
}

/* Medir y devolver los milisegundos */
uint16 US_Measure_us(bool direccion) {
	US_DeviceType *ptr = get_US(direccion);
	uint16 us;

	/* Enviar un pulso de 10 microsegundos en la línea de Triger. */
	ptr->TRIG_SetVal(ptr->trigDevice);
	WAIT1_Waitms(10);
	ptr->state = ECHO_TRIGGERED;
	ptr->TRIG_ClrVal(ptr->trigDevice);
	while(ptr->state!=ECHO_FINISHED) {
		/* Medir el pulso de eco */
		if (ptr->state==ECHO_OVERFLOW) { /* ¿La medida tomó demasiado tiempo? */
			ptr->state = ECHO_IDLE;
			return 0; /* No hay eco. Error */
		}
	}
	us = (ptr->capture*1000UL)/(TPM_US_CNT_INP_FREQ_U_0/1000);
	return us;
}

/*Carga las estructuras*/
void US_Init(void) {
	usDevice_DEL.state = ECHO_IDLE;
	usDevice_DEL.capture = 0;
	usDevice_DEL.trigDevice = TRIG_DEL_Init(NULL);
	usDevice_DEL.echoChannelNr = 0;
	usDevice_DEL.TRIG_SetVal = TRIG_DEL_SetVal;
	usDevice_DEL.TRIG_ClrVal = TRIG_DEL_ClrVal;
	usDevice_DEL.echoDevice = TPM_US_Init(NULL);
	usDevice_TRA.state = ECHO_IDLE;
	usDevice_TRA.capture = 0;
	usDevice_TRA.trigDevice = TRIG_TRA_Init(NULL);
	usDevice_TRA.echoDevice =  usDevice_DEL.echoDevice;
	usDevice_TRA.TRIG_SetVal = TRIG_TRA_SetVal;
	usDevice_TRA.TRIG_ClrVal = TRIG_TRA_ClrVal;
	usDevice_TRA.echoChannelNr = 1;
}
