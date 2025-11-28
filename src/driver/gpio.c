/*
 * file      : gpio.c
 */


#include <core/gpio_register.h>
#include <core/io_mux_register.h>
#include <core/reg_rw.h>
#include <core/rtc_register.h>
#include <driver/gpio.h>
#include <response.h>


response_t reset_pins() {
	for (uint32_t i = 0; i < 16; i++) {
		CLEAR_GPIO_MUX_FUNC(PIN_NUM_TO_IOMUX(i));
		if (i != 0 && i != 2 && i != 4 && i != 5) {
			SET_GPIO_FUNC(PIN_NUM_TO_IOMUX(i), 0x30);
		}
		gpio_output_disable(i);
	}

	return OK;
}

response_t gpio_output_enable(gpio_num_t gpio_num) {
	IS_VALID_GPIO(gpio_num);

	if (IS_RTC_PIN(gpio_num)) {
		CLEAR_XPD_DCDC_FUNC(PAD_XPD_DCDC_CONF);
		SET_XPD_DCDC_FUNC(PAD_XPD_DCDC_CONF, 0x1);
		RTC_CONF_FUNC(0x1);
		ENABLE_RTC_GPIO_OUTPUT();
	} else {
		ENABLE_GPIO_OUTPUT(gpio_num);
	}

	return OK;
}

response_t gpio_output_disable(gpio_num_t gpio_num) {
	IS_VALID_GPIO(gpio_num);

	if (IS_RTC_PIN(gpio_num)) {
		CLEAR_XPD_DCDC_FUNC(PAD_XPD_DCDC_CONF);
		SET_XPD_DCDC_FUNC(PAD_XPD_DCDC_CONF, 0x1);
		RTC_CONF_FUNC(0x1);
		DISABLE_RTC_GPIO_OUTPUT();
	} else {
		DISABLE_GPIO_OUTPUT(gpio_num);
	}

	return OK;
}

response_t gpio_set_level(gpio_num_t gpio_num, gpio_level_t level) {
	IS_VALID_GPIO(gpio_num);

	if (IS_RTC_PIN(gpio_num)) {
		if (level) {
			RTC_GPIO_SET_LEVEL_HIGH();
		} else {
			RTC_GPIO_SET_LEVEL_LOW();
		}
	} else {
		if (level) {
			GPIO_SET_LEVEL_HIGH(gpio_num);
		} else {
			GPIO_SET_LEVEL_LOW(gpio_num);
		}
	}

	return OK;
}

gpio_level_t gpio_get_level(gpio_num_t gpio_num) {
	IS_VALID_GPIO(gpio_num);
	return GPIO_GET_LEVEL(gpio_num) ? HIGH : LOW;
}

response_t gpio_pullup_en(gpio_num_t gpio_num) {
	IS_VALID_GPIO(gpio_num);

	if (IS_RTC_PIN(gpio_num)) {
		return OK;
	}

	gpio_mux_pin_t gpio_mux;
	gpio_mux.val = READ_FROM_REG(PIN_NUM_TO_IOMUX(gpio_num));
	gpio_mux.pullup = 1;
	WRITE_TO_REG(PIN_NUM_TO_IOMUX(gpio_num), gpio_mux.val);

	return OK;
}

response_t gpio_pullup_dis(gpio_num_t gpio_num) {
	IS_VALID_GPIO(gpio_num);

	if (IS_RTC_PIN(gpio_num)) {
		return OK;
	}

	gpio_mux_pin_t gpio_mux;
	gpio_mux.val = READ_FROM_REG(PIN_NUM_TO_IOMUX(gpio_num));
	gpio_mux.pullup = 0;
	WRITE_TO_REG(PIN_NUM_TO_IOMUX(gpio_num), gpio_mux.val);

	return OK;
}

response_t gpio_pulldown_en(gpio_num_t gpio_num) {
	IS_VALID_GPIO(gpio_num);

	if (!IS_RTC_PIN(gpio_num)) {
		return OK;
	}

	rtc_pin_t rtc_pin;
	rtc_pin.val = READ_FROM_REG(PAD_XPD_DCDC_CONF);
	rtc_pin.pulldown = 1;
	WRITE_TO_REG(PAD_XPD_DCDC_CONF, rtc_pin.val);

	return OK;
}

response_t gpio_pulldown_dis(gpio_num_t gpio_num) {
	IS_VALID_GPIO(gpio_num);

	if (!IS_RTC_PIN(gpio_num)) {
		return OK;
	}

	rtc_pin_t rtc_pin;
	rtc_pin.val = READ_FROM_REG(PAD_XPD_DCDC_CONF);
	rtc_pin.pulldown = 0;
	WRITE_TO_REG(PAD_XPD_DCDC_CONF, rtc_pin.val);

	return OK;
}
