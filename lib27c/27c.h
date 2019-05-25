
#ifndef h27C_H_
#define h27C_H_

enum vpp_e
{
	VPP_12V5,
	VPP_21V,
};

enum add_or_v_e
{
	USE_ADD,
	USE_v,
};

typedef struct
{
	uint8_t vpp_power; // vpp_e
	uint8_t sig_oe_vpp_activ;  // add_or_v_e
	uint8_t sig_add11_vpp_activ; // add_or_v_e
	uint8_t sig_add13_vcc_activ; // add_or_v_e
	uint8_t sig_add15_vpp_activ; // add_or_v_e
	uint8_t sig_add17_vcc_activ; // add_or_v_e
	uint8_t sig_add19_vpp_activ; // add_or_v_e
	uint8_t address_pins_count;
	uint32_t max_data;
	uint8_t name[];
} eprom_setting_t;


void setup_power(eprom_setting_t * setting);
void setup_relay(eprom_setting_t * setting);

void read_data_start(eprom_setting_t * setting);
uint32_t read_data(eprom_setting_t * setting, uint32_t address);
void read_data_end(eprom_setting_t * setting);

void program_data_start(eprom_setting_t * setting);
void program_data(eprom_setting_t * setting, uint32_t address, uint8_t data);
void program_data_end(eprom_setting_t * setting);


extern eprom_setting_t * eprom_settings[];

#endif
