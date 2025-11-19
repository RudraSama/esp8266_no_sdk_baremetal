/*
 * file      : printf.h
 */

#include <driver/uart.h>
#include <libs/printf.h>
#include <stdarg.h>

static void write_int(int num) {
	if (num == 0) {
		write_char(0, '0');
		return;
	}
	uint32_t is_neg = 0;
	char result[10];
	if (num < 0) is_neg = 1;

	uint32_t itr = 0;
	while (num) {
		result[itr++] = '0' + num % 10;
		num = num / 10;
	}

	if (is_neg) {
		write_char(0, '-');
	}

	while (itr > 0) {
		write_char(0, result[--itr]);
	}
}

static void write_hex(int num) {
	uint32_t is_neg = 0;
	char result[10];
	if (num < 0) is_neg = 1;

	uint32_t itr = 0;
	while (num) {
		uint32_t val = num % 16;
		result[itr++] = (val <= 9) ? '0' + val : 'A' + (val - 10);
		num = num / 16;
	}

	if (is_neg) {
		write_char(0, '-');
	}

	while (itr > 0) {
		write_char(0, result[--itr]);
	}
}


void printf(const char *str, ...) {
	uint32_t introducer = 0;
	va_list args;

	va_start(args, str);

	while (*str) {
		switch (introducer) {
			case 0: {
				switch (*str) {
					case '%': {
						introducer = 1;
						str++;
						continue;
					}
					default:
						write_char(0, *str);
						introducer = 0;
						str++;
						break;
				}
				break;
			}
			case 1: {
				switch (*str) {
					case 'c':
					case 'C':
						write_char(0, va_arg(args, int));
						break;
					case 's':
					case 'S':
						write_line(0, va_arg(args, const char *));
						break;
					case 'd':
					case 'D':
						write_int(va_arg(args, int));
						break;
					case 'x':
					case 'X':
						write_hex(va_arg(args, int));
						break;
					default:
						write_char(0, *str);
						break;
				}
				introducer = 0;
				str++;
				break;
			}
		}
		va_end(args);
	}
}
