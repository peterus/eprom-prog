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

int main(void)
{
	UART_Init(UART_BAUD_SELECT(9600, F_CPU));
	interrupts(1); //sei();

	reset_all();
	
	while(1)
	{
		DEBUG_OUT("select chip:\n");
		uint32_t i = 0;
		while(1)
		{
			eprom_setting_t * eprom_setting = eprom_settings[i];
			if(eprom_setting == 0)
			{
				break;
			}
			printf("    [%lu] %s\n", i, eprom_setting->name);
			i++;
		}
		unsigned int c = 0;
		while((c = UART_GetC()) == UART_NO_DATA) {}
		eprom_setting_t * eprom_setting = eprom_settings[c-'0'];
		printf("selected chip: %s\n", eprom_setting->name);
		address_map.size = eprom_setting->address_pins_count;

		setup_power(eprom_setting);
		setup_relay(eprom_setting);
		sleep(100);

		uint32_t add = 9;

		// read data:
		read_data_start(eprom_setting);
		uint32_t data = read_data(eprom_setting, add);
		read_data_end(eprom_setting);
		printf("%lu\n", data);

		// program data:
		program_data_start(eprom_setting);
		for(i = 0; i < 0xf; i++)
		{
			program_data(eprom_setting, i, 0x00);
		}
		program_data_end(eprom_setting);

		// read data:
		read_data_start(eprom_setting);
		//for(i = 0; i < eprom_setting->max_data; i++)
		for(i = 0; i < 0xf; i++)
		{
			uint32_t data = 0;
			data = read_data(eprom_setting, i);
			printf("[%lu] 0x%02x\n", i, data);
		}
		read_data_end(eprom_setting);
	}
}
