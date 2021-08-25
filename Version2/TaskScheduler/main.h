/*
 * main.h
 *
 *  Created on: Aug 23, 2021
 *      Author: simha
 */

#ifndef MAIN_H_
#define MAIN_H_

#define MAX_TASKS	5 // 4 user tasks + 1 idle task

/* Stack memory related calculations */
#define TASK_STACK_SIZE 	1024U
#define SCHED_STACK_SIZE	1024U

#define SRAM_START			0x20000000U
#define SRAM_SIZE			( (128) * (1024) )
#define SRAM_END			( (SRAM_START) + (SRAM_SIZE) )

#define IDLE_STACK_START	SRAM_END
#define T1_STACK_START		( (SRAM_END) - (1 * TASK_STACK_SIZE) )
#define T2_STACK_START		( (SRAM_END) - (2 * TASK_STACK_SIZE) )
#define T3_STACK_START		( (SRAM_END) - (3 * TASK_STACK_SIZE) )
#define T4_STACK_START		( (SRAM_END) - (4 * TASK_STACK_SIZE) )
#define SCHED_STACK_START	( (SRAM_END) - (5 * TASK_STACK_SIZE) )

/* Clock related configurations */
#define HSI_CLOCK			16000000U
#define SYSTICK_TIM_CLK		HSI_CLOCK
#define TICK_HZ				1000U

/* Task Stack related macros */
#define DUMMY_XPSR 0x01000000U

/* Task state related macros */
#define TASK_READY_STATE 	0x00
#define TASK_BLOCKED_STATE 	0xFF

/* Interrup enable/disable macros */
#define INTERRUPT_DISABLE()	do{__asm volatile ("MOV R0,#0x1"); __asm volatile ("MSR PRIMASK,R0"); } while(0)
#define INTERRUPT_ENABLE() 	do{__asm volatile ("MOV R0,#0x0"); __asm volatile ("MSR PRIMASK,R0"); } while(0)

#endif /* MAIN_H_ */
