.align  0x4
.type   WRITE_TO_REG,@function
.global WRITE_TO_REG
WRITE_TO_REG:
    memw
    s32i a3, a2, 0 
    ret.n


.align  0x4
.type   READ_FROM_REG,@function
.global READ_FROM_REG
READ_FROM_REG:
    memw
    l32i.n a2, a2, 0
    ret.n
