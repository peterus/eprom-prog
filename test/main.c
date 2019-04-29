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

	DEBUG_OUT("will reset!\n");
	reset_all();

	while(UART_GetC() == UART_NO_DATA)
	{
	}

	DEBUG_OUT("VPP on, 12.5V!\n");
	set_high(vpp_12v5);
	set_low(vpp_21v);
	set_low(vpp_on);

	while(UART_GetC() == UART_NO_DATA)
	{
	}

	DEBUG_OUT("VPP on, 21V!\n");
	set_low(vpp_12v5);
	set_high(vpp_21v);
	set_low(vpp_on);

	while(UART_GetC() == UART_NO_DATA)
	{
	}

	DEBUG_OUT("VPP off!\n");
	set_low(vpp_12v5);
	set_low(vpp_21v);
	set_high(vpp_on);

	while(UART_GetC() == UART_NO_DATA)
	{
	}

	DEBUG_OUT("VPP on, 21V, VPP on ADD19/VPP!\n");
	set_high(vpp_21v);
	set_low(vpp_on);
	set_high(sig_oe_vpp);
	set_high(sig_add11_vpp);
	set_high(sig_add13_vcc);
	set_high(sig_add15_vpp);
	set_high(sig_add17_vcc);
	set_high(sig_add19_vpp);

	DEBUG_OUT("Test finished!\n");
	printf("TEST: %lu\n", (long unsigned int)max);
	
	while(1)
	{
	}
}
