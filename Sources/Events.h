/* ###################################################################
**     Filename    : Events.h
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-10-19, 18:53, # CodeGen: 31
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         FRTOS1_vApplicationStackOverflowHook - void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName);
**         FRTOS1_vApplicationTickHook          - void FRTOS1_vApplicationTickHook(void);
**         FRTOS1_vApplicationIdleHook          - void FRTOS1_vApplicationIdleHook(void);
**         FRTOS1_vApplicationMallocFailedHook  - void FRTOS1_vApplicationMallocFailedHook(void);
**         Cpu_OnNMIINT                         - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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

#ifdef __cplusplus
extern "C" {
#endif 

void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationStackOverflowHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         if enabled, this hook will be called in case of a stack
**         overflow.
**     Parameters  :
**         NAME            - DESCRIPTION
**         pxTask          - Task handle
**       * pcTaskName      - Pointer to task name
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationTickHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationTickHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called by the RTOS for every
**         tick increment.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationMallocFailedHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationMallocFailedHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, the RTOS will call this hook in case memory
**         allocation failed.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


void FRTOS1_vOnPreSleepProcessing(portTickType expectedIdleTicks);
/*
** ===================================================================
**     Event       :  FRTOS1_vOnPreSleepProcessing (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         Used in tickless idle mode only, but required in this mode.
**         Hook for the application to enter low power mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         expectedIdleTicks - expected idle
**                           time, in ticks
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  TPM_US_OnCounterRestart (module Events)
**
**     Component   :  TPM_US [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TPM_US_OnCounterRestart(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  TPM_US_OnChannel0 (module Events)
**
**     Component   :  TPM_US [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if compare register match the counter registers or
**         capture register has a new content. OnChannel0 event and
**         Timer unit must be enabled. See [SetEventMask] and
**         [GetEventMask] methods. This event is available only if a
**         [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TPM_US_OnChannel0(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  TPM_US_OnChannel1 (module Events)
**
**     Component   :  TPM_US [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if compare register match the counter registers or
**         capture register has a new content. OnChannel1 event and
**         Timer unit must be enabled. See [SetEventMask] and
**         [GetEventMask] methods. This event is available only if a
**         [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TPM_US_OnChannel1(LDD_TUserData *UserDataPtr);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
