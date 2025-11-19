/*
 * file      : timer.h
 */


#ifndef TIMER_H_
#define TIMER_H_

#include <response.h>
#include <stdint.h>

typedef enum {
	TIMER_CLKDIV_1 = 0,
	TIMER_CLKDIV_16 = 4,
	TIMER_CLKDIV_256 = 8  // Or 3
} timer_clkdiv_t;

typedef enum {
	TIMER_EDGE = 0,
	TIMER_LEVEL = 1
} timer_int_type_t;

typedef struct {
	timer_clkdiv_t clkdiv;
	timer_int_type_t int_type;
	uint32_t autoload;
} timer_init_t;


/* @breif Initializing timer.
 * @param uint32_t ms
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t timer_init(timer_init_t timer_init, uint32_t ms);

/* @breif Set Clock Divisor.
 * @param timer_clkdiv_t clkdiv
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t timer_set_clkdiv(timer_clkdiv_t clkdiv);

/* @breif Enable/Disable Autoload feature in Timer1.
 * @param uint32_t bool
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t timer_autoload(uint32_t bool);

/* @breif Load Timer1.
 * @param uint32_t value
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t timer_load(uint32_t value);

/* @breif Set Timer1 interrupt Type.
 * @param timer_int_type_t int_type
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t timer_set_int_type(timer_int_type_t int_type);

/* @breif Enable/Disable Timer1.
 * @param uint32_t bool
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t timer_enable(uint32_t bool);

/* @breif Clear Timer1 Interrupt.
 * @param void
 * @return
 *      - response_t OK = 1, FAILED = 0
 */
response_t timer_clr_int(void);

/* @breif Check if Timer1 counter is zero.
 * @param void
 * @return
 *      - uint32_t, 1 - Zero, 0 - Not Zero
 */
uint32_t timer_is_count_zero(void);

/* @breif Get current CLKDIV.
 * @param void
 * @return
 *      - uint32_t
 */
uint32_t timer_get_clkdiv(void);

#endif
