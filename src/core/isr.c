/*
 * file     : isr.h
 */

#include <core/isr.h>
#include <libs/printf.h>

static inline uint32_t get_int_mask(void) {
	uint32_t interrupt;
	uint32_t enable;

	asm volatile(
	    "rsr %0, interrupt\n"
	    "rsr %1, intenable\n"
	    "rsync\n"
	    : "=r"(interrupt), "=r"(enable));

	return interrupt & enable & 0x00003fff;
}

static inline void clear_int_mask(uint32_t bit) {
	asm volatile("wsr %0, intclear" : : "r"(bit));
}

void isr_handler(void) {
	uint32_t intr;

	while ((intr = get_int_mask()) && intr) {
		for (uint32_t i = 0; i < INTERRUPT_MAX && intr; i++) {
			uint32_t bit = (1 << i);

			if (!(bit & intr)) continue;

			clear_int_mask(bit);

			intr = intr & ~(bit);
			// will do something here
		}
	}
}
