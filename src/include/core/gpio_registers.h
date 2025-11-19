/*
 * file      : gpio_registers.h
 * Reference : ESP8266 RTOS SDK
 */

#ifndef GPIO_REGISTERS_H_
#define GPIO_REGISTERS_H_

#include <stdint.h>

#define GPIO_BASE 0x60000300

// GPIO Input Output Configuration
#define GPIO_OUT_W1TS    (GPIO_BASE + 0x4)
#define GPIO_OUT_W1TC    (GPIO_BASE + 0x8)
#define GPIO_ENABLE_W1TS (GPIO_BASE + 0x10)
#define GPIO_ENABLE_W1TC (GPIO_BASE + 0x14)
#define GPIO_IN          (GPIO_BASE + 0x18)

// GPIO Interrupt Configuration
// Here base address is same as GPIO_BASE
#define GPIO_STATUS      (GPIO_BASE + 0x1C)
#define GPIO_STATUS_W1TS (GPIO_BASE + 0x20)
#define GPIO_STATUS_W1TC (GPIO_BASE + 0x24)

// Individual GPIN Configuration
#define GPIO_PIN0                  (GPIO_BASE + 0x28)
#define GPIO_PIN0_CONFIG           0x00000003
#define GPIO_PIN0_CONFIG_S         11
#define GPIO_PIN0_WAKEUP_ENABLE    BIT10
#define GPIO_PIN0_WAKEUP_ENABLE_S  10
#define GPIO_PIN0_INT_TYPE         0x00000007
#define GPIO_PIN0_INT_TYPE_S       7
#define GPIO_PIN0_DRIVER           BIT2
#define GPIO_PIN0_DRIVER_S         2
#define GPIO_PIN0_SOURCE           BIT0
#define GPIO_PIN0_SOURCE_S         0

#define GPIO_PIN1                  (GPIO_BASE + 0x2c)
#define GPIO_PIN1_CONFIG           0x00000003
#define GPIO_PIN1_CONFIG_S         11
#define GPIO_PIN1_WAKEUP_ENABLE    BIT10
#define GPIO_PIN1_WAKEUP_ENABLE_S  10
#define GPIO_PIN1_INT_TYPE         0x00000007
#define GPIO_PIN1_INT_TYPE_S       7
#define GPIO_PIN1_DRIVER           BIT2
#define GPIO_PIN1_DRIVER_S         2
#define GPIO_PIN1_SOURCE           BIT0
#define GPIO_PIN1_SOURCE_S         0

#define GPIO_PIN2                  (GPIO_BASE + 0x30)
#define GPIO_PIN2_CONFIG           0x00000003
#define GPIO_PIN2_CONFIG_S         11
#define GPIO_PIN2_WAKEUP_ENABLE    BIT10
#define GPIO_PIN2_WAKEUP_ENABLE_S  10
#define GPIO_PIN2_INT_TYPE         0x00000007
#define GPIO_PIN2_INT_TYPE_S       7
#define GPIO_PIN2_DRIVER           BIT2
#define GPIO_PIN2_DRIVER_S         2
#define GPIO_PIN2_SOURCE           BIT0
#define GPIO_PIN2_SOURCE_S         0

#define GPIO_PIN3                  (GPIO_BASE + 0x34)
#define GPIO_PIN3_CONFIG           0x00000003
#define GPIO_PIN3_CONFIG_S         11
#define GPIO_PIN3_WAKEUP_ENABLE    BIT10
#define GPIO_PIN3_WAKEUP_ENABLE_S  10
#define GPIO_PIN3_INT_TYPE         0x00000007
#define GPIO_PIN3_INT_TYPE_S       7
#define GPIO_PIN3_DRIVER           BIT2
#define GPIO_PIN3_DRIVER_S         2
#define GPIO_PIN3_SOURCE           BIT0
#define GPIO_PIN3_SOURCE_S         0

#define GPIO_PIN4                  (GPIO_BASE + 0x38)
#define GPIO_PIN4_CONFIG           0x00000003
#define GPIO_PIN4_CONFIG_S         11
#define GPIO_PIN4_WAKEUP_ENABLE    BIT10
#define GPIO_PIN4_WAKEUP_ENABLE_S  10
#define GPIO_PIN4_INT_TYPE         0x00000007
#define GPIO_PIN4_INT_TYPE_S       7
#define GPIO_PIN4_DRIVER           BIT2
#define GPIO_PIN4_DRIVER_S         2
#define GPIO_PIN4_SOURCE           BIT0
#define GPIO_PIN4_SOURCE_S         0

