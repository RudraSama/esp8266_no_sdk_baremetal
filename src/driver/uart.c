/*
 * file      : uart.c
 * Author    : Lucky Bairagi (luckybairagi96@gmail.com)
 */

#include <driver/uart.h>

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
	}

	return OK;
}


response_t uart_set_baud(uint32_t uart, uint32_t baud_rate) {
	uint32_t clk_div = (uint32_t)(CPU_CLK_52MHZ / (baud_rate));
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

void write_line(uint32_t uart, const char *line) {
	uint32_t i = 0;
	while (line[i]) {
		write_char(uart, line[i]);
		i++;
	}
	write_char(uart, '\n');
}

char read_char(uint32_t uart) {
	if (is_rx_fifo_empty(uart)) {
		return -1;
	}
	char c = READ_FROM_REG(UART_BASE(uart));
	return c;
}
