/* ###################################################################
 **     Filename    : main.c
 **     Project     : Avances2
 **     Processor   : MKL25Z128VLK4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2014-12-03, 02:13, # CodeGen: 16
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */         
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "UTIL1.h"
#include "PWM_TraccionTrasera.h"
#include "PWM_TraccionDelantera.h"
#include "TraccionDelantera_Direccion.h"
#include "TraccionTrasera_Direccion.h"
#include "WAIT1.h"
#include "TU_TracTras.h"
#include "TU_TracDel.h"
#include "PTA.h"
#include "BADELANTE.h"
#include "BitIoLdd11.h"
#include "BATRAS.h"
#include "BitIoLdd12.h"
#include "BADDER.h"
#include "BitIoLdd13.h"
#include "BADIZQ.h"
#include "BitIoLdd14.h"
#include "BATDER.h"
#include "BitIoLdd15.h"
#include "BATIZQ.h"
#include "BitIoLdd16.h"
#include "BOK.h"
#include "BitIoLdd17.h"
#include "Led.h"
#include "CS1.h"
#include "FRTOS1.h"


//#include "TMOUT1.h"
#include "EncDel1.h"
#include "EncDel2.h"
#include "BitIoLdd5.h"
#include "EncDel3.h"
#include "BitIoLdd6.h"
#include "EncDel4.h"
#include "BitIoLdd7.h"
#include "BitClock.h"
#include "BitIoLdd8.h"
#include "BitData.h"
#include "BitIoLdd9.h"
#include "TPM_US.h"
#include "TRIG_DEL.h"
#include "TRIG_TRA.h"
#include "BitIoLdd1.h"
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd2.h"
#include "LEDG.h"
#include "LEDpin2.h"
#include "BitIoLdd3.h"
#include "PTD.h"
#include "PTE.h"
#include "BitIoLdd10.h"
#include "PTC.h"
#include "PTB.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Globales.h"
#include "Tareas.h"
#include "Motor.h"
#include "Ultrasonic.h"
#include "EncoderDelantero.h"
#include "Ps2.h"
#include "Mensaje.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	
	LEDR_Neg(); //Enciende LED rojo
	Motor_Init(); //Inicializa el PWM de para motores
	PS2_Init(); //Inicializa PS/2 de encoder diferencial
	EncDel_Init(); //Inicializa bits de encoder delantero
	US_Init(); //Inicializa los sensores de ultrasonido
	
	vInicializar_globales();
	vCrearTareas();
	
	//Prende LED verde, apaga LED rojo.
	LEDR_Neg();
	LEDG_Neg();

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.3 [05.09]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
