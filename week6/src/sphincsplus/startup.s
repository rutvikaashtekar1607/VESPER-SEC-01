.syntax unified
.cpu cortex-m4
.thumb

.global _start
.global vector_table
.global fill_stack_region_asm

.type _start, %function
.type vector_table, %object
.type fill_stack_region_asm, %function

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

fill_stack_region_asm:
    ldr r0, =0x20000E00
    ldr r1, =0x2000F000
    ldr r2, =0xA5A5A5A5

fill_loop:
    cmp r0, r1
    bhs fill_done
    str r2, [r0], #4
    b fill_loop

fill_done:
    bx lr

.size _start, . - _start
.size fill_stack_region_asm, . - fill_stack_region_asm