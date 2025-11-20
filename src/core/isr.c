/*
 * file     : isr.h
 */

#include <core/isr.h>
#include <libs/printf.h>

static isr_t isr[INTERRUPT_MAX];

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

			if (!(bit & intr) || !(isr[bit].cb)) continue;

			isr[bit].cb(isr[bit].arg);

			clear_int_mask(bit);

			intr = intr & ~(bit);
		}
	}
}

void isr_attach(uint32_t inum, isr_cb cb, void *arg) {
	isr[inum].cb = cb;
	isr[inum].arg = arg;
}

void isr_detach(uint32_t inum) {
	isr[inum].cb = (void *)0;
	isr[inum].arg = (void *)0;
}
