/*
 * file      : startup.c
 * Author    : Lucky Bairagi (luckybairagi96@gmail.com)
 */

#include <context.h>
#include <stdint.h>

extern void main(void);

void app_entry(void) {
	uint32_t a = 0x40100000;
	asm volatile("wsr %0, vecbase" : "=r"(a));
	save_context();
	main();
	restore_context();
}
