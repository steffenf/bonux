OUTPUT_FORMAT("binary");
ENTRY(startup32)
phys = 0x00200000;
SECTIONS
{
  .text phys :
  {
    code = .; _code = .; __code = .;
    *(.text)
    . = ALIGN(4096);
  }

  .data :
  {
    data = .; _data = .; __data = .;
    *(.data)
    *(.rodata);
    . = ALIGN(4096);
  }

  .comment :
  {
    comment = .; _comment = .; __comment = .;
    *(.comment)
    . = ALIGN(4096);
  }

  .bss :
  {
    bss = .; _bss = .; __bss = .;
    *(.bss)
    . = ALIGN(4096);
  }
  end = .; _end = .; __end = .;
}
