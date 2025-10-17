#include <esp8266.h>

int main() {
	reset_pins();

	uart_init(0, 9600, WORD_8_BITS, STOP_1_BIT);
	while (1) {
		write_line(0, "HELLO");
		for (uint32_t i = 0; i < 80000; i++);
		for (uint32_t i = 0; i < 80000; i++);
		for (uint32_t i = 0; i < 80000; i++);
		for (uint32_t i = 0; i < 80000; i++);
	}
}
