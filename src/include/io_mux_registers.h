/*
 * file      : io_mux_registers.h
 * Author    : Lucky Bairagi (luckybairagi96@gmail.com)
 * Reference : ESP8266 RTOS SDK
 */


#ifndef IO_MUX_REGISTERS_H_
#define IO_MUX_REGISTERS_H_

#include <stdint.h>

// List of all IOMUX Registers
#define IOMUX_BASE 0x60000800

// Function Mask
#define IOMUX_MASK        0x130

#define IOMUX_SPI         (IOMUX_BASE + 0x00)

#define IOMUX_GPIO12      (IOMUX_BASE + 0x04)
#define FUNC_MTDI         0
#define FUNC_I2SI_DATA    0x10
#define FUNC_HSPIQ_MISO   0x20
#define FUNC_GPIO12       0x30
#define FUNC_UART0_DTR    0x100

#define IOMUX_GPIO13      (IOMUX_BASE + 0x08)
#define FUNC_MTCK         0
#define FUNC_I2SI_BCK     0x10
#define FUNC_HSPID_MOSI   0x20
#define FUNC_GPIO13       0x30
#define FUNC_UART0_CTS    0x100

#define IOMUX_GPIO14      (IOMUX_BASE + 0x0C)
#define FUNC_MTMS         0
#define FUNC_I2SI_WS      0x10
#define FUNC_HSPI_CLK     0x20
#define FUNC_GPIO14       0x30
#define FUNC_UART0_DSR    0x100

#define IOMUX_GPIO15      (IOMUX_BASE + 0x10)
#define FUNC_MTDO         0
#define FUNC_I2SO_BCK     0x10
#define FUNC_HSPI_CS0     0x20
#define FUNC_GPIO15       0x30
#define FUNC_U0RTS        0x100
#define FUNC_UART0_RTS    0x100

#define IOMUX_GPIO3       (IOMUX_BASE + 0x14)
#define FUNC_U0RXD        0
#define FUNC_I2SO_DATA    0x10
#define FUNC_GPIO3        0x30
#define FUNC_CLK_XTAL_BK  0x100

#define IOMUX_GPIO1       (IOMUX_BASE + 0x18)
#define FUNC_U0TXD        0
#define FUNC_SPICS1       0x10
#define FUNC_GPIO1        0x30
#define FUNC_CLK_RTC_BK   0x40

#define IOMUX_GPIO6       (IOMUX_BASE + 0x1C)
#define FUNC_SDCLK        0
#define FUNC_SPICLK       0x10
#define FUNC_GPIO6        0x30
#define UART1_CTS         0x100

#define IOMUX_GPIO7       (IOMUX_BASE + 0x20)
#define FUNC_SDDATA0      0
#define FUNC_SPIQ_MISO    0x10
#define FUNC_GPIO7        0x30
#define FUNC_U1TXD        0x100
#define FUNC_UART1_TXD    0x100

#define IOMUX_GPIO8       (IOMUX_BASE + 0x24)
#define FUNC_SDDATA1      0
#define FUNC_SPID_MOSI    0x10
#define FUNC_GPIO8        0x30
#define FUNC_U1RXD        0x100
#define FUNC_UART1_RXD    0x100

#define IOMUX_GPIO9       (IOMUX_BASE + 0x28)
#define FUNC_SDDATA2      0
#define FUNC_SPIHD        0x10
#define FUNC_GPIO9        0x30
#define UFNC_HSPIHD       0x100

#define IOMUX_GPIO10      (IOMUX_BASE + 0x2c)
#define FUNC_SDDATA3      0
#define FUNC_SPIWP        0x10
#define FUNC_GPIO10       0x30
#define FUNC_HSPIWP       0x100

#define IOMUX_GPIO11      (IOMUX_BASE + 0x30)
#define FUNC_SDCMD        0
#define FUNC_SPICS0       0x10
#define FUNC_GPIO11       0x30
#define U1RTS             0x100
#define UART1_RTS         0x100

#define IOMUX_GPIO0       (IOMUX_BASE + 0x34)
#define FUNC_GPIO0        0
#define FUNC_SPICS2       0x10
#define FUNC_CLK_OUT      0x100

#define IOMUX_GPIO2       (IOMUX_BASE + 0x38)
#define FUNC_GPIO2        0
#define FUNC_I2SO_WS      0x10
#define FUNC_U1TXD_BK     0x20
#define FUNC_UART1_TXD_BK 0x20
#define FUNC_U0TXD_BK     0x100
#define FUNC_UART0_TXD_BK 0x100

#define IOMUX_GPIO4       (IOMUX_BASE + 0x3C)
#define FUNC_GPIO4        0
#define FUNC_CLK_XTAL     0x10

#define IOMUX_GPIO5       (IOMUX_BASE + 0x40)
#define FUNC_GPIO5        0
#define FUNC_CLK_RTC      0x10

// PIN NUMBER TO IOMUX_GPION
#define PIN_NUM_TO_IOMUX(x)    \
	(x == 0)    ? IOMUX_GPIO0  \
	: (x == 1)  ? IOMUX_GPIO1  \
	: (x == 2)  ? IOMUX_GPIO2  \
	: (x == 3)  ? IOMUX_GPIO3  \
	: (x == 4)  ? IOMUX_GPIO4  \
	: (x == 5)  ? IOMUX_GPIO5  \
	: (x == 6)  ? IOMUX_GPIO6  \
	: (x == 7)  ? IOMUX_GPIO7  \
	: (x == 8)  ? IOMUX_GPIO8  \
	: (x == 9)  ? IOMUX_GPIO9  \
	: (x == 10) ? IOMUX_GPIO10 \
	: (x == 11) ? IOMUX_GPIO11 \
	: (x == 12) ? IOMUX_GPIO12 \
	: (x == 13) ? IOMUX_GPIO13 \
	: (x == 14) ? IOMUX_GPIO14 \
	            : IOMUX_GPIO15

typedef union {
	volatile struct {
		uint32_t oe             : 1;
		uint32_t sleep_oe       : 1;
		uint32_t pulldown_sleep : 1;
		uint32_t pullup_sleep   : 1;
		uint32_t function1      : 1;
		uint32_t function2      : 1;
		uint32_t pulldown       : 1;
		uint32_t pullup         : 1;
		uint32_t function3      : 1;
		uint32_t rsv            : 23;
	};
	volatile uint32_t val;
} gpio_mux_pin_t;

// Clears IO_MUX FUNCTION BITS
#define CLEAR_GPIO_MUX_FUNC(iomux) \
	WRITE_TO_REG(iomux, READ_FROM_REG(iomux) & (~IOMUX_MASK))

// Sets GPIO FUNCTION
#define SET_GPIO_FUNC(iomux, func) \
	WRITE_TO_REG(iomux, READ_FROM_REG(iomux) | func)

#endif
