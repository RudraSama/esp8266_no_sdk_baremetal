    
    #include <core/context.h>

    /* This functions must be called after caller create space in sp. */
    .align 0x4
    .type   save_context,@function
    .global save_context
save_context:
    s32i    a2, sp, XT_STK_A2
    s32i    a3, sp, XT_STK_A3
    s32i    a4, sp, XT_STK_A4
    s32i    a5, sp, XT_STK_A5
    s32i    a6, sp, XT_STK_A6
    s32i    a7, sp, XT_STK_A7
    s32i    a8, sp, XT_STK_A8
    s32i    a9, sp, XT_STK_A9
    s32i    a10, sp, XT_STK_A10
    s32i    a11, sp, XT_STK_A11

    rsr     a3, SAR
    s32i    a3, sp, XT_STK_SAR
    ret.n

    .align 0x4
    .type   restore_context,@function
    .global restore_context
restore_context:
    l32i    a3, sp, XT_STK_SAR
    l32i    a2, sp, XT_STK_A2
    wsr     a3, SAR
    l32i    a3, sp, XT_STK_A3
    l32i    a4, sp, XT_STK_A4
    l32i    a5, sp, XT_STK_A5
    l32i    a6, sp, XT_STK_A6
    l32i    a7, sp, XT_STK_A7
    l32i    a8, sp, XT_STK_A8
    l32i    a9, sp, XT_STK_A9
    l32i    a10, sp, XT_STK_A10
    l32i    a11, sp, XT_STK_A11
    ret.n
 
