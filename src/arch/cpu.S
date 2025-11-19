    #include <core/system.h>

    .extern

    .section .text

    .macro intr_lock    ax
    rsil     \ax, EXCM_LEVEL
    .endm

    .macro intr_unlock  ax
    wsr     \ax, PS
    .endm


    .section    .text._isr_unmask, "ax"
    .globl      isr_unmask
    .type       isr_unmask,@function
    .align      4
isr_unmask:
    /* creating new stack frame */
    addi        sp, sp, -16
    s32i        a0, sp, 0 

    intr_lock   a7
    rsr         a3, INTENABLE
    or          a5, a3, a2
    wsr         a5, INTENABLE
    intr_unlock a7
    
    /* loading previous sp value before returning */
    l32i        a0, sp, 0
    addi        sp, sp, 16
    ret

    .section    .text._isr_mask, "ax"
    .globl      _isr_mask
    .type       _isr_mask,@function
    .align      4
isr_mask:
    addi        sp, sp, -16
    s32i        a0, sp, 0 

    intr_lock   a7
    rsr         a3, INTENABLE
    or          a5, a3, a2
    xor         a5, a5, a2
    wsr         a5, INTENABLE
    intr_unlock a7

    l32i        a0, sp, 0
    addi        sp, sp, 16
    ret