#define GPIO_PIN5                  (GPIO_BASE + 0x3c)
#define GPIO_PIN5_CONFIG           0x00000003
#define GPIO_PIN5_CONFIG_S         11
#define GPIO_PIN5_WAKEUP_ENABLE    BIT10
#define GPIO_PIN5_WAKEUP_ENABLE_S  10
#define GPIO_PIN5_INT_TYPE         0x00000007
#define GPIO_PIN5_INT_TYPE_S       7
#define GPIO_PIN5_DRIVER           BIT2
#define GPIO_PIN5_DRIVER_S         2
#define GPIO_PIN5_SOURCE           BIT0
#define GPIO_PIN5_SOURCE_S         0

#define GPIO_PIN6                  (GPIO_BASE + 0x40)
#define GPIO_PIN6_CONFIG           0x00000003
#define GPIO_PIN6_CONFIG_S         11
#define GPIO_PIN6_WAKEUP_ENABLE    BIT10
#define GPIO_PIN6_WAKEUP_ENABLE_S  10
#define GPIO_PIN6_INT_TYPE         0x00000007
#define GPIO_PIN6_INT_TYPE_S       7
#define GPIO_PIN6_DRIVER           BIT2
#define GPIO_PIN6_DRIVER_S         2
#define GPIO_PIN6_SOURCE           BIT0
#define GPIO_PIN6_SOURCE_S         0

#define GPIO_PIN7                  (GPIO_BASE + 0x44)
#define GPIO_PIN7_CONFIG           0x00000003
#define GPIO_PIN7_CONFIG_S         11
#define GPIO_PIN7_WAKEUP_ENABLE    BIT10
#define GPIO_PIN7_WAKEUP_ENABLE_S  10
#define GPIO_PIN7_INT_TYPE         0x00000007
#define GPIO_PIN7_INT_TYPE_S       7
#define GPIO_PIN7_DRIVER           BIT2
#define GPIO_PIN7_DRIVER_S         2
#define GPIO_PIN7_SOURCE           BIT0
#define GPIO_PIN7_SOURCE_S         0

#define GPIO_PIN8                  (GPIO_BASE + 0x48)
#define GPIO_PIN8_CONFIG           0x00000003
#define GPIO_PIN8_CONFIG_S         11
#define GPIO_PIN8_WAKEUP_ENABLE    BIT10
#define GPIO_PIN8_WAKEUP_ENABLE_S  10
#define GPIO_PIN8_INT_TYPE         0x00000007
#define GPIO_PIN8_INT_TYPE_S       7
#define GPIO_PIN8_DRIVER           BIT2
#define GPIO_PIN8_DRIVER_S         2
#define GPIO_PIN8_SOURCE           BIT0
#define GPIO_PIN8_SOURCE_S         0

#define GPIO_PIN9                  (GPIO_BASE + 0x4c)
#define GPIO_PIN9_CONFIG           0x00000003
#define GPIO_PIN9_CONFIG_S         11
#define GPIO_PIN9_WAKEUP_ENABLE    BIT10
#define GPIO_PIN9_WAKEUP_ENABLE_S  10
#define GPIO_PIN9_INT_TYPE         0x00000007
#define GPIO_PIN9_INT_TYPE_S       7
#define GPIO_PIN9_DRIVER           BIT2
#define GPIO_PIN9_DRIVER_S         2
#define GPIO_PIN9_SOURCE           BIT0
#define GPIO_PIN9_SOURCE_S         0

#define GPIO_PIN10                 (GPIO_BASE + 0x50)
#define GPIO_PIN10_CONFIG          0x00000003
#define GPIO_PIN10_CONFIG_S        11
#define GPIO_PIN10_WAKEUP_ENABLE   BIT10
#define GPIO_PIN10_WAKEUP_ENABLE_S 10
#define GPIO_PIN10_INT_TYPE        0x00000007
#define GPIO_PIN10_INT_TYPE_S      7
#define GPIO_PIN10_DRIVER          BIT2
#define GPIO_PIN10_DRIVER_S        2
#define GPIO_PIN10_SOURCE          BIT0
#define GPIO_PIN10_SOURCE_S        0

#define GPIO_PIN11                 (GPIO_BASE + 0x54)
#define GPIO_PIN11_CONFIG          0x00000003
#define GPIO_PIN11_CONFIG_S        11
#define GPIO_PIN11_WAKEUP_ENABLE   BIT10
#define GPIO_PIN11_WAKEUP_ENABLE_S 10
#define GPIO_PIN11_INT_TYPE        0x00000007
#define GPIO_PIN11_INT_TYPE_S      7
#define GPIO_PIN11_DRIVER          BIT2
#define GPIO_PIN11_DRIVER_S        2
#define GPIO_PIN11_SOURCE          BIT0
#define GPIO_PIN11_SOURCE_S        0

#define GPIO_PIN12                 (GPIO_BASE + 0x58)
#define GPIO_PIN12_CONFIG          0x00000003
#define GPIO_PIN12_CONFIG_S        11
#define GPIO_PIN12_WAKEUP_ENABLE   BIT10
#define GPIO_PIN12_WAKEUP_ENABLE_S 10
#define GPIO_PIN12_INT_TYPE        0x00000007
#define GPIO_PIN12_INT_TYPE_S      7
#define GPIO_PIN12_DRIVER          BIT2
#define GPIO_PIN12_DRIVER_S        2
#define GPIO_PIN12_SOURCE          BIT0
#define GPIO_PIN12_SOURCE_S        0

