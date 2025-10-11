/*
 * file      : startup.c
 * Author    : Lucky Bairagi (luckybairagi96@gmail.com)
 */

#include <context.h>
#include <stdint.h>

extern void main(void);

void app_entry(void) {
	save_context();
	main();
	restore_context();
}
