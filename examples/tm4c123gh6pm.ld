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
        
        KEEP(*(.stack_start_value)) /* Begin value for stack pointer */
        KEEP(*(.vectors))

        *(.text*)

        *(.init)
        *(.fini)

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)


        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)

        *(.rodata*)
        KEEP(*(.eh_frame*))

    } >FLASH

    . = ALIGN(4);
    __exidx_start = .;      
    .ARM.exidx : ALIGN(4)
    {
       *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH
    __exidx_end = .;

    _etext = .;

    .data : AT (_etext)
    {
        _data_start = .;
        *(vtable)
        *(.data*)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (_preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (_preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (_init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (_init_array_end = .);

        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (_fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array*))
        PROVIDE_HIDDEN (_fini_array_end = .);

        KEEP(*(.jcr*))

        . = ALIGN(4);
        /* All data end */
        _data_end = .;
    } > SRAM

    .bss :
    {
        . = ALIGN(4);
        _bss_start = .;
        __bss_start__ = .; /* needed by newlib */
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .; /* needed by newlib */
        _bss_end = .;
    } > SRAM

    .stack_dummy (COPY):
    {
        *(.stack*)
    } >SRAM

    /* Set stack top to end of SRAM, and stack limit move down by
     * size of stack_dummy section */
    _StackTop = ORIGIN(SRAM) + LENGTH(SRAM);
    _StackLimit = _StackTop - SIZEOF(.stack_dummy);
    PROVIDE(_stack = _StackTop);
}
