.syntax unified
.cpu cortex-m4
.thumb

.global fill_stack_region_asm
.type fill_stack_region_asm, %function

fill_stack_region_asm:
    ldr r0, =0x20000100
    ldr r1, =0x2000F000
    ldr r2, =0xA5A5A5A5

fill_loop:
    cmp r0, r1
    bhs fill_done

    str r2, [r0], #4
    b fill_loop

fill_done:
    bx lr

.size fill_stack_region_asm, . - fill_stack_region_asm