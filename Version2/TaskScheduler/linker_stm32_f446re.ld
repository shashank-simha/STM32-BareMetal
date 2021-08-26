ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000,   LENGTH = 512K
  RAM  (xrw) : ORIGIN = 0x20000000,   LENGTH = 128K
}

SECTIONS
{
  .text :
  {
    *(.isr_vector)
    *(.text)
    *(.rodata)
    _etext = .;
  }> FLASH
  
  .data :
  {
  	_sdata = .; /* Start of data on VMA i.e; SRAM */
  	*(.data)
  	_edata = .;
  }> RAM AT> FLASH
  
  .bss :
  {
    _sbss = .;
  	*(.bss)
  	_ebss = .;
  }> RAM
}