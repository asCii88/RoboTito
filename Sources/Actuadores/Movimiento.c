/*

 * Movimiento.c
 *
 *  Created on: Oct 3, 2014
 *      Author: Franco
 */

#include "TrenDelantero.h"
#include "TrenTrasero.h"
#include "Ps2.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "Globales.h"
#include "Mensaje.h"

#define PUNTOSGIRO 200
#define PUNTOS_POR_METRO 100
#define DISTANCIA_MINIMA 15
#define PUNTOS_RESTANTES_PARA_REDUCCION 25
#define VELOCIDAD_ARRANQUE 100
#define VELOCIDAD_REDUCCION 80
#define CHECK_DELAY 100

void Movimiento_Avanzar(int8 metros){

	uint8 dato[3];
	uint16 puntos = metros * PUNTOS_POR_METRO;
	uint16 leidos = 0;
	PS2_report(dato); //Descartar un dato por las dudas.
	TrenDelantero_Girar(CENTRAR); //Endereza el tren delantero
	TrenTrasero_irHaciaAdelante(VELOCIDAD_ARRANQUE); //Inicia el movimiento
	PS2_report(dato); //Lee el primer valor del encoder
	leidos += dato[1];
	//Repite
	while((leidos < puntos) && (distancia_objeto > DISTANCIA_MINIMA)){ //TODO: Ver qué pasa cuando la distancia es superior al rango de detección
		PS2_report(dato);
		leidos += dato[1];
		if ((puntos - leidos) <= PUNTOS_RESTANTES_PARA_REDUCCION){
			TrenTrasero_VariarVelocidad(VELOCIDAD_REDUCCION);
		}
		FRTOS1_vTaskDelay(CHECK_DELAY/portTICK_RATE_MS);//Duerme la tarea
	}
	TrenTrasero_Frenar();
}

void Movimiento_Retroceder(int8 metros){
	uint8 dato[3];
	uint16 puntos = metros * PUNTOS_POR_METRO;
	uint16 leidos = 0;
	PS2_report(dato); //Descartar
	TrenDelantero_Girar(CENTRAR);
	TrenTrasero_irHaciaAtras(VELOCIDAD_ARRANQUE);
	PS2_report(dato); 
	leidos += dato[1];
	while((leidos < puntos) && (distancia_objeto > DISTANCIA_MINIMA)){
		PS2_report(dato);
		leidos += dato[1];
		if ((puntos - leidos) <= PUNTOS_RESTANTES_PARA_REDUCCION){
			TrenTrasero_VariarVelocidad(VELOCIDAD_REDUCCION);
		}
		FRTOS1_vTaskDelay(CHECK_DELAY/portTICK_RATE_MS);
	}
	TrenTrasero_Frenar();
}

void Movimiento_AvanzarIzquierda(){
	uint8_t dato[3];
	int16_t leidos = 0;

	TrenDelantero_Girar(GIRO_IZQUIERDA);
	PS2_report(dato); //Descartar
	TrenTrasero_irHaciaAdelante(VELOCIDAD_ARRANQUE);
	PS2_report(dato);
	leidos += dato[1];
	while((leidos < PUNTOSGIRO) && (distancia_objeto > DISTANCIA_MINIMA)){
		PS2_report(dato);
		leidos += dato[1];
		if ((PUNTOSGIRO - leidos) <= PUNTOS_RESTANTES_PARA_REDUCCION){
			TrenTrasero_VariarVelocidad(VELOCIDAD_REDUCCION);
		}
		FRTOS1_vTaskDelay(CHECK_DELAY/portTICK_RATE_MS);
	}
	TrenTrasero_Frenar();
}

void Movimiento_AvanzarDerecha(){
	uint8_t dato[3];
	int16_t leidos = 0;

	TrenDelantero_Girar(GIRO_DERECHA);
	PS2_report(dato); //Descartar
	TrenTrasero_irHaciaAdelante(VELOCIDAD_ARRANQUE);
	PS2_report(dato);
	leidos += dato[1];
	while((leidos < PUNTOSGIRO) && (distancia_objeto > DISTANCIA_MINIMA)){
		PS2_report(dato);
		leidos += dato[1];
		if ((PUNTOSGIRO - leidos) <= PUNTOS_RESTANTES_PARA_REDUCCION){
			TrenTrasero_VariarVelocidad(VELOCIDAD_REDUCCION);
		}
		FRTOS1_vTaskDelay(CHECK_DELAY/portTICK_RATE_MS);
	}
	TrenTrasero_Frenar();
}

void Movimiento_RetrocederIzquierda(){
	uint8_t dato[3];
	int16_t leidos = 0;

	TrenDelantero_Girar(GIRO_IZQUIERDA);
	PS2_report(dato); //Descartar
	TrenTrasero_irHaciaAtras(VELOCIDAD_ARRANQUE);
	PS2_report(dato);
	leidos += dato[1];
	while((leidos < PUNTOSGIRO) && (distancia_objeto > DISTANCIA_MINIMA)){
		PS2_report(dato);
		leidos += dato[1];
		if ((PUNTOSGIRO - leidos) <= PUNTOS_RESTANTES_PARA_REDUCCION){
			TrenTrasero_VariarVelocidad(VELOCIDAD_REDUCCION);
		}
		FRTOS1_vTaskDelay(CHECK_DELAY/portTICK_RATE_MS);
	}
	TrenTrasero_Frenar();
}

void Movimiento_RetrocederDerecha(){
	uint8_t dato[3];
	int16_t leidos = 0;

	TrenDelantero_Girar(GIRO_DERECHA);
	PS2_report(dato); //Descartar
	TrenTrasero_irHaciaAtras(VELOCIDAD_ARRANQUE);
	PS2_report(dato);
	leidos += dato[1];
	while((leidos < PUNTOSGIRO) && (distancia_objeto > DISTANCIA_MINIMA)){
		PS2_report(dato);
		leidos += dato[1];
		if ((PUNTOSGIRO - leidos) <= PUNTOS_RESTANTES_PARA_REDUCCION){
			TrenTrasero_VariarVelocidad(VELOCIDAD_REDUCCION);
		}
		FRTOS1_vTaskDelay(CHECK_DELAY/portTICK_RATE_MS);
	}
	TrenTrasero_Frenar();
}
