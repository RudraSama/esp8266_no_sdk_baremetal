/*
 * file      : rtc_registers.h
 * Reference : ESP8266 RTOS SDK
 */

#ifndef RTC_REGISTERS_H_
#define RTC_REGISTERS_H_

#include <stdint.h>

#define RTC_BASE 0x60000700

// Function Mask
#define PAD_XPD_DCDC_CONF_MASK 0x43

#define RTC_GPIO_OUT           (RTC_BASE + 0x068)
#define RTC_GPIO_ENABLE        (RTC_BASE + 0x074)
#define RTC_GPIO_IN_DATA       (RTC_BASE + 0x08C)
#define RTC_GPIO_CONF          (RTC_BASE + 0x090)
#define PAD_XPD_DCDC_CONF      (RTC_BASE + 0x0A0)

typedef union {
	volatile struct {
		uint32_t function       : 2;
		uint32_t rsv1           : 1;
		uint32_t pulldown       : 1;
		uint32_t rsv2           : 1;
		uint32_t pulldown_sleep : 1;
		uint32_t function2      : 1;
	};
	volatile uint32_t val;
} rtc_pin_t;

// Clearing XPD_DCDC Function
#define CLEAR_XPD_DCDC_FUNC(xpd_dcdc) \
	WRITE_TO_REG(xpd_dcdc, READ_FROM_REG(xpd_dcdc) & (~PAD_XPD_DCDC_CONF_MASK))

// Sets XPD_DCDC Function
#define SET_XPD_DCDC_FUNC(xpd_dcdc, func) \
	WRITE_TO_REG(xpd_dcdc, READ_FROM_REG(xpd_dcdc) | func)

// Enable RTC
#define ENABLE_RTC_GPIO_OUTPUT() \
	WRITE_TO_REG(RTC_GPIO_ENABLE, READ_FROM_REG(RTC_GPIO_ENABLE) | (0x1))

// Disable RTC
#define DISABLE_RTC_GPIO_OUTPUT() \
	WRITE_TO_REG(RTC_GPIO_ENABLE, READ_FROM_REG(RTC_GPIO_ENABLE) & (~0x1))

// Conf Mux Set
// Bit Field is not completely unknown, so we just use BIT0
#define RTC_CONF_FUNC(func) \
	WRITE_TO_REG(RTC_GPIO_CONF, READ_FROM_REG(RTC_GPIO_CONF) | (~func))

// Set RTC High when used as GPIO
#define RTC_GPIO_SET_LEVEL_HIGH() \
	WRITE_TO_REG(RTC_GPIO_OUT, READ_FROM_REG(RTC_GPIO_OUT) | (0x1))

// Set RTC LOW when used as GPIO
#define RTC_GPIO_SET_LEVEL_LOW() \
	WRITE_TO_REG(RTC_GPIO_OUT, READ_FROM_REG(RTC_GPIO_OUT) & (~0x1))

#endif
