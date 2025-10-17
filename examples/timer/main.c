#include <esp8266.h>
#include <stdint.h>

int main() {
	reset_pins();
	gpio_output_enable(2);
	gpio_set_level(2, HIGH);

	timer_init_t t_init;
	t_init.clkdiv = TIMER_CLKDIV_256;
	t_init.int_type = TIMER_LEVEL;
	t_init.autoload = 0;
	timer_init(t_init, 1000);

	timer_enable(1);


	while (1) {
		if (timer_is_count_zero()) {
			gpio_set_level(2, LOW);
			timer_enable(0);
			for (uint32_t i = 0; i < 80000; i++);
			gpio_set_level(2, HIGH);
			timer_clr_int();
			timer_init(t_init, 1000);
			timer_enable(1);
		}
	}
}
