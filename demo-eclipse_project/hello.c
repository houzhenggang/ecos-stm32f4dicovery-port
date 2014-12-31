#include <cyg/kernel/kapi.h>
//#include <cyg/hal/hal_io.h>
//#include <cyg/hal/plf_io.h>

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* now declare (and allocate space for) some kernel objects,
 like the two threads we will use */
cyg_thread thread_s[2]; /* space for two thread objects */

char stack[2][4096]; /* space for two 4K stacks */

/* now the handles for the threads */
cyg_handle_t simple_threadA, simple_threadB;

/* and now variables for the procedure which is the thread */
cyg_thread_entry_t simple_program;

/* and now a mutex to protect calls to the C library */
cyg_mutex_t cliblock;

void dbg_write_str(const char *msg) {
#ifdef __arm__
	// Manual semi-hosting, because the GCC ARM Embedded's semihosting wasn't working.
	for (; *msg; ++msg)
	{
		// Moves a pointer to msg into r1, sets r0 to 0x03,
		// and then performs a special breakpoint that OpenOCD sees as
		// the semihosting call. r0 tells OpenOCD which semihosting
		// function we're calling. In this case WRITEC, which writes
		// a single char pointed to by r1 to the console.
		__asm__ ("mov r1,%0; mov r0,$3; BKPT 0xAB" :
				: "r" (msg)
				: "r0", "r1"
		);
	}
#else
	printf("%s", msg);
#endif
}
/*
cyg_uint32 led1 = CYGHWR_HAL_STM32F4DISCOVERY_LED1;
cyg_uint32 led2 = CYGHWR_HAL_STM32F4DISCOVERY_LED2;
cyg_uint32 led3 = CYGHWR_HAL_STM32F4DISCOVERY_LED3;
cyg_uint32 led4 = CYGHWR_HAL_STM32F4DISCOVERY_LED4;
*/

/* we install our own startup routine which sets up threads */
void main(void) {
	/*CYGHWR_HAL_STM32_GPIO_SET(led1);
	CYGHWR_HAL_STM32_GPIO_SET(led2);
	CYGHWR_HAL_STM32_GPIO_SET(led3);
	CYGHWR_HAL_STM32_GPIO_SET(led4);*/
//	hal_stm32f4dis_led(1);

	dbg_write_str("Entering twothreads' cyg_user_start() function\n");

	cyg_mutex_init(&cliblock);

	cyg_thread_create(4, simple_program, (cyg_addrword_t) 0, "Thread A",
			(void *) stack[0], 4096, &simple_threadA, &thread_s[0]);
	cyg_thread_create(4, simple_program, (cyg_addrword_t) 1, "Thread B",
			(void *) stack[1], 4096, &simple_threadB, &thread_s[1]);

	cyg_thread_resume(simple_threadA);
	cyg_thread_resume(simple_threadB);
}

/* this is a simple program which runs in a thread */
//int flag = 1;
void simple_program(cyg_addrword_t data) {
	int message = (int) data;
	int delay;
	char buffer[256];

	if (message == 1) {

		//CYGHWR_HAL_STM32_GPIO_OUT(led2, 1);
		//CYGHWR_HAL_STM32_GPIO_OUT(led3, 1);
		//CYGHWR_HAL_STM32_GPIO_OUT(led4, 1);
		dbg_write_str("Beginning execution; thread data is 1\r\n");
	} else {
		//CYGHWR_HAL_STM32_GPIO_OUT(led1, 1);
		//CYGHWR_HAL_STM32_GPIO_OUT(led2, 1);
		//CYGHWR_HAL_STM32_GPIO_OUT(led2, 0x00);
		//CYGHWR_HAL_STM32_GPIO_OUT(led3, 0x00);
		//CYGHWR_HAL_STM32_GPIO_OUT(led4, 0x00);
		dbg_write_str("Beginning execution; thread data is 0\r\n");
	}

	cyg_thread_delay(200);

	for (;;) {
		delay = 200 + (rand() % 50);

		/* note: dbg_write_str() must be protected by a
		 call to cyg_mutex_lock() */
		cyg_mutex_lock(&cliblock);
		{
			//CYGHWR_HAL_STM32_GPIO_SET(led1);
			//CYGHWR_HAL_STM32_GPIO_OUT(led1, flag);
			//flag ^= flag;
			sprintf(buffer, "Thread %d: and now a delay of %d clock ticks\n",
					message, delay);
			dbg_write_str(buffer);
		}
		cyg_mutex_unlock(&cliblock);
		cyg_thread_delay(delay);
	}
}
