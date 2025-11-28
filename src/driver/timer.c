/*
 * file      : timer.c
 */

#include <core/isr.h>
#include <core/reg_rw.h>
#include <core/system.h>
#include <core/timer_register.h>
#include <driver/timer.h>
#include <response.h>


response_t timer_init(timer_init_t t_init) {
	timer_set_clkdiv(t_init.clkdiv);
	timer_autoload(t_init.autoload);
	timer_set_int_type(t_init.int_type);

	uint32_t load_value =
	    (APB_CLK / timer_get_clkdiv()) * t_init.time_ms / 1000;
	timer_load(load_value);

	return OK;
}

response_t timer_set_clkdiv(timer_clkdiv_t clkdiv) {
	uint32_t frc1_ctrl = READ_FROM_REG(FRC1_CTRL);
	frc1_ctrl = frc1_ctrl & ~(1UL << 3) & ~(1UL << 2);
	frc1_ctrl = frc1_ctrl | clkdiv;
	WRITE_TO_REG(FRC1_CTRL, frc1_ctrl);
	return OK;
}

response_t timer_autoload(uint32_t bool) {
	uint32_t frc1_ctrl = READ_FROM_REG(FRC1_CTRL);
	frc1_ctrl = frc1_ctrl & ~(1UL << 6);
	if (bool) {
		frc1_ctrl = frc1_ctrl | (1UL << 6);
	}
	WRITE_TO_REG(FRC1_CTRL, frc1_ctrl);
	return OK;
}

response_t timer_load(uint32_t value) {
	uint32_t v = (value >= 0x007FFFFF) ? 0x007FFFFF : value;
	WRITE_TO_REG(FRC1, v);
	return OK;
}

response_t timer_set_int_type(timer_int_type_t int_type) {
	uint32_t frc1_ctrl = READ_FROM_REG(FRC1_CTRL);
	frc1_ctrl = frc1_ctrl & ~(1UL);
	frc1_ctrl = frc1_ctrl | int_type;
	WRITE_TO_REG(FRC1_CTRL, frc1_ctrl);

	if (int_type == TIMER_EDGE) {
		TM1_INT_EN();
		isr_unmask(1 << FRC_TIMER1_INUM);
	}
	return OK;
}

response_t timer_enable(uint32_t bool) {
	uint32_t en = (uint32_t)(1 << 7);
	if (bool) {
		WRITE_TO_REG(FRC1_CTRL, READ_FROM_REG(FRC1_CTRL) | en);
	} else {
		en = (uint32_t)~en;
		WRITE_TO_REG(FRC1_CTRL, READ_FROM_REG(FRC1_CTRL) & en);
	}
	return OK;
}

response_t timer_clr_int(void) {
	WRITE_TO_REG(FRC1_INT, 1);
	return OK;
}

uint32_t timer_is_count_zero(void) {
	uint32_t frc1_ctrl = READ_FROM_REG(FRC1_CTRL);
	if ((frc1_ctrl >> 8) & 1) {
		return 1;
	}
	return 0;
}

uint32_t timer_get_clkdiv(void) {
	uint32_t frc1_ctrl = READ_FROM_REG(FRC1_CTRL);
	if ((frc1_ctrl & TIMER_CLKDIV_16) == TIMER_CLKDIV_16) {
		return 16;
	} else if ((frc1_ctrl & TIMER_CLKDIV_256) == TIMER_CLKDIV_256) {
		return 256;
	}
	return 1;
}

response_t timer_isr_attach(isr_cb cb, void *arg) {
	isr_attach(1 << FRC_TIMER1_INUM, cb, arg);
	return OK;
}

response_t timer_isr_detach(void) {
	isr_detach(1 << FRC_TIMER1_INUM);
	return OK;
}
