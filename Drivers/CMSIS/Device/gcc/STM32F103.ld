
ENTRY(Reset_Handler)

MEMORY
{
	FLASH (rx)  :  ORIGIN = 0x08000000, LENGTH = 64K
	SRAM  (rxw) :  ORIGIN = 0x20000000, LENGTH = 20K
}

_estack = 0x20004FFF; 

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
		*(.text)
		. = ALIGN(4);
	} > FLASH

	.rodata :
	{
		. = ALIGN(4);
		*(.rodata)
		. = ALIGN(4);
	} > FLASH

	_sidata = LOADADDR(.data);

	.data :
	{
		. = ALIGN(4);
		_sdata = .;
		*(.data);
		. = ALIGN(4);
		_edata = .;
	} > SRAM AT> FLASH

	.bss :
	{
		. = ALIGN(4);
		_sbss = .;
		*(.bss)
		. = ALIGN(4);
		_ebss = .;
	} > SRAM
}


