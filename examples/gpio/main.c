#include <esp8266.h>
#include <stdint.h>

void main(void) {
	reset_pins();

	unsigned int rx;
	gpio_output_enable(2);

	gpio_set_level(2, 0);
	for (rx = 0; rx < 800000; rx++);
	for (rx = 0; rx < 800000; rx++);
	for (rx = 0; rx < 800000; rx++);
	for (rx = 0; rx < 800000; rx++);
	for (rx = 0; rx < 800000; rx++);
	for (rx = 0; rx < 800000; rx++);

	gpio_set_level(2, 1);

	while (1);
}
