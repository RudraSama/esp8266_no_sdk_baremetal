/*
 * file      : uart_registers.h
 * Author    : Lucky Bairagi (luckybairagi96@gmail.com)
 * Reference : ESP8266 RTOS SDK
 */

#ifndef UART_REGISTERS_H_
#define UART_REGISTERS_H_


/*
 * UART_0 Reg - 0x60000000
 * UART_1 Reg - 0x60000F00
 */
#define UART_BASE(i)    0x60000000 + (i * 0xF00)

#define UART_RAW_INT(i) (UART_BASE(i) + 0x4)
#define UART_ST_INT(i)  (UART_BASE(i) + 0x8)
#define UART_INT_EN(i)  (UART_BASE(i) + 0xC)
#define UART_INT_CLR(i) (UART_BASE(i) + 0x10)
/* Same Bit mapping for -
 * UART_RAW_INT UART_ST_INT UART_INT_EN UART_CLR_INT
 */
#define RX_FULL_INT             (1 << 0)
#define TX_FULL_INT             (1 << 1)
#define PARITY_ERR_INT          (1 << 2)
#define FRAME_ERR_INT           (1 << 3)
#define RX_FIFO_OVFLOW_INT      (1 << 4)
#define DSR_CHNG_INT            (1 << 5)
#define CTS_CHNG_INT            (1 << 6)
#define BRK_DETC_INT            (1 << 7)

#define UART_CLKDIV(i)          (UART_BASE(i) + 0x14)
#define UART_CLKDIV_MASK        0x000FFFFF

#define UART_AUTOBAUD(i)        (UART_BASE(i) + 0x18)
#define EN_AUTOBAUD             (1 << 0)

#define UART_STATUS(i)          (UART_BASE(i) + 0x1C)
#define RX_FIFO_CNT             0x000000FF
#define RX_FIFO_CNT_S           0
#define DSR_STATE               1
#define DSR_STATE_S             13
#define CTS_STATE               1
#define CTS_STATE_S             14
#define RXD_STATE               1
#define RXD_STATE_S             15
#define TX_FIFO_CNT             0x000000FF
#define TX_FIFO_CNT_S           16
#define DTR_STATE               1
#define DTR_STATE_S             29
#define RTS_HW_STATE            1
#define RTS_HW_STATE_S          30
#define TXD_STATE               1
#define TXD_STATE_S             31

#define UART_CONFIG0(i)         (UART_BASE(i) + 0x20)
#define PARITY_TYPE             1
#define PARITY_TYPE_S           0
#define PARITY_EN               1
#define PARITY_EN_S             1
#define WORD_LEN                0x00000003
#define WORD_LEN_S              2
#define STOP_BIT                0x00000003
#define STOP_BIT_S              4
#define SW_RTS                  1
#define SW_RTS_S                6
#define SW_DTR                  1
#define SW_DTR_S                7
#define TX_BRK                  1
#define TX_BRK_S                8
#define UART_IRDA_DPLX          1
#define UART_IRDA_DPLX_S        9
#define UART_IRDA_TX_EN         1
#define UART_IRDA_TX_EN_S       10
#define UART_IRDA_WCTL          1
#define UART_IRDA_WCTL_S        11
#define UART_IRDA_TX_INV        1
#define UART_IRDA_TX_INV_S      12
#define UART_IRDA_RX_INV        1
#define UART_IRDA_RX_INV_S      13
#define UART_LOOPBACK           1
#define UART_LOOPBACK_S         14
#define AUTO_HW_FLOW_CNTRL_EN   1
#define AUTO_HW_FLOW_CNTRL_EN_S 15
#define UART_IRDA_EN            1
#define UART_IRDA_EN_S          16
#define RST_RX_FIFO_BUF         1
#define RST_TX_FIFO_BUF_S       18
#define RXD_INV                 1
#define RXD_INV_S               19
#define CTS_INV                 1
#define CTS_INV_S               20
#define TXD_INV                 1
#define TXD_INV_S               21
#define RTX_INV                 1
#define RTX_INV_S               22
#define DTR_INV                 1
#define DTR_INV_S               23

#define UART_CONFIG1(i)         (UART_BASE(i) + 0x24)
#define RX_FIFO_FULL_THRHD      0x7F
#define RX_FIFO_FULL_THRHD_S    0
#define TX_FIFO_EMPTY_THRHD     0x7F
#define TX_FIFO_EMPTY_THRHD_S   8
#define RX_FLOW_THRHD           0x7F
#define RX_FLOW_THRHD_S         16
#define RX_FLOW_EN              1
#define RX_FLOW_EN_S            23
#define RX_TOUT_THRHD           0x7F
#define RX_TOUT_THRHD_S         24

#define UART_LOWPULSE(i)        (UART_BASE(i) + 0x28)
#define UART_LOWPULSE_MASK      0x000FFFFF
#define UART_HIGHPULSE(i)       (UART_BASE(i) + 0x2C)
#define UART_HIGHULSE_MASK      0x000FFFFF
#define UART_PULSE_NUM(i)       (UART_BASE(i) + 0x30)
#define UART_PULSE_NUM_MASK     0x0003FF

#define UART_DATE(i)            (UART_BASE(i) + 0x78)
#define UART_ID(i)              (UART_BASE(i) + 0x7C)

typedef union {
	volatile struct {
		uint32_t parity_type : 1;
		uint32_t parity_en   : 1;
		uint32_t word_len    : 2;
		uint32_t stop_bit    : 2;
		/* Bits which are not useful for right now */
		uint32_t other : 26;
	};
	volatile uint32_t val;
} uart_config0_t;


#endif
