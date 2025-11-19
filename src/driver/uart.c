/*
 * file      : uart.c
 */

#include <core/io_mux_registers.h>
#include <core/reg_rw.h>
#include <core/system.h>
#include <core/uart_registers.h>
#include <driver/uart.h>
#include <response.h>
#include <stdint.h>


response_t uart_init(uint32_t uart, uint32_t baud_rate, uint32_t word_len,
                     uint32_t stop_bit) {
	if (uart == 0) {
		CLEAR_GPIO_MUX_FUNC(IOMUX_GPIO1);
		SET_GPIO_FUNC(IOMUX_GPIO1, FUNC_U0TXD);
		CLEAR_GPIO_MUX_FUNC(IOMUX_GPIO3);
		SET_GPIO_FUNC(IOMUX_GPIO3, FUNC_U0RXD);
	} else if (uart == 1) {
		CLEAR_GPIO_MUX_FUNC(IOMUX_GPIO2);
		SET_GPIO_FUNC(IOMUX_GPIO2, FUNC_U1TXD_BK);
	}

	if (uart == 0 || uart == 1) {
		uart_config0_t uart_config0;
		uart_config0.val = READ_FROM_REG(UART_CONFIG0(uart));
		uart_config0.parity_type = 0;
		uart_config0.parity_en = 0;
		uart_config0.word_len = word_len;
		uart_config0.stop_bit = stop_bit;
		WRITE_TO_REG(UART_CONFIG0(uart), uart_config0.val);

		uart_set_baud(uart, baud_rate);
		// Small delay before actually using UART
		for (uint32_t i = 0; i < 80000; i++);
	}

	return OK;
}


response_t uart_set_baud(uint32_t uart, uint32_t baud_rate) {
	uint32_t clk_div = (uint32_t)(APB_CLK / (baud_rate));
	WRITE_TO_REG(UART_CLKDIV(uart), clk_div);
	return OK;
}

uint32_t is_tx_fifo_full(uint32_t uart) {
	uint32_t value =
	    (uint32_t)(READ_FROM_REG(UART_STATUS(uart)) >> TX_FIFO_CNT_S) &
	    TX_FIFO_CNT;

	if (value >= 0x7F) return 1;
	return 0;
}

uint32_t is_rx_fifo_empty(uint32_t uart) {
	uint32_t value =
	    (uint32_t)(READ_FROM_REG(UART_STATUS(uart)) >> RX_FIFO_CNT_S) &
	    RX_FIFO_CNT;

	if (value <= 0) return 1;
	return 0;
}

void write_char(uint32_t uart, char c) {
	while (is_tx_fifo_full(uart));
	WRITE_TO_REG(UART_BASE(uart), c);
}

void write_line(uint32_t uart, const char *str) {
	while (*str) {
		write_char(uart, *str);
		str++;
	}
}

char read_char(uint32_t uart) {
	if (is_rx_fifo_empty(uart)) {
		return -1;
	}
	char c = READ_FROM_REG(UART_BASE(uart));
	return c;
}
