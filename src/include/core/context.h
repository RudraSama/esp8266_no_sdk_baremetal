/*
 * file      : context.h
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

// Copied directly from ESP8266 FREE RTOS

/*
Align a value up to nearest n-byte boundary, where n is a power of 2.
*/
#define ALIGNUP(n, val) (((val) + (n) - 1) & -(n))

/*
 * Offset for saving register context.
 * It is so that Exception return (RFE) expects registers in specific offsets.
 */

#define XT_STK_EXIT     0x00 /* (offset 0) exit point for dispatch */
#define XT_STK_PC       0x04 /* return address */
#define XT_STK_PS       0x08 /* at level 1 PS.EXCM is set here */
#define XT_STK_A0       0x0C
#define XT_STK_A1       0x10 /* stack ptr before interrupt */
#define XT_STK_A2       0x14
#define XT_STK_A3       0x18
#define XT_STK_A4       0x1C
#define XT_STK_A5       0x20
#define XT_STK_A6       0x24
#define XT_STK_A7       0x28
#define XT_STK_A8       0x2C
#define XT_STK_A9       0x30
#define XT_STK_A10      0x34
#define XT_STK_A11      0x38
#define XT_STK_A12      0x3C /* Call0 callee-save */
#define XT_STK_A13      0x40 /* Call0 callee-save */
#define XT_STK_A14      0x44 /* Call0 callee-save */
#define XT_STK_A15      0x48 /* Call0 callee-save */
#define XT_STK_SAR      0x4C
#define XT_STK_EXCCAUSE 0x50

#define XT_STK_EXCVADDR 0x54

#define XT_STK_NEXT1    0x50

#define XT_STK_NEXT1    0x50 /* next unused offset */

#define XT_STK_NEXT2    XT_STK_NEXT1

#define XT_STK_N_TMP    3 /* # of 4-byte temp. slots */
#define XT_STK_TMP      XT_STK_NEXT2
#define XT_STK_NEXT3    XT_STK_TMP + (4 * XT_STK_N_TMP)
#define XT_STK_FRMSZ \
	(ALIGNUP(0x10, XT_STK_NEXT3) + 0x20) /* XT_STK_FRMSZ = 0x80 (128) */


#ifndef __ASSEMBLER__

/* @breif Saving context of current function stack frame.
 * @param void
 * @return
 *      - void
 */
void save_context(void);

/* @breif Restoring context of function stack frame.
 * @param void
 * @return
 *      - void
 */
void restore_context(void);

#endif

#endif
