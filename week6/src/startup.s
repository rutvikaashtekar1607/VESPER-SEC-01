.syntax unified
.cpu cortex-m4
.thumb

.global _start
.type _start, %function

.extern fill_stack_region_asm
.extern main

_start:
    ldr sp, =_stack_top

    bl fill_stack_region_asm

    ldr sp, =_stack_top
    bl main

halt:
    b halt

.size _start, . - _start