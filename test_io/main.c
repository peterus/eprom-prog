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
	UART_Init(UART_BAUD_SELECT(9600, F_CPU));
	interrupts(1); //sei();
	
	while(UART_GetC() == UART_NO_DATA) {}
	DEBUG_OUT("will reset!\n");
	reset_all();

	while(UART_GetC() == UART_NO_DATA) {}
	DEBUG_OUT("VPP on, 12.5V!\n");
	set_high(vpp_12v5_pin);
	set_low(vpp_21v_pin);
	set_low(vpp_on_pin);

	while(UART_GetC() == UART_NO_DATA) {}
	DEBUG_OUT("VPP on, 21V!\n");
	set_low(vpp_12v5_pin);
	set_high(vpp_21v_pin);
	set_low(vpp_on_pin);

	while(UART_GetC() == UART_NO_DATA) {}
	DEBUG_OUT("VPP off!\n");
	set_low(vpp_12v5_pin);
	set_low(vpp_21v_pin);
	set_high(vpp_on_pin);

	while(UART_GetC() == UART_NO_DATA) {}
	DEBUG_OUT("VPP on, 21V, VPP on ADD19/VPP!\n");
	set_high(vpp_21v_pin);
	set_low(vpp_on_pin);
	set_high(sig_oe_vpp_pin);
	set_high(sig_add11_vpp_pin);
	set_high(sig_add13_vcc_pin);
	set_high(sig_add15_vpp_pin);
	set_high(sig_add17_vcc_pin);
	set_high(sig_add19_vpp_pin);

	while(UART_GetC() == UART_NO_DATA) {}
	DEBUG_OUT("Reset!\n");
	reset_all();

	uint32_t k = 1;
	for(uint8_t i = 0; i < data_map.size; i++)
	{
		while(UART_GetC() == UART_NO_DATA) {}
		printf("data[%i]: %i\n", i, k);
		set_pins_map(&data_map, k);
		k = (k << 1);
	}

	while(UART_GetC() == UART_NO_DATA) {}
	DEBUG_OUT("Reset!\n");
	reset_all();

	k = 1;
	for(uint32_t i = 0; i < address_map.size; i++)
	{
		while(UART_GetC() == UART_NO_DATA) {}
		printf("address[%lu]: %lu\n", i, k);
		set_pins_map(&address_map, k);
		k = (k << 1);
	}

	while(UART_GetC() == UART_NO_DATA) {}
	DEBUG_OUT("Reset!\n");
	reset_all();

	while(UART_GetC() == UART_NO_DATA) {}
	DEBUG_OUT("PGM high!\n");
	set_high(PGM_pin);

	while(UART_GetC() == UART_NO_DATA) {}
	DEBUG_OUT("OE high!\n");
	set_low(PGM_pin);
	set_high(OE_pin);

	while(UART_GetC() == UART_NO_DATA) {}
	DEBUG_OUT("CE high!\n");
	set_low(OE_pin);
	set_high(CE_pin);

	while(UART_GetC() == UART_NO_DATA) {}
	DEBUG_OUT("Reset!\n");
	reset_all();

	DEBUG_OUT("Test finished!\n");
	
	while(1) {}
}
