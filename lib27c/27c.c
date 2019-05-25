/*
 * 27c.c
 *
 * Created: 04.05.2019 19:01:09
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

void setup_power(eprom_setting_t * setting)
{
	//printf("vpp: %c\n", '0'+setting->vpp_power);
	if(setting->vpp_power == VPP_12V5)
	{
		//DEBUG_OUT("Set VPP to 12.5V.\n");
		set_low(vpp_21v_pin);
		set_high(vpp_12v5_pin);
	}
	else if(setting->vpp_power == VPP_21V)
	{
		//DEBUG_OUT("Set VPP to 21V.\n");
		set_low(vpp_12v5_pin);
		set_high(vpp_21v_pin);
	} else {
		DEBUG_OUT("ERROR in VPP setting");
	}
}

void setup_relay(eprom_setting_t * setting)
{
	if(setting->sig_add11_vpp_activ == USE_ADD)
	{
		set_low(sig_add11_vpp_pin);
	}
	else
	{
		set_high(sig_add11_vpp_pin);
	}
	if(setting->sig_add13_vcc_activ == USE_ADD)
	{
		set_low(sig_add13_vcc_pin);
	}
	else
	{
		set_high(sig_add13_vcc_pin);
	}
	if(setting->sig_add15_vpp_activ == USE_ADD)
	{
		set_low(sig_add15_vpp_pin);
	}
	else
	{
		set_high(sig_add15_vpp_pin);
	}
	if(setting->sig_add17_vcc_activ == USE_ADD)
	{
		set_low(sig_add17_vcc_pin);
	}
	else
	{
		set_high(sig_add17_vcc_pin);
	}
	if(setting->sig_add19_vpp_activ == USE_ADD)
	{
		set_low(sig_add19_vpp_pin);
	}
	else
	{
		set_high(sig_add19_vpp_pin);
	}
	set_high(CE_pin);
	set_high(OE_pin);
}

void read_data_start(eprom_setting_t * setting)
{
	// set_low(E)
	set_low(CE_pin);

	_delay_us(0.100);

	// set_low(G)
	set_low(OE_pin);

	_delay_us(0.050);
}

uint32_t read_data(eprom_setting_t * setting, uint32_t address)
{
	// set ADD
	set_pins_map(&address_map, address);

	_delay_us(0.100);

	// read DATA
	uint32_t data = get_status_map(&data_map);

	return data;
}

void read_data_end(eprom_setting_t * setting)
{
	// set_high(E, G)
	set_high(CE_pin);
	set_high(OE_pin);
}

void program_data_start(eprom_setting_t * setting)
{
	set_high(sig_oe_vpp_pin);
	sleep(2);

	// set VPP
	set_low(vpp_on_pin);
}

void program_data(eprom_setting_t * setting, uint32_t address, uint8_t data)
{
	// set ADD
	set_pins_map(&address_map, address);
	// set DATA
	set_output_map(&data_map);
	set_pins_map(&data_map, data);
	_delay_us(2);
	// set_low(E)
	set_low(CE_pin);
	// wait 50 us
	_delay_us(50);
	// set_high(E)
	set_high(CE_pin);
	_delay_us(2);
	sleep(2);
}

void program_data_end(eprom_setting_t * setting)
{
	// remove DATA
	set_pins_map(&data_map, 0);
	set_input_map(&data_map);
	// set_low(VPP)
	set_high(vpp_on_pin);
	set_low(sig_oe_vpp_pin);
	_delay_us(2);
}


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
