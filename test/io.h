
#ifndef IO_H_
#define IO_H_

#include "GPIO/GPIO.h"

extern gpio_map_t data_map;

extern gpio_map_t address_map;

extern gpio_t * vpp_12v5;
extern gpio_t * vpp_21v;
extern gpio_t * vpp_on;

extern gpio_t * sig_oe_vpp;
extern gpio_t * sig_add11_vpp;
extern gpio_t * sig_add13_vpp;
extern gpio_t * sig_add15_vpp;
extern gpio_t * sig_add17_vpp;
extern gpio_t * sig_add19_vpp;

extern gpio_t * CE;
extern gpio_t * OE;
extern gpio_t * PGM;

void reset_all(void);

#endif
