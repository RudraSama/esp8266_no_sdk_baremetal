.align 0x4
.global save_context
save_context:
    addi a1, a1, -20
    s32i a12, a1, 0
    s32i a13, a1, 4
    s32i a14, a1, 8
    s32i a15, a1, 12
    s32i a0,  a1, 16
    ret.n

.align 0x4
.global restore_context
restore_context:
    l32i a12, a1, 0
    l32i a13, a1, 4
    l32i a14, a1, 8
    l32i a15, a1, 12
    l32i a0,  a1, 16
    addi a1, a1, 20 
    ret.n
 
