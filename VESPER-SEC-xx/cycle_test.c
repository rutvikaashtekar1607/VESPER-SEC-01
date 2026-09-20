#define STACK_TOP 0x20020000  // top of STM32F407 SRAM

void Reset_Handler(void) {
    __asm volatile (
        ".rept 1000\n"
        "nop\n"
        ".endr\n"
        "b .\n"        // infinite loop — halts execution cleanly here
    );
}

__attribute__((section(".isr_vector")))
void (* const vector_table[])(void) = {
    (void(*)(void))STACK_TOP,
    Reset_Handler
};