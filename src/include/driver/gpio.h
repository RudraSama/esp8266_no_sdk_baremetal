/*
 * file      : gpio.h
 * Reference : ESP8266 RTOS SDK
 */

#ifndef GPIO_H_
#define GPIO_H_



#include <response.h>
#include <stdint.h>


// GPIO PIN List
#define GPIO0  (1 << 0)
#define GPIO1  (1 << 1)
#define GPIO2  (1 << 2)
#define GPIO3  (1 << 3)
#define GPIO4  (1 << 4)
#define GPIO5  (1 << 5)
#define GPIO6  (1 << 6)
#define GPIO7  (1 << 7)
#define GPIO8  (1 << 8)
#define GPIO9  (1 << 9)
#define GPIO10 (1 << 10)
#define GPIO11 (1 << 11)
#define GPIO12 (1 << 12)
#define GPIO13 (1 << 13)
#define GPIO14 (1 << 14)
#define GPIO15 (1 << 15)

// Mapping GPIO to GPIO NUM
typedef enum {
	GPIO_NUM_0 = 0,
	GPIO_NUM_1 = 1,
	GPIO_NUM_2 = 2,
	GPIO_NUM_3 = 3,
	GPIO_NUM_4 = 4,
	GPIO_NUM_5 = 5,
	GPIO_NUM_6 = 6,
	GPIO_NUM_7 = 7,
	GPIO_NUM_8 = 8,
	GPIO_NUM_9 = 9,
	GPIO_NUM_10 = 10,
	GPIO_NUM_11 = 11,
	GPIO_NUM_12 = 12,
	GPIO_NUM_13 = 13,
	GPIO_NUM_14 = 14,
	GPIO_NUM_15 = 15,
	GPIO_NUM_16 = 16,
	GPIO_MAX = 17
} gpio_num_t;

// GPIO LEVEL Enum
// Whatever, greater than 1 is considered HIGH
typedef enum {
	LOW = 0,
	HIGH = 1
} gpio_level_t;


// Checks if valid GPIO PIN
#define IS_VALID_GPIO(gpio_num)                \
	if (gpio_num > GPIO_MAX || gpio_num < 0) { \
		return FAILED;                         \
	}

// Checks if RTC Pin
#define IS_RTC_PIN(gpio_num) (gpio_num == GPIO_NUM_16 ? 1 : 0)


/* @breif Reseting all pins to normal function.
 * @param void
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t reset_pins(void);


/* @breif Checking if valid GPIO
 * @param gpio_num_t gpio_num
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t check_gpio_pin(gpio_num_t gpio_num);

/* @breif Checking if valid RTC GPIO
 * @param gpio_num_t gpio_num
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t check_rtc_gpio_pin(gpio_num_t gpio_num);

/* @breif Enabling output of GPIO pin
 * @param gpio_num_t gpio_num
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t gpio_output_enable(gpio_num_t gpio_num);

/* @breif Disable output of GPIO pin
 * @param gpio_num_t gpio_num
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t gpio_output_disable(gpio_num_t gpio_num);

/* @breif Set GPIO level
 * @param gpio_num_t gpio_num, gpio_level_t level
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t gpio_set_level(gpio_num_t gpio_num, gpio_level_t level);

/* @breif Pullup enable. Pullup doesn't exist for RTC GPIO
 * @param gpio_num_t gpio_num
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t gpio_pullup_en(gpio_num_t gpio_num);

/* @breif Pullup Disable.
 * @param gpio_num_t gpio_num
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t gpio_pullup_dis(gpio_num_t gpio_num);

/* @breif Pulldown enable. Pullup doesn't exist for Normal GPIO
 * @param gpio_num_t gpio_num
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t gpio_pulldown_en(gpio_num_t gpio_num);

/* @breif Pulldown disable.
 * @param gpio_num_t gpio_num
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t gpio_pulldown_dis(gpio_num_t gpio_num);


#endif
