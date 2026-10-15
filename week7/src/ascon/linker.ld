ENTRY(_start)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    .text :
    {
        . = ALIGN(4);
        *(.text.startup)
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    .data :
    {
        . = ALIGN(4);
        __data_start__ = .;
        *(.data*)
        . = ALIGN(4);
        __data_end__ = .;
    } > RAM AT > FLASH

    __data_load__ = LOADADDR(.data);

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM

    . = ALIGN(8);

    _end = .;

    /*
     * Dedicated Week 7 benchmark buffer region.
     * Placed above the stack so large message/ciphertext buffers
     * do not consume the limited .bss area or interfere with
     * stack high-water measurement.
     */
    .bench_buffers 0x20010000 (NOLOAD) :
    {
        . = ALIGN(4);
        __bench_buffers_start__ = .;
        *(.bench_buffers)
        . = ALIGN(4);
        __bench_buffers_end__ = .;
    } > RAM

    ASSERT(__bench_buffers_end__ <= 0x20020000,
           "ERROR: benchmark buffers exceed RAM")

    /*
     * Dedicated stack region.
     * Stack grows downward from _stack_top.
     */
    _stack_bottom = 0x20000100;
    _stack_top    = 0x2000F000;

    ASSERT(_end < _stack_bottom,
           "ERROR: .bss/data overlaps stack region")
}
