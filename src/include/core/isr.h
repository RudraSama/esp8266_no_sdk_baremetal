/*
 * file     : isr.h
 */

#ifndef ISR_H_
#define ISR_H_

#include <stdint.h>

typedef void (*isr_cb)(void *);

typedef struct {
	isr_cb cb;
	void *arg;
} isr_t;

/* Interrupt Number in INTENABLE register */
#define SLC_INUM        1
#define SPI_INUM        2
#define GPIO_INUM       4
#define UART_INUM       5
#define MAX_INUM        6
#define SOFT_INUM       7
#define WDT_INUM        8
#define FRC_TIMER1_INUM 9
#define INTERRUPT_MAX   14

/* @breif Unmasking Interrupts so CPU can see them.
 * @param uint32_t inum
 * @return
 *
 */
void isr_unmask(uint32_t inum);

/* @breif Masking Interrupts so CPU cannot see them.
 * @param uint32_t inum
 * @return
 *
 */
void isr_mask(uint32_t inum);

/* @breif Handling ISR requests. Called by UserExceptionVector.
 * @param void
 * @return
 *
 */
void isr_handler(void);

/* @breif Attaching ISR for Interrupt.
 * @param uint32_t inum, isr_cb cb, void *arg
 * @return
 *
 */
void isr_attach(uint32_t inum, isr_cb cb, void *arg);

/* @breif Detaching ISR from Interrupt.
 * @param uint32_t inum, isr_cb cb, void *arg
 * @return
 *
 */
void isr_detach(uint32_t inum);
#endif
