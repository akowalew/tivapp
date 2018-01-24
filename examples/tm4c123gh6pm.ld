/**
 * tm4c123gh6pm.ld
 * Linker script for application
 * Author: akowalew
 */

ENTRY(resetISR)

/* Specify the memory areas */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
}

SECTIONS {
    .text :
    {
        . = ALIGN(4);
        _start_text = .;
        KEEP(*(.stack_start_value)) /* Begin value for stack pointer */
        KEEP(*(.isr_vector)) /* Startup code */
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        _end_text = .;
    } >FLASH

    _etext = .;
    _end_text = .;

    .data : AT (_end_text)
    {
        _start_data = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _end_data = .;
    } >SRAM

    .bss :
    {
         . = ALIGN(4);
        _start_bss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _end_bss = .;
    } >SRAM

    .init.array :
    {
        __init_array_start = .;
        *(.init_array)
        *(.init_array.*)
        __init_array_end = .;
    } >SRAM

    .vtable :
    {
        . = ALIGN(1024);
        _start_vtable = .;
        *(.vtable)
        *(.vtable*)
        _end_vtable = .;
    } >SRAM

    .stack_dummy (COPY):
    {
        _end_stack = .;
        *(.stack*)
    } >SRAM

    /* Set stack top to end of SRAM, and stack limit move down by
     * size of stack_dummy section */
    _start_stack = ORIGIN(SRAM) + LENGTH(SRAM);
    _size_stack = _start_stack - SIZEOF(.stack_dummy);
    PROVIDE(__stack = _start_stack);
}
