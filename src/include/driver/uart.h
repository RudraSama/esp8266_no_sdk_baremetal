/*
 * file      : uart.h
 */

#ifndef UART_H_
#define UART_H_

#include <response.h>
#include <stdint.h>

/*
 * Common Baud rates
 *
 *	74880,
 *	300,
 *	1200,
 *	2400,
 *	4800,
 *	9600,
 *	19200,
 *	38400,
 *	57600,
 *	115200
 */

typedef enum {
	WORD_5_BTIS = 0x0,
	WORD_6_BITS = 0x01,
	WORD_7_BITS = 0x02,
	WORD_8_BITS = 0x03
} uart_word_len_t;

typedef enum {
	STOP_1_BIT = 0x01,
	STOP_1_5_BIT = 0x02,
	STOP_2_BIT = 0x03
} uart_stop_bits_t;


/* @breif Initiazling UART with CLK DIVISOR
 * @param uint32_t uart, uint32_t baud_rate, uint32_t word_len, uint32_t
 * stop_bit
 * @return
 *      - response_t. OK - 1, ERROR - 0
 */
response_t uart_init(uint32_t uart, uint32_t baud_rate, uint32_t word_len,
                     uint32_t stop_bit);

/* @breif Setting baudrate for uart
 * @param uint32_t uart, uint32_t baud_rate
 * @return
 *      - response_t. OK - 1, ERROR - 0
 */
response_t uart_set_baud(uint32_t uart, uint32_t baud_rate);

/* @breif Checking if TX FIFO full
 * @param uint32_t uart
 * @return
 *      - uint32_t. 0 - False, 1 - True
 */
uint32_t is_tx_fifo_full(uint32_t uart);

/* @breif Writing single Char to Buffer
 * @param char c
 * @return
 *      - void
 */
void write_char(uint32_t uart, char c);

/* @breif Writing each char of string to Buffer
 * @param const char *c
 * @return
 *      - void
 */
void write_line(uint32_t uart, const char *str);

/* @breif Reading char from buffer
 * @param uint32_t uart
 * @return
 *      - char
 */
char read_char(uint32_t uart);

#endif
