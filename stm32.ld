_estack = ORIGIN(RAM) + LENGTH(RAM);

_rom_begin  = 0x08000000;
_rom_end    = 0x08007FFC;

_sstack = 0x20001800;
_estack = 0x20002000;

__initial_sp = 0x20002000;

MEMORY
{
  RAM   (xrw)   : ORIGIN = 0x20000000,  LENGTH = 20K
  FLASH (rx)    : ORIGIN = 0x8000000,   LENGTH = 64K
}

SECTIONS
{
  . = 0x08000000;
  . = ALIGN(4);

  .reset_vector :
  {
    *(.reset_vector)
    . = ALIGN(0x100);
    KEEP(*(.reset_vector))
  } >FLASH = 0xAAAA

  .text :
  {
    _ctors_begin = .;
    *(.init_array)
    . = ALIGN(4);
    KEEP (*(SORT(.init_array)))
    _ctors_end = .;
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.rodata)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  . = 0x20000000;
  . = ALIGN(4);

  .data :
  {
    _data_begin = .;
    *(.data)
    . = ALIGN(4);
    KEEP (*(.data))
    *(.data*)
    . = ALIGN(4);
    KEEP (*(.data*))
    _data_end = .;
  } >RAM AT >FLASH

  .bss :
  {
    _bss_begin = .;
    *(.bss)
    . = ALIGN(4);
    KEEP (*(.bss))
    *(.bss*)
    . = ALIGN(4);
    KEEP (*(.bss*))
    _bss_end = .;
  } > RAM

  _rom_data_begin = LOADADDR(.data);
}
    