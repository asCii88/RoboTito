/* ###################################################################
 **     Filename    : Events.c
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
 ** @file Events.c
 ** @version 01.00
 ** @brief
 **         This is user's event module.
 **         Put your event handler code here.
 */         
/*!
 **  @addtogroup Events_module Events module documentation
 **  @{
 */         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Ultrasonic.h"
#include "Globales.h"
#include "FRTOS1.h"
#include "PE_Types.h"
#include "semphr.h"
#include "queue.h"
#include "Mensaje.h"


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
void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName)
{
	/* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. */
	(void)pxTask;
	(void)pcTaskName;
	taskDISABLE_INTERRUPTS();
	/* Write your code here ... */
	for(;;) {}
}

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
void FRTOS1_vApplicationTickHook(void)
{
	/* Called for every RTOS tick. */
	/* Write your code here ... */
}

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
void FRTOS1_vApplicationMallocFailedHook(void)
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
     free memory available in the FreeRTOS heap.  pvPortMalloc() is called
     internally by FreeRTOS API functions that create tasks, queues, software
     timers, and semaphores.  The size of the FreeRTOS heap is set by the
     configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	taskDISABLE_INTERRUPTS();
	/* Write your code here ... */
	for(;;) {}
}

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
void Cpu_OnNMIINT(void)
{
	/* Write your code here ... */
}

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
void FRTOS1_vOnPreSleepProcessing(portTickType expectedIdleTicks)
{
	(void)expectedIdleTicks; /* not used */
#if 1
	/* example for Kinetis (enable SetOperationMode() in CPU component): */
	Cpu_SetOperationMode(DOM_WAIT, NULL, NULL);
	/* or to wait for interrupt:
    __asm volatile("dsb");
    __asm volatile("wfi");
    __asm volatile("isb");
	 */
#elif 0
	/* example for S08/S12/ColdFire V1 (enable SetWaitMode() in CPU): */
	Cpu_SetWaitMode();
#elif 0
	/* example for ColdFire V2: */
	__asm("stop #0x2000"); */
#else
#error "you *must* enter low power mode (wait for interrupt) here!"
#endif
	/* Write your code here ... */
}

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
void TPM_US_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
	US_EventEchoOverflow();
}

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
void TPM_US_OnChannel0(LDD_TUserData *UserDataPtr)
{
	US_EventEchoCapture(ADELANTE);
}

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
void TPM_US_OnChannel1(LDD_TUserData *UserDataPtr)
{
	US_EventEchoCapture(ATRAS);
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
