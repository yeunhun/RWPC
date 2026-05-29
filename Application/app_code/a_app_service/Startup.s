.set     VTOR_REG, 0xE000ED08
.section ".START_CODE"
.globl   Reset_Handler
.type    Reset_Handler, $function

Reset_Handler:

    ldr  r0, =VTOR_REG
    ldr  r1, =Os_ExceptionVectorTable
    str  r1,[r0]

    b    _start_T

.size Reset_Handler, . - Reset_Handler
