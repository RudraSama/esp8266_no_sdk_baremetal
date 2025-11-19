/*
 * file excause.h
 */

#ifndef EXCAUSE_H_
#define EXCAUSE_H_

// Copied directly from ESP8266 FREE RTOS

/*  EXCCAUSE register values:  */
/*
 *  General Exception Causes
 *  (values of EXCCAUSE special register set by general exceptions,
 *   which vector to the user, kernel, or double-exception vectors).
 */
#define EXCCAUSE_ILLEGAL     0 /* Illegal Instruction */
#define EXCCAUSE_SYSCALL     1 /* System Call (SYSCALL instruction) */
#define EXCCAUSE_INSTR_ERROR 2 /* Instruction Fetch Error */
#define EXCCAUSE_IFETCHERROR \
	2 /* (backward compatibility macro, deprecated, avoid) */
#define EXCCAUSE_LOAD_STORE_ERROR 3 /* Load Store Error */
#define EXCCAUSE_LOADSTOREERROR \
	3 /* (backward compatibility macro, deprecated, avoid) */
#define EXCCAUSE_LEVEL1_INTERRUPT 4 /* Level 1 Interrupt */
#define EXCCAUSE_LEVEL1INTERRUPT \
	4 /* (backward compatibility macro, deprecated, avoid) */
#define EXCCAUSE_ALLOCA \
	5 /* Stack Extension Assist (MOVSP instruction) for alloca */
#define EXCCAUSE_DIVIDE_BY_ZERO 6 /* Integer Divide by Zero */
#define EXCCAUSE_SPECULATION \
	7 /* Use of Failed Speculative Access (not implemented) */
#define EXCCAUSE_PRIVILEGED 8 /* Privileged Instruction */
#define EXCCAUSE_UNALIGNED  9 /* Unaligned Load or Store */
/* Reserved				10..11 */
#define EXCCAUSE_INSTR_DATA_ERROR \
	12 /* PIF Data Error on Instruction Fetch (RB-200x and later) */
#define EXCCAUSE_LOAD_STORE_DATA_ERROR \
	13 /* PIF Data Error on Load or Store (RB-200x and later) */
#define EXCCAUSE_INSTR_ADDR_ERROR \
	14 /* PIF Address Error on Instruction Fetch (RB-200x and later) */
#define EXCCAUSE_LOAD_STORE_ADDR_ERROR \
	15 /* PIF Address Error on Load or Store (RB-200x and later) */
#define EXCCAUSE_ITLB_MISS \
	16 /* ITLB Miss (no ITLB entry matches, hw refill also missed) */
#define EXCCAUSE_ITLB_MULTIHIT \
	17 /* ITLB Multihit (multiple ITLB entries match) */
#define EXCCAUSE_INSTR_RING \
	18 /* Ring Privilege Violation on Instruction Fetch */
/* Reserved				19 */ /* Size Restriction on IFetch (not implemented) */
#define EXCCAUSE_INSTR_PROHIBITED \
	20 /* Cache Attribute does not allow Instruction Fetch */
/* Reserved				21..23 */
#define EXCCAUSE_DTLB_MISS \
	24 /* DTLB Miss (no DTLB entry matches, hw refill also missed) */
#define EXCCAUSE_DTLB_MULTIHIT \
	25 /* DTLB Multihit (multiple DTLB entries match) */
#define EXCCAUSE_LOAD_STORE_RING \
	26                        /* Ring Privilege Violation on Load or Store */
/* Reserved				27 */ /* Size Restriction on Load/Store (not
                                 implemented) */
#define EXCCAUSE_LOAD_PROHIBITED 28 /* Cache Attribute does not allow Load */
#define EXCCAUSE_STORE_PROHIBITED              \
	29 /* Cache Attribute does not allow Store \
	    */
/* Reserved				30..31 */
#define EXCCAUSE_CP_DISABLED(n) \
	(32 + (n))                   /* Access to Coprocessor 'n' when disabled */
#define EXCCAUSE_CP0_DISABLED 32 /* Access to Coprocessor 0 when disabled */
#define EXCCAUSE_CP1_DISABLED 33 /* Access to Coprocessor 1 when disabled */
#define EXCCAUSE_CP2_DISABLED 34 /* Access to Coprocessor 2 when disabled */
#define EXCCAUSE_CP3_DISABLED 35 /* Access to Coprocessor 3 when disabled */
#define EXCCAUSE_CP4_DISABLED 36 /* Access to Coprocessor 4 when disabled */
#define EXCCAUSE_CP5_DISABLED 37 /* Access to Coprocessor 5 when disabled */
#define EXCCAUSE_CP6_DISABLED 38 /* Access to Coprocessor 6 when disabled */
#define EXCCAUSE_CP7_DISABLED 39 /* Access to Coprocessor 7 when disabled */

#endif
