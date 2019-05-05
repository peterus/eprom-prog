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
	printf("vpp: %c\n", '0'+setting->vpp_power);
	if(setting->vpp_power == VPP_12V5)
	{
		DEBUG_OUT("Set VPP to 12.5V.\n");
		set_low(vpp_21v_pin);
		set_high(vpp_12v5_pin);
	}
	else if(setting->vpp_power == VPP_21V)
	{
		DEBUG_OUT("Set VPP to 21V.\n");
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
