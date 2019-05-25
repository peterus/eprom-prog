/*
 * UART_Test.c
 *
 * Created: 26.10.2014 19:01:09
 *  Author: Peter Buchegger
 */ 


#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include "COM/UART.h"
#define _DEBUG
#include "Debug.h"
#include "System.h"

#include "io.h"
#include "27c.h"

/*************************************
---> set eprom type
1. byte: 0x01
2. byte: enum EPROM_Type { 801 = 0, 4001 = 1, 2001 = 2, 1001 = 3, 512 = 4, 256 = 5, 128 = 6, 64 = 7, 32 = 8, 16 = 9 }
3. byte: enum EPROM_VPP { 12.5V = 0, 21V = 1 }

---> set address
1. byte: 0x02
2. byte: address (higher byte)
3. byte: address (lower byte)

---> read data (with address increment)
1. byte: 0x03
2. byte: length to read in bytes

---> write data (with address increment)
1. byte 0x04
2. byte: length to write
x. byte: data

all answers are:
1. byte: 0x1.
other bytes are the same as sent
*************************************/

eprom_setting_t * eprom_setting = 0;
uint32_t address = 0;

void set_eprom_type(void)
{
	unsigned int type = 0;
	unsigned int vpp = 0;
	while((type = UART_GetC()) == UART_NO_DATA) {} // 2. byte: type
	eprom_setting = eprom_settings[type];
	
	while((vpp = UART_GetC()) == UART_NO_DATA) {} // 3. byte: vpp
	eprom_setting->vpp_power = vpp;

	address_map.size = eprom_setting->address_pins_count;
	printf("selected chip: %s\n", eprom_setting->name);

	reset_all();
	setup_power(eprom_setting);
	setup_relay(eprom_setting);
	sleep(100);

	UART_PutByte(0x11);
	UART_PutByte((uint8_t)type);
	UART_PutByte((uint8_t)vpp);
}

void set_address(void)
{
	uint8_t upper = 0;
	uint8_t lower = 0;
	unsigned int buffer = 0;
	while((buffer = UART_GetC()) == UART_NO_DATA) {} // 2. byte: address (higher byte)
	upper = buffer & 0xFF;
	while((buffer = UART_GetC()) == UART_NO_DATA) {} // 3. byte: address (lower byte)
	lower = buffer & 0xFF;

	address = upper << 8 | lower;

	UART_PutByte(0x12);
	UART_PutByte(upper);
	UART_PutByte(lower);
}

void read_data_(void)
{
	unsigned int length = 0;
	while((length = UART_GetC()) == UART_NO_DATA) {} // 2. byte: length to read in bytes
	uint32_t len = length & 0xFF;

	UART_PutByte(0x13);
	read_data_start(eprom_setting);
	for(uint8_t i = 0; i < len; i++)
	{
		uint32_t data = read_data(eprom_setting, address);
		UART_PutByte((uint8_t)data);
		address++;
	}
	read_data_end(eprom_setting);
}

void write_data_(void)
{
	unsigned int length = 0;
	while((length = UART_GetC()) == UART_NO_DATA) {} // 2. byte: length to read in bytes

	UART_PutByte(0x14);
	UART_PutByte((uint8_t)length);
	program_data_start(eprom_setting);
	for(uint8_t i = 0; i < length; i++)
	{
		unsigned int data = 0;
		while((data = UART_GetC()) == UART_NO_DATA) {} // x. byte: data
		program_data(eprom_setting, address, (uint8_t)data);
		UART_PutByte((uint8_t)data);
		address++;
	}
	program_data_end(eprom_setting);

}

int main(void)
{
	UART_Init(UART_BAUD_SELECT(9600, F_CPU));
	interrupts(1); //sei();

	reset_all();
	DEBUG_OUT("ready\n");
	
	while(1)
	{
		unsigned int c = 0;
		while((c = UART_GetC()) == UART_NO_DATA) {}

		switch(c)
		{
			case 0x01:
				set_eprom_type();
				break;
			case 0x02:
				set_address();
				break;
			case 0x03:
				read_data_();
				break;
			case 0x04:
				write_data_();
				break;
			default:
				break;
		}
	}
}
