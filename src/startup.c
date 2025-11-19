/*
 * file      : startup.c
 */

#include <driver/uart.h>
#include <stdint.h>

extern void main(void);
extern uint32_t _iram0_bss_start;
extern uint32_t _iram0_bss_end;
extern uint32_t _dram0_bss_start;
extern uint32_t _dram0_bss_end;

volatile uint32_t *reg = (volatile uint32_t *)0x60000D10;

void app_entry(void) {
	uint32_t vecaddr = 0x40100000;
	asm volatile("wsr %0, vecbase" : "=r"(vecaddr));

	// Changing CPU Frequency to 80Mhz
	*reg = 0x1880167;
	do {
		__asm__ __volatile__("memw");
	} while ((*reg & 0x2000000) != 0);
	*reg = 0x1910267;
	do {
		__asm__ __volatile__("memw");
	} while ((*reg & 0x2000000) != 0);

	// Clearning IRAM BSS
	uint32_t *p;
	for (p = &_iram0_bss_start; p < &_iram0_bss_start; p++) *p = 0;
	// Clearing DRAM BSS
	for (p = &_dram0_bss_start; p < &_dram0_bss_start; p++) *p = 0;

	main();
}
