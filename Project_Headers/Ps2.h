/*
 * Ps2.h
 *
 *  Created on: Oct 31, 2014
 *      Author: lau-Desktop
 */

#include "PE_Types.h"

#ifndef PS2_H_
#define PS2_H_

typedef enum PS2_PIN_ {PS2_PIN_CLOCK,PS2_PIN_DATA} PS2_PIN;
		
void PS2_Init(void);
void PS2_gohi(PS2_PIN);
void PS2_golo(PS2_PIN);
void PS2_write(unsigned char);
unsigned char PS2_read(unsigned char * data);
unsigned char PS2_leer(PS2_PIN);
void PS2_report(uint8_t data[]);
void PS2_send(unsigned char data);
unsigned char PS2_read_movement_x(uint8_t status, uint8_t * x); 
unsigned char PS2_read_movement_y(uint8_t status, uint8_t  * y);


#endif /* PS2_H_ */
