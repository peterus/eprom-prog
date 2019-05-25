
#ifndef IO_H_
#define IO_H_

#include "GPIO/GPIO.h"

extern gpio_map_t data_map;

extern gpio_map_t address_map;

extern gpio_t * vpp_12v5_pin;
extern gpio_t * vpp_21v_pin;
extern gpio_t * vpp_on_pin;

extern gpio_t * sig_oe_vpp_pin;
extern gpio_t * sig_add11_vpp_pin;
extern gpio_t * sig_add13_vcc_pin;
extern gpio_t * sig_add15_vpp_pin;
extern gpio_t * sig_add17_vcc_pin;
extern gpio_t * sig_add19_vpp_pin;

extern gpio_t * CE_pin;
extern gpio_t * OE_pin;
extern gpio_t * PGM_pin;

void reset_all(void);

#endif
