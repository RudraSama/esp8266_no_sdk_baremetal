#include <core/system.h>
#include <esp8266.h>
#include <stdint.h>

void func(void *arg) {
	uint32_t *flag = (uint32_t *)arg;
	*flag = *flag ? 0 : 1;
	gpio_set_level(2, *flag ? HIGH : LOW);
	printf("\n%d", *flag);
}

int main() {
	reset_pins();
	uart_init(0, 9600, WORD_8_BITS, STOP_1_BIT);

	gpio_output_enable(2);
	gpio_set_level(2, HIGH);

	timer_init_t t_init;
	t_init.clkdiv = TIMER_CLKDIV_256;
	t_init.int_type = TIMER_EDGE;
	t_init.autoload = 1;
	t_init.time_ms = 1000;
	timer_init(t_init);

	uint32_t flag = 0;
	timer_isr_attach(&func, &flag);

	timer_enable(1);

	while (1) {
	}
}
