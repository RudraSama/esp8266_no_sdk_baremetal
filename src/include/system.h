/*
 * file      : uart.c
 * Author    : Lucky Bairagi (luckybairagi96@gmail.com)
 * Reference : ESP8266 RTOS SDK
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#define CPU_CLK_52MHZ (52 * 1000000)
// #define CPU_CLK_80MHZ  (80 * 1000000)
// #define CPU_CLK_160MHZ (160 * 1000000)
//


#define DPORT_BASE          0x3FF00000

#define EDGE_INT_ENABLE_REG (DPORT_BASE + 0x04)
#define WDT_INT_ENABLE      1
#define WDT_INT_ENABLE_S    0
#define TIMER1_INT_ENABLE   1
#define TIMER1_INT_ENABLE_S 1


#endif
