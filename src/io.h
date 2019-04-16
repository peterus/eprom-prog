
gpio_t * data[8] = {
	&gpio[ePORTK]
}

gpio_t * address[20] = {
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

gpio_t * vpp_12v5 = &gpio[ePORTA][1];
gpio_t * vpp_21v  = &gpio[ePORTC][0];
gpio_t * vpp_on   = &gpio[ePORTG][2];

gpio_t * sig_oe_vpp = &gpio[ePORTE][5];
gpio_t * sig_add11_vpp = &gpio[ePORTH][5];
gpio_t * sig_add13_vpp = &gpio[ePORTB][4];
gpio_t * sig_add15_vpp = &gpio[ePORTL][0];
gpio_t * sig_add17_vpp = &gpio[ePORTB][6];
gpio_t * sig_add19_vpp = &gpio[ePORTD][7];

gpio_t * CE = &gpio[ePORTC][5];
gpio_t * OE = &gpio[ePORTE][3];
gpio_t * PGM = &gpio[ePORTA][0];

void reset_all(void);


