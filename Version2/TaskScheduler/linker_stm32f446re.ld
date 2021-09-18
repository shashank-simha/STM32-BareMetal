ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);	/* end of "RAM" Ram type memory */

_Min_Heap_Size = 0x200;	/* required amount of heap  */
_Min_Stack_Size = 0x400;	/* required amount of stack */

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000,   LENGTH = 512K
  RAM  (xrw) : ORIGIN = 0x20000000,   LENGTH = 128K
}

SECTIONS
{
  .text :
  {
    . = ALIGN(4);

    *(.isr_vector)
    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    
    . = ALIGN(4);
    _etext = .;
  }> FLASH

  _la_data = LOADADDR(.data);

  .data :
  {
    . = ALIGN(4);

    _sdata = .; /* Start of data on VMA i.e; SRAM */
    *(.data)
    *(.data*)

    . = ALIGN(4);
    _edata = .;
  }> RAM AT> FLASH
  
  .bss :
  {
    . = ALIGN(4);

    _sbss = .;
    __bss_start__ = _sbss;

    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
    . = ALIGN(4);
    _end = .;
    end = _end;
    __end__ = _end;
  }> RAM
}
