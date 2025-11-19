#include <core/reg_rw.h>
#include <core/system.h>
#include <esp8266.h>
#include <stdint.h>
#include <utils.h>

extern uint32_t _dram0_data_start;
extern uint32_t _dram0_data_end;

int main() {
	reset_pins();
	uart_init(0, 9600, WORD_8_BITS, STOP_1_BIT);

	uint32_t *p = &_dram0_data_start;
	while (p < &_dram0_data_end) {
		printf("%x\n", *p);
		p++;
	}

	while (1) {
	}
}
