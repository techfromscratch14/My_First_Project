/* program entry point */
ENTRY(Reset_Handler)

/* Define physical memory regions */

MEMORY
{

/* Internal FLASH memory */

FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K

/*Internal SRAM memory */

RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Top of the stack */
_estack = ORIGIN(RAM) + LENGTH(RAM) ;

SECTIONS
{

    /* Interupt vector table */

    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    /* program code and read only data */

    .text :
    {
        *(.text*)
        *(.rodata*)
    } > FLASH

    /* FLASH address of initialized variables */

    _sidata = LOADADDR(.data);

    /* Initialized global/static variables */
    .data :
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM AT > FLASH

    /* Uninitialized global /static variables */

    .bss :
    {

        _sbss = .;
        *(.bss*)
        *(COMMON)

        _ebss = .;

    } >RAM
}