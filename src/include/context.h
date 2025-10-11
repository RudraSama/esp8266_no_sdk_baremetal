/*
 * file      : context.h
 * Author    : Lucky Bairagi (luckybairagi96@gmail.com)
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

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
