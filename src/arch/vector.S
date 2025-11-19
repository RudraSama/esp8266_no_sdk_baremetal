    #include <core/special_registers.h>
    #include <core/excause.h>
    #include <core/context.h>

    .extern isr_handler 

    /* 
     * Temporary global storage for saving scratch register before entering C code ISR.
     *  _chip_interrupt_stk is stack where ISR will run
     * 1536 Value I got from ESP8266 FreeRTOS SDK
     */

    .section    .data, "aw"
    .global     _chip_interrupt_stk, _chip_interrupt_tmp
    .align      16
_chip_interrupt_stk:
    .space       1536
_chip_interrupt_tmp:
    .word        0

    /* I don't know what to do during Panic so just loop forever */
    .section    .text
    .type       panic_loop, @function
    .align      4
    .literal_position
panic_loop:
    j panic_loop 

    .begin      literal_prefix .DebugExceptionVector
    .section    .DebugExceptionVector.text, "ax"
    .global     _DebugExceptionVector
    .align      4
    .literal_position
_DebugExceptionVector:
    /* Save caller's return address to EXCSAVE_1 */
    wsr     a0,  EXCSAVE_1
    /* Save stack pointer to EXCSAVE_2 */
    wsr     a1,  EXCSAVE_2
    j panic_loop
 
    .end        literal_prefix
 
 
    .begin      literal_prefix .DoubleExceptionVector
    .section    .DoubleExceptionVector.text, "ax"
    .global     _DoubleExceptionVector
    .align      4
    .literal_position
_DoubleExceptionVector:
    wsr     a0, EXCSAVE_1 
    wsr     a1, EXCSAVE_2
    j panic_loop
    
    .end        literal_prefix
 
 
    .begin      literal_prefix .KernelExceptionVector
    .section    .KernelExceptionVector.text, "ax"
    .global     _KernelExceptionVector
    .align      4
    .literal_position
_KernelExceptionVector:
    wsr     a0,  EXCSAVE_1
    wsr     a1,  EXCSAVE_2
    j panic_loop
 
    .end        literal_prefix
 

    .begin      literal_prefix .UserExceptionVector
    .section    .UserExceptionVector.text, "ax"
    .global     _UserExceptionVector
    .type       _UserExceptionVector,@function
    .align      4
    .literal_position
_UserExceptionVector:
    wsr     a0,  EXCSAVE_1
    wsr     a1,  EXCSAVE_2
    call0   _user_func_wrap
 
    .end        literal_prefix
 
    .section    .text
    .type       _user_func_wrap,@function 
    .align      4
_user_func_wrap:
    /* Save address of what caused this Exception */
    rsr    a0, EXCCAUSE
    /* If EXCUASE if Level1 Interrupt, jump to _user_func */
    beqi   a0, EXCCAUSE_LEVEL1INTERRUPT, _user_func
    /* Else panic loop */
    j panic_loop 

      
 _user_func:
    /* Storing current sp in a0 */ 
    mov    a0, sp 
    /* Creating space in sp for Exception Frame */
    addi   sp, sp, -XT_STK_FRMSZ    /* addi sp, sp, -0x80 */
    s32i   a0, sp, XT_STK_A1        /* Save pre-interrupt SP */
    rsr    a0, PS                   
    s32i   a0, sp, XT_STK_PS        /* Save process state */  
    rsr    a0, EPC_1
    s32i   a0, sp, XT_STK_PC        /* Save program counter */
    rsr    a0, EXCSAVE_1            
    s32i   a0, sp, XT_STK_A0        /* Save return address of who cause interrupt */
 
    /* Saving registers for task switching */
    s32i   a12, sp, XT_STK_A12 
    s32i   a13, sp, XT_STK_A13
 
    mov    a12, a0                  /* Saving a0 in a12 before calling save_context */
    call0  save_context
    mov    a0, a12                  /* Restore value of a0 */
 
    movi    a0, _chip_interrupt_tmp
    s32i   a1, a0, 0                /* Save a1 at _chip_interrupt_tmp memory */
    mov    a1, a0
 
    call0   isr_handler              /* Calling C code ISR handler */
 
    movi    a0, _chip_interrupt_tmp  /* Restoring a1 from _chip_interrupt_tmp */
    l32i   a1, a0, 0 
 
    mov    a12, a0                  /* Saving a0 in a12 before calling restore_context */
    call0  restore_context
    mov    a0, a12                  /* Restore value of a0 */
 
    /* Restoring registers after task switching */
    l32i   a12, sp, XT_STK_A12
    l32i   a13, sp, XT_STK_A13
 
    /* Restoring Exception Frame registers */
    l32i   a0, sp, XT_STK_PS
    wsr    a0, PS
    l32i   a0, sp, XT_STK_PC
    wsr    a0, EPC_1
    l32i   a0, sp, XT_STK_A0
    l32i   sp, sp, XT_STK_A1
    rsync                          /* Ensures Special Registers are written */
    rfe                            /* PS.EXCM is cleared */
