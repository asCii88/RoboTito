/*
 * Tareas.c
 *
 *  Created on: Feb 21, 2015
 *      Author: asCii
 */

#include "Globales.h"
#include "Ultrasonic.h"
#include "FRTOS1.h"
#include "semphr.h"
#include "queue.h"
#include "PE_Types.h"
#include "Movimiento.h"
#include "Mensaje.h"
#include "BADELANTE.h"
#include "BATRAS.h"
#include "BADDER.h"
#include "BADIZQ.h"
#include "BATDER.h"
#include "BATIZQ.h"
#include "BOK.h"


xTaskHandle xLeer_Botones_Handle;
xTaskHandle xSensor_proximidad_Handle;
xTaskHandle xMovimiento_Handle;

/*
 * Estaes la tarea de menor prioridad. Cada 100ms comprueba si se apretó algún botón.
 * */
void vLeer_Botones( void * pvParameters ){
	uint8 val;
	for(;;){
		if (!BADELANTE_GetVal()){
			while(!BADELANTE_GetVal()); //Espera a que se suelte el botón
			val = MSJ_ADELANTE; 
			Led_SetVal(); //Enciende el led del teclado
			FRTOS1_xQueueSendToBack(xCola_mov, (const void *) &val, 0); //Carga el mensaje en la cola de movimientos
		} else	if (!BATRAS_GetVal()){
			while(!BATRAS_GetVal());
			val = MSJ_ATRAS;
			Led_SetVal();
			FRTOS1_xQueueSendToBack(xCola_mov, (const void *) &val, 0);	
		} else	if (!BADDER_GetVal()){
			while(!BADDER_GetVal());
			val = MSJ_GIRO_ADELANTE_DERECHA;
			Led_SetVal();
			FRTOS1_xQueueSendToBack(xCola_mov, (const void *) &val, 0);	
		} else	if (!BADIZQ_GetVal()){
			while(!BADIZQ_GetVal());
			val = MSJ_GIRO_ADELANTE_IZQUIERDA;
			Led_SetVal();
			FRTOS1_xQueueSendToBack(xCola_mov, (const void *) &val, 0);	
		} else if (!BATDER_GetVal()){
			while(!BATDER_GetVal());
			val = MSJ_GIRO_ATRAS_DERECHA;
			Led_SetVal();
			FRTOS1_xQueueSendToBack(xCola_mov, (const void *) &val, 0);	
		} else if (!BATIZQ_GetVal()){
			while(!BATIZQ_GetVal());
			val = MSJ_GIRO_ATRAS_IZQUIERDA;
			Led_SetVal();
			FRTOS1_xQueueSendToBack(xCola_mov, (const void *) &val, 0);	
		} else if(!BOK_GetVal()){
			while(!BOK_GetVal());
			Led_SetVal();
			FRTOS1_xSemaphoreGive(xSem_OK); //Da el semáforo para que se inicie el movimiento
			FRTOS1_xSemaphoreTake(xSem_Fin_mov, portMAX_DELAY); //Espera a que se haya finalizado el movimiento
		}
		FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
		Led_ClrVal(); //Apaga el led. De este modo se logra un destello de 100ms por cada botón y que quede encendido durante todo el movimiento.
	}
}

//Actualiza la distancia al objeto más cercano
void vSensor_proximidad( void * pvParameters ){
	portCHAR direccion;
	uint16 aux;
	for( ;; ) {
		if(FRTOS1_xQueueReceive(xCola_US, (void *) &direccion, portMAX_DELAY) == pdTRUE){
			while(sensar){
				aux = US_Measure(direccion);
				if (aux != 0){
					distancia_objeto = aux;
				}
				FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
			}
		}
	}
}

/*
 * Espera en un semáforo a que se inicialice el movimiento. Lee los mensajes de la cola de movimientos, hasta que no haya más. 
 * */
void vMovimiento( void * pvParameters ){
	uint8 mov;
	portCHAR direccion;

	for( ;; ) {
		if(FRTOS1_xSemaphoreTake(xSem_OK,portMAX_DELAY) == pdTRUE){
			while(FRTOS1_xQueueReceive(xCola_mov, (void *) &mov, 0) == pdTRUE){
				switch (mov){
				case MSJ_ADELANTE:{
					sensar = TRUE;
					direccion = ADELANTE;
					FRTOS1_xQueueSendToBack(xCola_US,(const void *)&direccion,portMAX_DELAY); //Comienza el sensado en la dirección del movimiento
					FRTOS1_vTaskDelay(100/portTICK_RATE_MS); //Duerme la tarea para que se actualice el valor de la distancia antes de iniciar el movimiento
					Movimiento_Avanzar(1);
					sensar = FALSE;
					FRTOS1_vTaskDelay(100/portTICK_RATE_MS); //Duerme la tarea para que se reciba el False
					break;
				}
				case MSJ_ATRAS: {
					sensar = TRUE;
					direccion = ATRAS;
					FRTOS1_xQueueSendToBack(xCola_US,(const void *)&direccion,portMAX_DELAY);
					FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
					Movimiento_Retroceder(1);
					sensar = FALSE;
					FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
					break;
				}
				case MSJ_GIRO_ATRAS_DERECHA:{
					sensar = TRUE;
					direccion = ATRAS;
					FRTOS1_xQueueSendToBack(xCola_US,(const void *)&direccion,portMAX_DELAY);
					FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
					Movimiento_RetrocederDerecha();
					sensar = FALSE;
					FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
					break;
				}
				case MSJ_GIRO_ADELANTE_DERECHA:{
					sensar = TRUE;
					direccion = ADELANTE;
					FRTOS1_xQueueSendToBack(xCola_US,(const void *)&direccion,portMAX_DELAY);
					FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
					Movimiento_AvanzarDerecha();
					sensar = FALSE;
					FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
					break;
				}
				case MSJ_GIRO_ATRAS_IZQUIERDA:{
					sensar = TRUE;
					sensar = TRUE;
					direccion = ATRAS;
					FRTOS1_xQueueSendToBack(xCola_US,(const void *)&direccion,portMAX_DELAY);
					FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
					Movimiento_RetrocederIzquierda();
					sensar = FALSE;
					FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
					break;
				}
				case MSJ_GIRO_ADELANTE_IZQUIERDA:{
					sensar = TRUE;
					direccion = ADELANTE;
					FRTOS1_xQueueSendToBack(xCola_US,(const void *)&direccion,portMAX_DELAY);
					FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
					Movimiento_AvanzarIzquierda();
					sensar = FALSE;
					FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
					break;
				}
				default:{
					/*error*/
					break;
				}
				}
			}
		}
		FRTOS1_xSemaphoreGive(xSem_Fin_mov);
	}
}

void vCrearTareas(){
	if (FRTOS1_xTaskCreate( vLeer_Botones, "Leer_Botones", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY, &xLeer_Botones_Handle ) != pdPASS) {
		for(;;){} /* error */
	}
	if (FRTOS1_xTaskCreate( vSensor_proximidad, "Sensor_proximidad", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY+1, &xSensor_proximidad_Handle ) != pdPASS) {
		for(;;){} /* error */
	}
	if (FRTOS1_xTaskCreate( vMovimiento, "Movimiento", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY+1, &xMovimiento_Handle ) != pdPASS) {
		for(;;){} /* error */
	}
}
