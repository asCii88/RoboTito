#include "Ps2.h"
#include "WAIT1.h"
#include "BitClock.h"
#include "BitData.h"
#include "PORT_PDD.h"
#include "PE_Types.h"
#include "FRTOS1.h"

#define PS2_bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define OUTPUT      1U
#define INPUT       0U
#define PS2_ACK 0xFA
#define PS2_RESEND 0xFE
#define PS2_ERROR 0xFC 
#define MAX_RESEND 2

unsigned char reporte = 0;

//Se usa busy waiting porque los cambios de contexto del delay del rtos no son lo suficientemente
//predecibles como para las restricciones de temporalidad que requiere la comunicacion ps2 por bit-banging
void PS2_Init()
{	
	BitClock_SetDir((bool)INPUT);
	BitData_SetDir((bool)INPUT);
	WAIT1_Waitus(20);
	PS2_send(0xff);  // reset
	WAIT1_Waitus(20);
	unsigned char aux;
	PS2_read(&aux);  // Vacío
	PS2_read(&aux);  // Vacío
	WAIT1_Waitus(20);
	PS2_send(0xf0);  // Modo remoto
	WAIT1_Waitus(100);
}

/*envia dato y comprueba su recepcion correcta, si no reenvia o resetea y reenvia*/
void PS2_send(unsigned char data){
	unsigned char ack_byte;
	PS2_write(data);
	PS2_read(&ack_byte);
	switch (ack_byte){
	case PS2_ACK: {
		break;
	}
	case PS2_RESEND: {
		PS2_send(data); 
		break;
	}
	case PS2_ERROR: {
		PS2_Init(); 
		PS2_send(data); 
		break;
	}
	default: break; 
	}	
}

/* write a byte to the PS2 device */
void PS2_write(unsigned char data)
{
	unsigned char i;
	unsigned char parity = 1;
	FRTOS1_taskENTER_CRITICAL();
	BitClock_SetDir((bool)INPUT);
	BitData_SetDir((bool)INPUT);
	WAIT1_Waitus(100);
	// Poner el bus en el modo Request to Send (petición de envío), para ello primero debe
	//inhibir la comunicación llevando
	//la línea de PS2_PIN_clock a “0” por al menos 100 microsegundos
	//El protocolo dice por lo menos 100 ms
	//PS2_PIN_data = high, PS2_PIN_clock = low:  Communication Inhibited.
	BitClock_SetDir((bool)OUTPUT);
	BitClock_ClrVal();
	WAIT1_Waitus(100);
	//Se lleva al bus al estado de Request to Send poniendo la línea PS2_PIN_data en “bajo”
	//y liberando la línea PS2_PIN_clock (estado “alto”)
	//PS2_PIN_data = low, PS2_PIN_clock = high:  Host Request-to-Send
	BitData_SetDir((bool)OUTPUT);
	BitData_ClrVal();
	WAIT1_Waitus(10);
	//Se libera la linea PS2_PIN_clock
	BitClock_SetDir((bool)INPUT);	
	//Se espera a que el mouse tome el control y nos de el tren de pulsos
	//El Mouse va a leer cuando el PS2_PIN_clock este en alto
	//Cuando el mouse detecte este estado comenzará a enviar pulsos de reloj
	while (BitClock_GetVal() == 1U);	
	//El host cambia los datos cuando la línea PS2_PIN_clock esta en “bajo”
	//y el mouse los lee cuando PS2_PIN_clock está en “alto”
	for (i=0; i < 8; i++)
	{
		if (data & 0x01)
		{
			BitData_SetDir((bool)INPUT); //Si el bit es un 1 se pone un 1 en el bus de datos
		} else {
			BitData_SetDir((bool)OUTPUT);
			BitData_ClrVal(); //Si el bit es un 0 se pone un 0 en el bus de datos
		}
		//Hay que esperar que el clk se ponga en alto que es cuando
		//el reloj va a leer el dato
		while (BitClock_GetVal() == 0U);
		//Hay que esperar que esperar que el clk se vuelva a poner en bajo
		//para enviar
		while (BitClock_GetVal() == 1U);
		parity = parity ^ (data & 0x01);
		data = data >> 1;
	}
	//Luego de mandar los datos, se envia el bit de paridad
	if (parity)
	{
		BitData_SetDir((bool)INPUT);
	} else {
		BitData_SetDir((bool)OUTPUT);
		BitData_ClrVal();
	}
	//Se espera a que el ckl lea el bit de paridad
	while (BitClock_GetVal() == 0U);
	//Se espera a que baje el pulso
	while (BitClock_GetVal() == 1U);
	//Se libera el bus de datos
	BitData_SetDir((bool)INPUT);
	WAIT1_Waitus(50);
	//Esperar a que se ponga en bajo el ckl
	while (BitClock_GetVal() == 1U);
	//Esperar a que se liberen el bus de datos y clk
	while ((BitClock_GetVal() == 0U) || (BitData_GetVal() == 0U));
	//Poner en espera los datos entrantes
	BitClock_SetDir((bool)OUTPUT);
	BitClock_ClrVal();
	FRTOS1_taskEXIT_CRITICAL();
}


