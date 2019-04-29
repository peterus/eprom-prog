
#include "GPIO/GPIO.h"

gpio_map_t data_map = {
	.size = 8,
	.gpio = { &gpio[ePORTK][0], &gpio[ePORTK][1], &gpio[ePORTK][2], &gpio[ePORTK][3], &gpio[ePORTK][4], &gpio[ePORTK][5], &gpio[ePORTK][6], &gpio[ePORTK][7] }
};

gpio_map_t address_map = {
	.size = 20,
	.gpio = { 
		&gpio[ePORTF][0],
		&gpio[ePORTF][1],
		&gpio[ePORTF][2],
		&gpio[ePORTF][3],
		&gpio[ePORTF][4],
		&gpio[ePORTF][5],
		&gpio[ePORTF][6],
		&gpio[ePORTF][7], // ADD7
		&gpio[ePORTA][4], // ADD8
		&gpio[ePORTA][6], // ADD9
		&gpio[ePORTC][7], // ADD10
		&gpio[ePORTH][6], // ADD11
		&gpio[ePORTL][1], // ADD12
		&gpio[ePORTB][5], // ADD13
		&gpio[ePORTA][2], // ADD14
		&gpio[ePORTB][0], // ADD15
		&gpio[ePORTL][3], // ADD16
		&gpio[ePORTB][7], // ADD17
		&gpio[ePORTA][0], // ADD18 / PGM
		&gpio[ePORTG][1], // ADD19
	}
};

gpio_t * vpp_12v5 = &gpio[ePORTA][1];
gpio_t * vpp_21v  = &gpio[ePORTC][0];
gpio_t * vpp_on   = &gpio[ePORTG][2];

gpio_t * sig_oe_vpp = &gpio[ePORTE][5];
gpio_t * sig_add11_vpp = &gpio[ePORTH][5];
gpio_t * sig_add13_vcc = &gpio[ePORTB][4];
gpio_t * sig_add15_vpp = &gpio[ePORTL][0];
gpio_t * sig_add17_vcc = &gpio[ePORTB][6];
gpio_t * sig_add19_vpp = &gpio[ePORTD][7];

gpio_t * CE = &gpio[ePORTC][5];
gpio_t * OE = &gpio[ePORTE][3];
gpio_t * PGM = &gpio[ePORTA][0];


void reset_all(void)
{
	set_output_map(&data_map);
	set_output_map(&address_map);

	set_output(vpp_on);
	set_output(vpp_12v5);
	set_output(vpp_21v);

	set_output(sig_oe_vpp);
	set_output(sig_add11_vpp);
	set_output(sig_add13_vcc);
	set_output(sig_add15_vpp);
	set_output(sig_add17_vcc);
	set_output(sig_add19_vpp);

	set_output(CE);
	set_output(OE);
	set_output(PGM);

	set_pins_map(&data_map, 0);
	set_pins_map(&address_map, 0);

	set_high(vpp_on);
	set_low(vpp_12v5);
	set_low(vpp_21v);

	set_low(sig_oe_vpp);
	set_low(sig_add11_vpp);
	set_low(sig_add13_vcc);
	set_low(sig_add15_vpp);
	set_low(sig_add17_vcc);
	set_low(sig_add19_vpp);

	set_low(CE);
	set_low(OE);
	set_low(PGM);
}
