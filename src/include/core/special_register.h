/*
 * file special_register.h
 */

#ifndef SPECIAL_REGISTER_H_
#define SPECIAL_REGISTER_H_

// Copied directly from ESP8266 FREE RTOS

/*  Special registers:  */
#define SAR          3
#define LITBASE      5
#define IBREAKENABLE 96
#define DDR          104
#define IBREAKA_0    128
#define DBREAKA_0    144
#define DBREAKC_0    160
#define EPC_1        177
#define EPC_2        178
#define EPC_3        179
#define DEPC         192
#define EPS_2        194
#define EPS_3        195
#define EXCSAVE_1    209
#define EXCSAVE_2    210
#define EXCSAVE_3    211
#define INTERRUPT    226
#define INTENABLE    228
#define PS           230
#define VECBASE      231
#define EXCCAUSE     232
#define DEBUGCAUSE   233
#define CCOUNT       234
#define PRID         235
#define ICOUNT       236
#define ICOUNTLEVEL  237
#define EXCVADDR     238
#define CCOMPARE_0   240

/*  Special cases (bases of special register series):  */
#define IBREAKA  128
#define DBREAKA  144
#define DBREAKC  160
#define EPC      176
#define EPS      192
#define EXCSAVE  208
#define CCOMPARE 240

/*  Special names for read-only and write-only interrupt registers:  */
#define INTREAD  226
#define INTSET   226
#define INTCLEAR 227

#endif