/*
 * read a byte of data from the ps2 device.  Ignores parity.
 */
unsigned char PS2_read(unsigned char * data)
{
	*data = 0x00;//En esta variable se van a guardar los datos
	unsigned char data_paridad;
	unsigned char i;
	unsigned char bit = 0x01;
	unsigned char parity_recvd;
	unsigned char parity_calc = 1;
	FRTOS1_taskENTER_CRITICAL();
	//Estado idle
	//PS2_PIN_clock debe estar continuamente en alto por al menos 50 microsegundos antes de
	//que el mouse pueda comenzar a transmitir.
	BitClock_SetDir((bool)INPUT);
	BitData_SetDir((bool)INPUT);
	WAIT1_Waitus(50);
	//El mouse debe escribir los datos mientras la línea PS2_PIN_clock está en alto y el host
	//los leerá mientras PS2_PIN_clock está en bajo.
	while (BitClock_GetVal() == 1U);
	WAIT1_Waitus(5);	
	while (BitClock_GetVal() == 0U);	// Se come el bit de start
	for (i=0; i < 8; i++)
	{
		//Se espera a que el clk este en bajo para poder leer el dato
		//Se pasan los datos recibidos al buffer
		while (BitClock_GetVal() == 1U);
		if (BitData_GetVal() == 1U)
		{
			*data = *data | bit;
		}
		while (BitClock_GetVal() == 0U);
		bit = bit << 1;
	}
	// Se recibe el bit de paridad
	while (BitClock_GetVal() == 1U);
	parity_recvd = BitData_GetVal();
	while (BitClock_GetVal() == 0U);
	// Se recibe el bit de stop
	while (BitClock_GetVal() == 1U);
	while (BitClock_GetVal() == 0U);
	BitClock_SetDir((bool)OUTPUT);
	BitClock_ClrVal();	//Poner en espera los datos entrantes
	FRTOS1_taskEXIT_CRITICAL();
	data_paridad = *data;
	//Calcula la paridad
	for (i=0; i < 8; i++)
	{
		parity_recvd = parity_recvd ^ (data_paridad & 0x01);
		data_paridad = data_paridad >> 1;
	}
	if (parity_recvd != parity_calc){
		//Si se recibe un valor con la paridad incorrecta
		return 0; //se devuelve 0
	} else {
		return 1;
	}
}

//El movimiento esta en complento 2, ca2. Se lo convierte a la forma binaria
unsigned char PS2_read_movement_x(uint8_t status, uint8_t * x) {
	if(PS2_read(x)){
		//El bit 4 del primer byte es de signo x (X sign bit)
		//si no tiene signo no es necesario hacerse el ca2
		if (PS2_bitRead(status, 4)) {
			*x = 255 - *x;
		}
		return 1;
	} else {
		return 0;
	}
}

//El movimiento esta en complento 2, ca2. Se lo convierte a decimal
unsigned char PS2_read_movement_y(uint8_t status, uint8_t  * y) {
	return PS2_read_movement_x((status>>1), y);
}

/*El mouse responde con $FA y envía un paquete de datos de
movimiento. Esta es la única forma de leer datos en modo “Remoto”. Luego de
que el paquete de datos fue exitosamente enviado se borran los contadores */
void PS2_report(uint8_t data[]) {
	PS2_send(0xeb); // Send Read PS2_PIN_data
	while(!PS2_read(&(data[0]))){
		PS2_write(PS2_RESEND);
	} // Bits de estado (desborde,signo,etc) - Status bit
	while(!PS2_read_movement_x(data[0], &(data[1]))){
		PS2_write(PS2_RESEND);
	} // Contador X - X Movement Packet
	while(!PS2_read_movement_y(data[0], &(data[2]))){
		PS2_write(PS2_RESEND);
	} // Contador Y - Y Movement Packet
}

