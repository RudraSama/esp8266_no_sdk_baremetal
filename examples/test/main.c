#include <esp8266.h>
#include <reg_rw.h>
#include <stdint.h>
#include <system.h>
#include <utils.h>

#define REG 0x60000D10

volatile uint32_t *reg = (volatile uint32_t *)REG;


int main() {
	reset_pins();

	*reg = 0x1880167;
	do {
		__asm__ __volatile__("memw");
	} while ((*reg & 0x2000000) != 0);
	*reg = 0x1910267;
	do {
		__asm__ __volatile__("memw");
	} while ((*reg & 0x2000000) != 0);

	uart_init(0, 9600, WORD_8_BITS, STOP_1_BIT);

	printf("\nhelo%x %d", 12, 343);
	while (1) {
	}
}
