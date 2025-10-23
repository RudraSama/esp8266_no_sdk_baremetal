#include <esp8266.h>
#include <stdint.h>
#include <utils.h>

int main() {
	reset_pins();

	timer_init_t t_init;
	t_init.clkdiv = TIMER_CLKDIV_256;
	t_init.int_type = TIMER_LEVEL;
	t_init.autoload = 0;

	timer_enable(1);

	while (1) {
	}
}
