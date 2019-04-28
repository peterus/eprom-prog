/*
 * UART_Test.c
 *
 * Created: 26.10.2014 19:01:09
 *  Author: Peter Buchegger
 */ 


#include <stdint.h>
#include <stdio.h>
#include "COM/UART.h"
#define _DEBUG
#include "Debug.h"
#include "System.h"

#include "io.h"

int main(void)
{
	uint32_t max = 0xFFFFFFFF;
	UART_Init(UART_BAUD_SELECT(9600, F_CPU));
	interrupts(1); //sei();
	
	while(UART_GetC() == UART_NO_DATA)
	{
	}

	reset_all();
	
	while(1)
	{
		printf("TEST: %lu\n", (long unsigned int)max);
		DEBUG_OUT("HALLOOOO\n");
	}
}
