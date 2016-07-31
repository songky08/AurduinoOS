/* Default linker script for a normal executables for CORE N */
/*
 * Define the sizes of the user and system stacks.
 */
CORE_SYM(_ISTACK_SIZE) = DEFINED (CORE_SYM(_ISTACK_SIZE)) ? CORE_SYM(_ISTACK_SIZE) : 1K;
CORE_SYM(_USTACK_SIZE) = DEFINED (CORE_SYM(_USTACK_SIZE)) ? CORE_SYM(_USTACK_SIZE) : 12K;
CORE_SYM(__CSA_SIZE)   = DEFINED (CORE_SYM(__CSA_SIZE))   ? CORE_SYM(__CSA_SIZE)   : 2K;

SECTIONS
{
  /*
   * Allocate space for absolute addressable sections; this requires that
   * "int_dspr" starts at a TriCore segment (256M) and points to
   * some RAM area!  If these conditions are not met by your particular
   * hardware setup, you should either not use absolute data, or you
   * must move .zdata*,.zbss*, input sections to some appropriate
   * memory area.
   */
  CORE_SEC(.zbss)  : FLAGS(awz)
  {
    CORE_SYM(ZBSS_BASE) = .;
    *(*.zbss)
    *(*.zbss.*)
    *(.gnu.linkonce.zb.*)
    . = ALIGN(8);
    CORE_SYM(ZBSS_END) = .;
  } > CORE_SYM(ZDATA)
  CORE_SEC(.zdata)  :  FLAGS(awzl)
  {
    CORE_SYM(ZDATA_BASE) = .;
    *(*.zdata)
    *(*.zdata.*)
    . = ALIGN(8);
    CORE_SYM(ZDATA_END) = .;
  } > CORE_SYM(ZDATA) AT> CODE_MEM

  /*
   * Allocate trap and interrupt vector tables.
   */
  CORE_SEC(.traptab) : ALIGN(8) FLAGS(axwl)
  {
    *(*.traptab)
  } > CODE_MEM

  CORE_SEC(.inttab)  : ALIGN(8) FLAGS(axwl)
  {
    *(*.inttab)
  } > CODE_MEM

  CORE_SEC(.init)    : ALIGN(8) FLAGS(axl)
  {
    /* we have to keep all .init/.fini section
       because the linker should not delete this
       sections with --gc-sections
     */
    KEEP(*(SORT(*.init*)))
  } > CODE_MEM =0

  CORE_SEC(.fini)    : ALIGN(8) FLAGS(axl)
  {
    KEEP(*(SORT(*.fini*)))
  } > CODE_MEM =0

  /*
   * Allocate .text and other read-only sections.
   */
  CORE_SEC(.fasttext) ADDR(.fasttext)+SIZEOF(.fasttext) : FLAGS(axl)
  {
    *(*.fasttext)
    *(*.fasttext.*)
    . = ALIGN(8);
  } > CORE_SYM(FASTCODE_MEM) AT> CODE_MEM

  CORE_SEC(.text)    : ALIGN(8) FLAGS(axl)
  {
    *(*.text)
    *(*.text.*)
  } > CODE_MEM =0

  CORE_SEC(.rodata)  : ALIGN(8) FLAGS(arl)
  {
    *(*.rodata*)
  } > RODATA_MEM

  /*
   * Create the clear and copy tables that tell the startup code
   * which memory areas to clear and to copy, respectively.
   */
  CORE_SEC(.clear_sec) : ALIGN(8) FLAGS(arl)
  {
    PROVIDE(CORE_SYM(__clear_table) = .);
    LONG(0 + ADDR(CORE_SEC(.bss)));      LONG(SIZEOF(CORE_SEC(.bss)));
    LONG(0 + ADDR(CORE_SEC(.zbss)));     LONG(SIZEOF(CORE_SEC(.zbss)));
    LONG(0 + ADDR(CORE_SEC(.sbss)));     LONG(SIZEOF(CORE_SEC(.sbss)));
    LONG(0 + ADDR(CORE_SEC(.sbss3)));    LONG(SIZEOF(CORE_SEC(.sbss3)));
    LONG(0 + ADDR(CORE_SEC(.sbss4)));    LONG(SIZEOF(CORE_SEC(.sbss4)));
    LONG(-1);                            LONG(-1);
  } > RODATA_MEM
  CORE_SEC(.copy_sec)  : ALIGN(8) FLAGS(arl)
  {
    PROVIDE(CORE_SYM(__copy_table) = .);
    LONG(LOADADDR(.fasttext));           LONG(0 + ADDR(.fasttext));           LONG(SIZEOF(.fasttext));
    LONG(LOADADDR(CORE_SEC(.fasttext))); LONG(0 + ADDR(CORE_SEC(.fasttext))); LONG(SIZEOF(CORE_SEC(.fasttext)));
    LONG(LOADADDR(CORE_SEC(.data)));     LONG(0 + ADDR(CORE_SEC(.data)));     LONG(SIZEOF(CORE_SEC(.data)));
    LONG(LOADADDR(CORE_SEC(.zdata)));    LONG(0 + ADDR(CORE_SEC(.zdata)));    LONG(SIZEOF(CORE_SEC(.zdata)));
    LONG(LOADADDR(CORE_SEC(.sdata)));    LONG(0 + ADDR(CORE_SEC(.sdata)));    LONG(SIZEOF(CORE_SEC(.sdata)));
    LONG(LOADADDR(CORE_SEC(.sdata3)));   LONG(0 + ADDR(CORE_SEC(.sdata3)));   LONG(SIZEOF(CORE_SEC(.sdata3)));
    LONG(LOADADDR(CORE_SEC(.sdata4)));   LONG(0 + ADDR(CORE_SEC(.sdata4)));   LONG(SIZEOF(CORE_SEC(.sdata4)));
    LONG(-1);                            LONG(-1);                            LONG(-1);
  } > RODATA_MEM

  CORE_SEC(.sdata2)  : ALIGN(8) FLAGS(arsl)
  {
    PROVIDE(CORE_SYM(_SMALL_DATA2_) = 0x8000);
    *(*.sdata2)
    *(*.sdata.rodata)
    *(*.sdata.rodata.*)
    *(*.srodata*)
  } > RODATA_MEM

  CORE_SEC(.ctors)   : FLAGS(arl)
  {
    CORE_SYM(__CTOR_LIST__) = .;
    LONG((CORE_SYM(__CTOR_END__) - CORE_SYM(__CTOR_LIST__)) / 4 - 2);
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    /* We don't want to include the .ctor section from
       from the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    LONG(0);
    CORE_SYM(__CTOR_END__) = .;
    . = ALIGN(8);
  } > CODE_MEM
  CORE_SEC(.dtors)   : FLAGS(arl)
  {
    CORE_SYM(__DTOR_LIST__) = .;
    LONG((CORE_SYM(__DTOR_END__) - CORE_SYM(__DTOR_LIST__)) / 4 - 2);
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    LONG(0) ;
    CORE_SYM(__DTOR_END__) = .;
    . = ALIGN(8);
  } > CODE_MEM

  /*
   * We're done now with the text part of the executable.  The
   * following sections are special in that their initial code or
   * data (if any) must also be stored in said text part of an
   * executable, but they "live" at completely different addresses
   * at runtime -- usually in RAM areas.  NOTE: This is not really
   * necessary if you use a special program loader (e.g., a debugger)
   * to load a complete executable consisting of code, data, BSS, etc.
   * into the RAM of some target hardware or a simulator, but it *is*
   * necessary if you want to burn your application into non-volatile
   * memories such as EPROM or FLASH.
   */
  CORE_SEC(.data)    : ALIGN(8) FLAGS(awl)
  {
    *(*.data)
    *(*.data.*)
  } > CORE_SYM(DATA) AT> CODE_MEM

  CORE_SEC(.sdata)   : ALIGN(8) FLAGS(awsl)
  {
    CORE_SYM(SDATA_BASE) = .;
    PROVIDE(CORE_SYM(_SMALL_DATA_) = 0x8000);
    *(*.sdata)
    *(*.sdata.*)
  } > CORE_SYM(SDATA) AT> CODE_MEM

  CORE_SEC(.sbss)    : ALIGN(8) FLAGS(aws)
  {
    *(*.sbss)
    *(*.sbss.*)
  } > CORE_SYM(SDATA)


  CORE_SEC(.sdata3)  : ALIGN(8) FLAGS(awsl)
  {
    CORE_SYM(SDATA3_BASE) = .;
    PROVIDE(CORE_SYM(_SMALL_DATA3_) = 0x8000);
    *(*.sdata3*)
  } > CORE_SYM(SDATA) AT> CODE_MEM

  CORE_SEC(.sbss3)   : ALIGN(8) FLAGS(aws)
  {
    *(*.sbss3*)
  } > CORE_SYM(SDATA)

  CORE_SEC(.sdata4)  : ALIGN(8) FLAGS(awsl)
  {
    CORE_SYM(SDATA4_BASE) = .;
    PROVIDE(CORE_SYM(_SMALL_DATA4_) = 0x8000);
    *(*.sdata4*)
  } > CORE_SYM(SDATA)  AT> CODE_MEM

  CORE_SEC(.sbss4)   : ALIGN(8) FLAGS(aws)
  {
    *(*.sbss4*)
  } > CORE_SYM(SDATA)

  CORE_SEC(.bss)     : ALIGN(8) FLAGS(aw)
  {
    *(*.bss*)
  } > CORE_SYM(BSS)

  CORE_SEC(.ustack)  : ALIGN(8) FLAGS(aw)
  {
    . +=  CORE_SYM(_USTACK_SIZE);
    CORE_SYM(__USTACK) =  .;
  } > CORE_SYM(BSS)

  CORE_SEC(.istack)  : ALIGN(8) FLAGS(aw)
  {
    . +=  CORE_SYM(_ISTACK_SIZE);
    CORE_SYM(__ISTACK) =  .;
  } > CORE_SYM(BSS)

  /* define the CSA Memory area as an own section
   * this section will be allocated into the internal RAM
   * after the absolute addressable sections .zdata/.zbss
   * and allocate all internal memory not occupied by .zdata/.zbss
   */
  CORE_SEC(.csa) : ALIGN(64) FLAGS(aw)
  {
    CORE_SYM(__CSA_BEGIN) = .;
    . +=  CORE_SYM(__CSA_SIZE);
    CORE_SYM(__CSA_END) = .;
  } > CORE_SYM(CSA)
  CORE_SYM(__CSA_SIZE) = CORE_SYM(__CSA_END) - CORE_SYM(__CSA_BEGIN);

  /* Make sure CSA, stack and heap addresses are properly aligned.  */
  _. = ASSERT ((CORE_SYM(__CSA_BEGIN) & 0x3f) == 0 , "illegal CSA start address");
  _. = ASSERT ((CORE_SYM(__CSA_SIZE) & 0x3f) == 0 , "illegal CSA size");
  _. = ASSERT ((CORE_SYM(__ISTACK) & 7) == 0 , "ISTACK not doubleword aligned");
  _. = ASSERT ((CORE_SYM(__USTACK) & 7) == 0 , "USTACK not doubleword aligned");

  /* Define a default symbol for address 0.  */
  NULL = DEFINED (NULL) ? NULL : 0;
}
