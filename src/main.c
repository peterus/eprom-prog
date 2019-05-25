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

eprom_setting_t M27C801 = {
	.name = "27C801",
	.vpp_power = VPP_12V5,
	.sig_oe_vpp_activ = USE_v,
	.sig_add11_vpp_activ = USE_ADD,
	.sig_add13_vcc_activ = USE_ADD,
	.sig_add15_vpp_activ = USE_ADD,
	.sig_add17_vcc_activ = USE_ADD,
	.sig_add19_vpp_activ = USE_ADD,
	.address_pins_count = 20,
	.max_data = 2^20,
};

eprom_setting_t M27C4001 = {
	.name = "27C4001 (not tested)",
	.vpp_power = VPP_12V5,
	.sig_oe_vpp_activ = USE_ADD,
	.sig_add11_vpp_activ = USE_ADD,
	.sig_add13_vcc_activ = USE_ADD,
	.sig_add15_vpp_activ = USE_ADD,
	.sig_add17_vcc_activ = USE_ADD,
	.sig_add19_vpp_activ = USE_v,
	.address_pins_count = 19,
	.max_data = 2^19,
};

eprom_setting_t M27C2001 = {
	.name = "27C2001 (not tested)",
	.vpp_power = VPP_12V5,
	.sig_oe_vpp_activ = USE_ADD,
	.sig_add11_vpp_activ = USE_ADD,
	.sig_add13_vcc_activ = USE_ADD,
	.sig_add15_vpp_activ = USE_ADD,
	.sig_add17_vcc_activ = USE_ADD,
	.sig_add19_vpp_activ = USE_v,
	.address_pins_count = 18,
	.max_data = 2^18,
};

eprom_setting_t M27C1001 = {
	.name = "27C1001 (not tested)",
	.vpp_power = VPP_12V5,
	.sig_oe_vpp_activ = USE_ADD,
	.sig_add11_vpp_activ = USE_ADD,
	.sig_add13_vcc_activ = USE_ADD,
	.sig_add15_vpp_activ = USE_ADD,
	.sig_add17_vcc_activ = USE_ADD,
	.sig_add19_vpp_activ = USE_v,
	.address_pins_count = 17,
	.max_data = 2^17,
};

eprom_setting_t M27C512 = {
	.name = "27C512 (not tested)",
	.vpp_power = VPP_12V5,
	.sig_oe_vpp_activ = USE_v,
	.sig_add11_vpp_activ = USE_ADD,
	.sig_add13_vcc_activ = USE_ADD,
	.sig_add15_vpp_activ = USE_ADD,
	.sig_add17_vcc_activ = USE_v,
	.sig_add19_vpp_activ = USE_ADD,
	.address_pins_count = 16,
	.max_data = 2^16,
};

eprom_setting_t M27C256 = {
	.name = "27C256 (not tested)",
	.vpp_power = VPP_12V5,
	.sig_oe_vpp_activ = USE_ADD,
	.sig_add11_vpp_activ = USE_ADD,
	.sig_add13_vcc_activ = USE_ADD,
	.sig_add15_vpp_activ = USE_v,
	.sig_add17_vcc_activ = USE_v,
	.sig_add19_vpp_activ = USE_ADD,
	.address_pins_count = 15,
	.max_data = 2^15,
};

eprom_setting_t M27C128 = {
	.name = "27C128 (not tested)",
	.vpp_power = VPP_12V5,
	.sig_oe_vpp_activ = USE_ADD,
	.sig_add11_vpp_activ = USE_ADD,
	.sig_add13_vcc_activ = USE_ADD,
	.sig_add15_vpp_activ = USE_v,
	.sig_add17_vcc_activ = USE_v,
	.sig_add19_vpp_activ = USE_ADD,
	.address_pins_count = 14,
	.max_data = 2^14,
};

eprom_setting_t M27C64 = {
	.name = "27C64 (not tested)",
	.vpp_power = VPP_12V5,
	.sig_oe_vpp_activ = USE_ADD,
	.sig_add11_vpp_activ = USE_ADD,
	.sig_add13_vcc_activ = USE_ADD,
	.sig_add15_vpp_activ = USE_v,
	.sig_add17_vcc_activ = USE_v,
	.sig_add19_vpp_activ = USE_ADD,
	.address_pins_count = 13,
	.max_data = 2^13,
};

eprom_setting_t M27C32 = {
	.name = "27C32 (not tested)",
	.vpp_power = VPP_12V5,
	.sig_oe_vpp_activ = USE_v,
	.sig_add11_vpp_activ = USE_ADD,
	.sig_add13_vcc_activ = USE_v,
	.sig_add15_vpp_activ = USE_ADD,
	.sig_add17_vcc_activ = USE_ADD,
	.sig_add19_vpp_activ = USE_ADD,
	.address_pins_count = 12,
	.max_data = 2^12,
};

eprom_setting_t M27C16 = {
	.name = "27C16 (not tested)",
	.vpp_power = VPP_12V5,
	.sig_oe_vpp_activ = USE_ADD,
	.sig_add11_vpp_activ = USE_v,
	.sig_add13_vcc_activ = USE_v,
	.sig_add15_vpp_activ = USE_ADD,
	.sig_add17_vcc_activ = USE_ADD,
	.sig_add19_vpp_activ = USE_ADD,
	.address_pins_count = 11,
	.max_data = 2^11,
};

eprom_setting_t * eprom_settings[] = {
	&M27C801,
	&M27C4001,
	&M27C2001, // ADD18 = PGM
	&M27C1001, // ADD18 = PGM
	&M27C512,
	&M27C256,
	&M27C128,
	&M27C64,
	&M27C32,
	&M27C16,
	0,
};


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
