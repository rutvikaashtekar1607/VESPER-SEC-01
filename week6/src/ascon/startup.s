.syntax unified
.cpu cortex-m4
.thumb

.global _start
.global vector_table

.extern fill_stack_region_asm
.extern main

.section .isr_vector, "a", %progbits
.align 2

vector_table:
    .word _stack_top
    .word _start
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0

.section .text.startup, "ax", %progbits
.align 2

_start:
    ldr sp, =_stack_top

    bl fill_stack_region_asm

    ldr sp, =_stack_top

    bl main

halt:
    b halt

.size _start, . - _start