#define GPIO_PIN13                 (GPIO_BASE + 0x5c)
#define GPIO_PIN13_CONFIG          0x00000003
#define GPIO_PIN13_CONFIG_S        11
#define GPIO_PIN13_WAKEUP_ENABLE   BIT10
#define GPIO_PIN13_WAKEUP_ENABLE_S 10
#define GPIO_PIN13_INT_TYPE        0x00000007
#define GPIO_PIN13_INT_TYPE_S      7
#define GPIO_PIN13_DRIVER          BIT2
#define GPIO_PIN13_DRIVER_S        2
#define GPIO_PIN13_SOURCE          BIT0
#define GPIO_PIN13_SOURCE_S        0

#define GPIO_PIN14                 (GPIO_BASE + 0x60)
#define GPIO_PIN14_CONFIG          0x00000003
#define GPIO_PIN14_CONFIG_S        11
#define GPIO_PIN14_WAKEUP_ENABLE   BIT10
#define GPIO_PIN14_WAKEUP_ENABLE_S 10
#define GPIO_PIN14_INT_TYPE        0x00000007
#define GPIO_PIN14_INT_TYPE_S      7
#define GPIO_PIN14_DRIVER          BIT2
#define GPIO_PIN14_DRIVER_S        2
#define GPIO_PIN14_SOURCE          BIT0
#define GPIO_PIN14_SOURCE_S        0

#define GPIO_PIN15                 (GPIO_BASE + 0x64)
#define GPIO_PIN15_CONFIG          0x00000003
#define GPIO_PIN15_CONFIG_S        11
#define GPIO_PIN15_WAKEUP_ENABLE   BIT10
#define GPIO_PIN15_WAKEUP_ENABLE_S 10
#define GPIO_PIN15_INT_TYPE        0x00000007
#define GPIO_PIN15_INT_TYPE_S      7
#define GPIO_PIN15_DRIVER          BIT2
#define GPIO_PIN15_DRIVER_S        2
#define GPIO_PIN15_SOURCE          BIT0
#define GPIO_PIN15_SOURCE_S        0

#define PIN_NUM_TO_REG(x)    \
	(x == 0)    ? GPIO_PIN0  \
	: (x == 1)  ? GPIO_PIN1  \
	: (x == 2)  ? GPIO_PIN2  \
	: (x == 3)  ? GPIO_PIN3  \
	: (x == 4)  ? GPIO_PIN4  \
	: (x == 5)  ? GPIO_PIN5  \
	: (x == 6)  ? GPIO_PIN6  \
	: (x == 7)  ? GPIO_PIN7  \
	: (x == 8)  ? GPIO_PIN8  \
	: (x == 9)  ? GPIO_PIN9  \
	: (x == 10) ? GPIO_PIN10 \
	: (x == 11) ? GPIO_PIN11 \
	: (x == 12) ? GPIO_PIN12 \
	: (x == 13) ? GPIO_PIN13 \
	: (x == 14) ? GPIO_PIN14 \
	            : GPIO_PIN15

typedef union {
	volatile struct {
		uint32_t source   : 1;
		uint32_t rsv1     : 1;
		uint32_t driver   : 1;
		uint32_t rsv2     : 4;
		uint32_t int_type : 3;
		uint32_t wake_en  : 1;
		uint32_t config   : 2;
		uint32_t resv3    : 19;
	};
	volatile uint32_t val;
} gpio_reg_pin_t;

// Enabling GPIO OUTPUT
#define ENABLE_GPIO_OUTPUT(gpio_pin) \
	WRITE_TO_REG(GPIO_ENABLE_W1TS,   \
	             READ_FROM_REG(GPIO_ENABLE_W1TS) | (1 << gpio_num))

// Disabling GPIO OUTPUT
#define DISABLE_GPIO_OUTPUT(gpio_pin) \
	WRITE_TO_REG(GPIO_ENABLE_W1TC,    \
	             READ_FROM_REG(GPIO_ENABLE_W1TC) | (1 << gpio_num))

// Set GPIO Level HIGH
#define GPIO_SET_LEVEL_HIGH(gpio_pin) \
	WRITE_TO_REG(GPIO_OUT_W1TS, READ_FROM_REG(GPIO_OUT_W1TS) | (1 << gpio_num));

// Set GPIO Level HIGH
#define GPIO_SET_LEVEL_LOW(gpio_pin) \
	WRITE_TO_REG(GPIO_OUT_W1TC, READ_FROM_REG(GPIO_OUT_W1TC) | (1 << gpio_num));


#endif
