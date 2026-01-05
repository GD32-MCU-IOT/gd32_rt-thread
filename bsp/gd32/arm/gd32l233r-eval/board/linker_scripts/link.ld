/* Linker script for GD32L233RC */

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = 0x20008000;    /* end of RAM (32KB) */

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x200;      /* required amount of heap  */
_Min_Stack_Size = 0x400;     /* required amount of stack */

/* Specify the memory areas */
MEMORY
{
    CODE (rx) : ORIGIN = 0x08000000, LENGTH = 256K    /* Flash 256KB for GD32L233RC */
    DATA (rw) : ORIGIN = 0x20000000, LENGTH = 32K     /* SRAM 32KB for GD32L233RC */
}

/* 
 * Define the size of the stack used by the system. 
 * This is for the main stack pointer (MSP), used before RT-Thread scheduler starts and in interrupts.
 */
_system_stack_size = 0x200;

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        _stext = .;
        KEEP(*(.isr_vector))            /* Backup: also keep .isr_vector if exists */
        . = ALIGN(4);
        *(.text)                        /* remaining code */
        *(.text.*)                      /* remaining code */
        *(.rodata)                      /* read-only data (constants) */
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        *(.gnu.linkonce.t*)

        /* section information for finsh shell */
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;
        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;
        . = ALIGN(4);

        /* section information for initial. */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(4);

        . = ALIGN(4);
        _etext = .;
    } > CODE

    /* 
     * The .ARM.exidx section is needed for exception handling and stack unwinding.
     * It should be placed in a loadable region like CODE.
     */
    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > CODE
    
    /*
     * Define the load address for the .data section.
     * It should immediately follow the .ARM.exidx section in Flash.
     */
    _sidata = __exidx_end;

    /* .data section which is used for initialized data */
    .data : AT (_sidata)
    {
        . = ALIGN(4);
        _sdata = . ;
        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d*)
        . = ALIGN(4);
        _edata = . ;
    } > DATA

    /* Main stack, located at the top of the RAM region */
    .stack (NOLOAD):
    {
        . = ALIGN(8);
        _sstack = .;
        . = . + _system_stack_size;
        . = ALIGN(8);
        _estack = .;
        _sp = _estack;  /* Alias for startup code compatibility */
    } > DATA

    /* .bss section which is used for uninitialized data */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = . ;
    } > DATA

    /* Define __bss_end for C code to find the heap start. */
    __bss_end = _ebss;

    _end = .;
    
    /******************************************************************************
     * Corrected section to discard unwanted information from the final binary. *
     ******************************************************************************/
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )

        /* Discard all debugging and comment sections using the correct wildcard syntax */
        *(.comment)
        *(.note.gnu.build-id)
        *(.ARM.attributes)
    }
}