/*
 * file      : utils.h
 * Author    : Lucky Bairagi (luckybairagi96@gmail.com)
 */

#ifndef UTILS_H_
#define UTILS_H_

/*
 * All helper funcitons which I am too lazy to properly implement are here.
 */

typedef void (*callback_t)(uint32_t, char);

/* @breif Converting integer into char and sending each byte to UART0.
 * @param uint32_t value, pointer to
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
void int_to_chars(uint32_t value, callback_t cb, uint32_t arg) {
	// max uint32_t value is 4294967295 which has 10 digits max.

	uint32_t count = 0;
	char arr[12];

	while (value) {
		uint32_t rem = value % 10;
		value = value / 10;
		arr[count] = '0' + rem;
		count++;
	}

	uint32_t i = 0;
	count--;
	while (i < count) {
		uint32_t temp = arr[i];
		arr[i] = arr[count];
		arr[count] = temp;
		i++;
		count--;
	}

	count = i + count + 1;
	i = 0;
	(*cb)(arg, '\n');
	while (i < count) {
		(*cb)(arg, arr[i]);
		i++;
	}
}

#endif
