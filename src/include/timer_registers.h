/*
 * file      : time_registers.h
 * Author    : Lucky Bairagi (luckybairagi96@gmail.com)
 * Reference : ESP8266 RTOS SDK
 */


#ifndef TIMER_REGISTERS_H_
#define TIMER_REGISTERS_H_

#define TIMER_BASE           0x60000600

#define FRC1                 (TIMER_BASE + 0x00)
#define FRC1_TIMER_VALUE     0x007FFFFF
#define FRC1_TIMER_VALUE_S   0
#define FRC1_DATA_MSB        22
#define FRC1_DATA_LSB        0
#define FRC1_DATA_MASK       0x007FFFFF

#define FRC1_COUNT           (TIMER_BASE + 0x04)
#define FRC1_TIMER_COUNT     0x007FFFFF
#define FRC1_TIMER_COUNT_S   0
#define FRC1_COUNT_DATA_MSB  22
#define FRC1_COUNT_DATA_LSB  0
#define FRC1_COUNT_DATA_MASK 0x007FFFFF

#define FRC1_CTRL            (TIMER_BASE + 0x08)
#define FRC1_CTRL_INT        (1 << 8)
#define FRC1_TIMER_CTRL      0x000000FF
#define FRC1_CTRL_DATA_MSB   7
#define FRC1_CTRL_DATA_LSB   0
#define FRC1_CTRL_DATA_MASK  0x000000FF

#define FRC1_INT             (TIMER_BASE + 0x0c)
#define FRC1_INT_CLR         (1 << 0)
#define FRC1_INT_CLR_MASK    0x00000001

#define FRC2                 (TIMER_BASE + 0x20)
#define FRC2_TIMER_VALUE     0xFFFFFFFF
#define FRC2_TIMER_VALUE_S   0
#define FRC2_DATA_MSB        31
#define FRC2_DATA_LSB        0
#define FRC2_DATA_MASK       0xFFFFFFFF

#define FRC2_COUNT           (TIMER_BASE + 0x24)
#define FRC2_TIMER_COUNT     0xFFFFFFFF
#define FRC2_TIMER_COUNT_S   0
#define FRC2_COUNT_DATA_MSB  31
#define FRC2_COUNT_DATA_LSB  0
#define FRC2_COUNT_DATA_MASK 0xFFFFFFFF

#define FRC2_CTRL            (TIMER_BASE + 0x28)
#define FRC2_CTRL_INT        (1 << 8)
#define FRC2_TIMER_CTRL      0x000000FF
#define FRC2_CTRL_DATA_MSB   7
#define FRC2_CTRL_DATA_LSB   0
#define FRC2_CTRL_DATA_MASK  0x000000FF

#define FRC2_INT             (TIMER_BASE + 0x2c)
#define FRC2_INT_CLR         (1 << 0)
#define FRC2_INT_CLR_MASK    0x00000001

#define FRC2_ALARM           (TIMER_BASE + 0x30)
#define FRC2_TIMER_ALARM     0xFFFFFFFF
#define FRC2_TIMER_ALARM_S   0
#define FRC2_ALARM_DATA_MSB  31
#define FRC2_ALARM_DATA_LSB  0
#define FRC2_ALARM_DATA_MASK 0xFFFFFFFF

#endif
