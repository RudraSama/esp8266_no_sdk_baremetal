/*
 * file      : reg_rw.h
 * Author    : Lucky Bairagi (luckybairagi96@gmail.com)
 */

#ifndef REG_RW_H_
#define REG_RW_H_

#include <stdint.h>

/* @breif Writing value to register.
 * @param uint32_t register, uint32_t value
 * @return
 *      - void
 */
void WRITE_TO_REG(uint32_t, uint32_t);

/* @breif Reading value from register.
 * @param uint32_t register
 * @return
 *      - uint32_t value
 */
uint32_t READ_FROM_REG(uint32_t);


#endif
