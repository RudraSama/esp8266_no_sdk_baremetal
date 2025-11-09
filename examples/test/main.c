#include <esp8266.h>
#include <stdint.h>
#include <utils.h>

int main() {
	reset_pins();

	uart_init(0, 9600, WORD_8_BITS, STOP_1_BIT);

	printf("\nhelo%x", 1);
	while (1) {
	}
}
