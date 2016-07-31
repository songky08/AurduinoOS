/*
 * tricoreIROM.ld -- TriBoard-TC27xx/AppKit-TC27xx full linker script
 *   (using internal Flash for code and internal RAM for data)
 *
 * Copyright (C) 1982-2013 HighTec EDV-Systeme GmbH.
 */

OUTPUT_FORMAT("elf32-tricore")
OUTPUT_ARCH(tricore)
ENTRY(_start)

__TRICORE_DERIVATE_MEMORY_MAP__ = 0x2700;

/* minimal heap size (C library stuff) */
__HEAP_SIZE = DEFINED (__HEAP_SIZE) ? __HEAP_SIZE : 16K;

MEMORY
{
/* internal flash memories */
  int_flash0 (rx): org = 0x80000000, len = 2M
  int_flash1 (rx): org = 0x80200000, len = 2M

/* ED (emulation device) memory */
  ed_mem (rx):  org = 0x9f000000, len = 1M

/* internal code ram */
  int_psprcpu0 (rxc0): org = 0xc0000000, len = 24K
  int_psprcpu1 (rxc1): org = 0xc0000000, len = 24K
  int_psprcpu2 (rxc2): org = 0xc0000000, len = 24K

/* internal data ram */
  int_dsprcpu0 (wc0!x): org = 0xd0000000, len = 112K
  int_dsprcpu1 (wc1!x): org = 0xd0000000, len = 120K
  int_dsprcpu2 (wc2!x): org = 0xd0000000, len = 120K

/* global view on internal memories */
  glb_int_psprcpu0 (rx): org = 0x70100000, len = 24K
  glb_int_psprcpu1 (rx): org = 0x60100000, len = 24K
  glb_int_psprcpu2 (rx): org = 0x50100000, len = 24K
  glb_int_dsprcpu0 (w!x): org = 0x70000000, len = 112K
  glb_int_dsprcpu1 (w!x): org = 0x60000000, len = 120K
  glb_int_dsprcpu2 (w!x): org = 0x50000000, len = 120K

/* global LMU RAM */
/* using the non cachable address enable shared accesses */
  lmu_sram (wx): org = 0xB0000000, len = 32K

/* local view on GTM/MCS data and code memory */
  int_mcs0_code (rx): org = 0x0000, len = 4K
  int_mcs0_data (w):  org = 0x1000, len = 2K

/* TriCore view on GTM/MCS data and code memory */
  glb_mcs0_code (rx): org = 0xf0138000, len = 4K
  glb_mcs0_data (w):  org = 0xf0139000, len = 2K
}

/* map local memory address to the corresponding global address */
REGION_MAP("CPU0", ORIGIN(int_dsprcpu0),  LENGTH(int_dsprcpu0),  ORIGIN(glb_int_dsprcpu0))
REGION_MAP("CPU1", ORIGIN(int_dsprcpu1),  LENGTH(int_dsprcpu1),  ORIGIN(glb_int_dsprcpu1))
REGION_MAP("CPU2", ORIGIN(int_dsprcpu2),  LENGTH(int_dsprcpu2),  ORIGIN(glb_int_dsprcpu2))
REGION_MAP("CPU0", ORIGIN(int_psprcpu0),  LENGTH(int_psprcpu0),  ORIGIN(glb_int_psprcpu0))
REGION_MAP("CPU1", ORIGIN(int_psprcpu1),  LENGTH(int_psprcpu1),  ORIGIN(glb_int_psprcpu1))
REGION_MAP("CPU2", ORIGIN(int_psprcpu2),  LENGTH(int_psprcpu2),  ORIGIN(glb_int_psprcpu2))

/* Use alias for memory regions */
REGION_ALIAS("MCS0_TEXT", glb_mcs0_code)
REGION_ALIAS("MCS0_DATA", glb_mcs0_data)

REGION_ALIAS("CODE_MEM", int_flash0)
REGION_ALIAS("FASTCODE_MEM", int_psprcpu0)
REGION_ALIAS("FASTCODE_MEM_CPU0_", int_psprcpu0)
REGION_ALIAS("FASTCODE_MEM_CPU1_", int_psprcpu1)
REGION_ALIAS("FASTCODE_MEM_CPU2_", int_psprcpu2)

REGION_ALIAS("RODATA_MEM", int_flash0)
REGION_ALIAS("GLOB_DATA", lmu_sram)

REGION_ALIAS("CSA_CPU0_", int_dsprcpu0)
REGION_ALIAS("DATA_CPU0_", int_dsprcpu0)
REGION_ALIAS("SDATA_CPU0_", int_dsprcpu0)
REGION_ALIAS("ZDATA_CPU0_", int_dsprcpu0)
REGION_ALIAS("BSS_CPU0_", int_dsprcpu0)

REGION_ALIAS("CSA_CPU1_", int_dsprcpu1)
REGION_ALIAS("DATA_CPU1_", int_dsprcpu1)
REGION_ALIAS("SDATA_CPU1_", int_dsprcpu1)
REGION_ALIAS("ZDATA_CPU1_", int_dsprcpu1)
REGION_ALIAS("BSS_CPU1_", int_dsprcpu1)

REGION_ALIAS("CSA_CPU2_", int_dsprcpu2)
REGION_ALIAS("DATA_CPU2_", int_dsprcpu2)
REGION_ALIAS("SDATA_CPU2_", int_dsprcpu2)
REGION_ALIAS("ZDATA_CPU2_", int_dsprcpu2)
REGION_ALIAS("BSS_CPU2_", int_dsprcpu2)

/* global and shared: code and data of Master Core CPU0 */
SECTIONS
{
  /*
   * The startup code should be placed where the CPU expects it after a reset,
   * so we try to locate it first, no matter where it appears in the list of
   * objects and libraries (note: because the wildcard pattern doesn't match
   * directories, we'll try to find crt0.o in various (sub)directories).
   */
  .startup : FLAGS(axl)
  {
    /* boot header */
    KEEP (*(.startup.bmhd))
    KEEP (*(.startup.code))
    . = ALIGN(8);
  } > CODE_MEM =0x800
  /*
   * Allocate space for absolute addressable sections; this requires that
   * "int_dspr" starts at a TriCore segment (256M) and points to
   * some RAM area!  If these conditions are not met by your particular
   * hardware setup, you should either not use absolute data, or you
   * must move .zdata*,.zbss*,.bdata*,.bbss* input sections to some appropriate
   * memory area.
   */
 .zbss   : FLAGS(awz)
  {
    ZBSS_BASE = .;
    *(.zbss)
    *(.zbss.*)
    *(.gnu.linkonce.zb.*)
    . = ALIGN(8);
    ZBSS_END = .;
  } > GLOB_DATA
  .zdata  : FLAGS(awzl)
  {
    ZDATA_BASE = .;
    *(.zrodata)
    *(.zrodata.*)
    *(.zdata)
    *(.zdata.*)
    *(.gnu.linkonce.z.*)
    . = ALIGN(8);
    ZDATA_END = .;
  } > GLOB_DATA AT> CODE_MEM

  /*
   * Allocate trap and interrupt vector tables.
   */
  .traptab  : FLAGS(axl)
  {
    *(.traptable)
    . = ALIGN(8);
  } > CODE_MEM

  .inttab : FLAGS(axl)
  {
    KEEP (*(.*.inttable));
    . = ALIGN(8);
  } > CODE_MEM

  /*
   * Allocate .text and other read-only sections.
   */
  .init  : FLAGS(axl)
  {
    *(.init)
    *(.fini)
    . = ALIGN(8);
  } > CODE_MEM =0

  .fasttext  : FLAGS(axl)
  {
    *(.fasttext)
    *(.fasttext.*)
    . = ALIGN(8);
  } > FASTCODE_MEM AT> CODE_MEM

  .text  : FLAGS(axl)
  {
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t.*)
    /*
     * .gnu.warning sections are handled specially by elf32.em.
     */
    *(.gnu.warning)
    . = ALIGN(8);
  } > CODE_MEM =0

  .rodata   : FLAGS(arl)
  {
    *(.rodata)
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
    *(.toc)
    . = ALIGN(8);
  } > RODATA_MEM

  /*
   * Create the clear and copy tables that tell the startup code
   * which memory areas to clear and to copy, respectively.
   */
  CORE_SEC(.clear_sec) : ALIGN(8) FLAGS(arl)
  {
    PROVIDE(__clear_table = .);
    LONG(0 + ADDR(.bss));      LONG(SIZEOF(.bss));
    LONG(0 + ADDR(.sbss));     LONG(SIZEOF(.sbss));
    LONG(0 + ADDR(.zbss));     LONG(SIZEOF(.zbss));
    LONG(-1);                  LONG(-1);
  } > RODATA_MEM
  CORE_SEC(.copy_sec)  : ALIGN(8) FLAGS(arl)
  {
    PROVIDE(__copy_table = .);
    LONG(LOADADDR(.data));     LONG(0 + ADDR(.data));     LONG(SIZEOF(.data));
    LONG(LOADADDR(.sdata));    LONG(0 + ADDR(.sdata));    LONG(SIZEOF(.sdata));
    LONG(LOADADDR(.zdata));    LONG(0 + ADDR(.zdata));    LONG(SIZEOF(.zdata));
    LONG(-1);                  LONG(-1);                  LONG(-1);
  } > RODATA_MEM

  /* mcs sections */
  .mcs0_text :
  {
    MCS0_CODE_BASE = .;
    KEEP(*(.mcs.text*))
    KEEP(*(.mcs_text*))
    MCS0_CODE_END = .;
  } > MCS0_TEXT AT>CODE_MEM
  .mcs0_data :
  {
    MCS0_DATA_BASE = .;
    KEEP(*(.mcs.data*))
    KEEP(*(.mcs_data*))
    MCS0_DATA_END = .;
  } > MCS0_DATA AT>CODE_MEM

  .rodata : FLAGS(arl)
  {
    . = ALIGN(4);
    /*
     * define the copy table accessible from C
     * to copy the MCS code and data into the MCS mem
     */
    PROVIDE(mcs0_copy_table = .);
    LONG(ADDR(.mcs0_text)); LONG(LOADADDR(.mcs0_text)); LONG(SIZEOF(.mcs0_text));
    LONG(ADDR(.mcs0_data)); LONG(LOADADDR(.mcs0_data)); LONG(SIZEOF(.mcs0_data));
    LONG(-1);               LONG(-1);                   LONG(-1);
  } > RODATA_MEM

  /*
   * C++ exception handling tables.  NOTE: gcc emits .eh_frame
   * sections when compiling C sources with debugging enabled (-g).
   * If you can be sure that your final application consists
   * exclusively of C objects (i.e., no C++ objects), you may use
   * the -R option of the "strip" and "objcopy" utilities to remove
   * the .eh_frame section from the executable.
   */
  .eh_frame  :
  {
    *(.gcc_except_table)
    __EH_FRAME_BEGIN__ = .;
    KEEP (*(.eh_frame))
    __EH_FRAME_END__ = .;
    *(.jcr)
    . = ALIGN(8);
  } > CODE_MEM

  /*
   * Constructors and destructors.
   */
  .ctors : FLAGS(arl)
  {
    __CTOR_LIST__ = .;
    LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2);
    *(.ctors)
    LONG(0);
    __CTOR_END__ = .;
    . = ALIGN(8);
  } > CODE_MEM
  .dtors :  FLAGS(arl)
  {
    __DTOR_LIST__ = .;
    LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2);
    *(.dtors)
    LONG(0);
    __DTOR_END__ = .;
    . = ALIGN(8);
  } > CODE_MEM
}

/* CPU0 data and code is linked and located */
CORE_ID = CPU0;
INCLUDE ..\ld\coreN.ld

/* CPU1 data and code is linked and located */
CORE_ID = CPU1;
INCLUDE ..\ld\coreN.ld

/* CPU2 data and code is linked and located */
CORE_ID = CPU2;
INCLUDE ..\ld\coreN.ld

/* Switch to master core CPU0 */
CORE_ID = GLOBAL;

/* global data and debug information */
SECTIONS
{
  .sdata2  : ALIGN(8) FLAGS(arsl)
  {
    *(.sdata.rodata)
    *(.sdata.rodata.*)
    *(*.sdata2)
    *(*.srodata*)
    . = ALIGN(8);
  } > RODATA_MEM

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
  .data : ALIGN(8) FLAGS(awl)
  {
    DATA_BASE = .;
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d.*)
    SORT(CONSTRUCTORS)
    . = ALIGN(8);
    DATA_END = .;
  } > GLOB_DATA AT> CODE_MEM

  .sdata  : ALIGN(8) FLAGS(awsl)
  {
    SDATA_BASE = .;
    PROVIDE(__sdata_start = .);
    *(.sdata)
    _CONFIG_BEGIN_ = .;
    *(.sdata.CONFIG)
    _CONFIG_END_ = .;
    *(.sdata.*)
    *(.gnu.linkonce.s.*)
    . = ALIGN(8);
  } > GLOB_DATA AT> CODE_MEM

  .sbss  : ALIGN(8) FLAGS(aws)
  {
    PROVIDE(__sbss_start = .);
    *(.sbss)
    *(.sbss.*)
    *(.gnu.linkonce.sb.*)
    . = ALIGN(8);
  } > GLOB_DATA

  /*
   * Allocate space for BSS sections.
   */
  .bss  : ALIGN(8) FLAGS(aw)
  {
    BSS_BASE = .;
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(8);
  } > GLOB_DATA

  .heap : ALIGN(8) FLAGS(aw)
  {
    __HEAP = .;
    . += __HEAP_SIZE;
    __HEAP_END = .;
  } > GLOB_DATA
  /* Make sure heap addresses are properly aligned.  */
  _. = ASSERT ((__HEAP_END & 7) == 0 , "HEAP not doubleword aligned");

 /* the symbol __TRICORE_DERIVATE_NAME__ will be defined in the crt0_tc27x.c and is
  * tested here to confirm that this memory map and the startup file will fit together
  */
  _. = ASSERT ((__TRICORE_DERIVATE_MEMORY_MAP__ == __TRICORE_DERIVATE_NAME__), "Using wrong Memory Map. This Map is for TC27XX");

  /* Define a default symbol for address 0.  */
  NULL = DEFINED (NULL) ? NULL : 0;
  /*
   * DWARF debug sections.
   * Symbols in the DWARF debugging sections are relative to the
   * beginning of the section, so we begin them at 0.
   */
  /*
   * DWARF 1
   */
  .comment         0 : { *(.comment) }
  .debug           0 : { *(.debug) }
  .line            0 : { *(.line) }
  /*
   * GNU DWARF 1 extensions
   */
  .debug_srcinfo   0 : { *(.debug_srcinfo) }
  .debug_sfnames   0 : { *(.debug_sfnames) }
  /*
   * DWARF 1.1 and DWARF 2
   */
  .debug_aranges   0 : { *(.debug_aranges) }
  .debug_pubnames  0 : { *(.debug_pubnames) }
  /*
   * DWARF 2
   */
  .debug_info      0 : { *(.debug_info) }
  .debug_abbrev    0 : { *(.debug_abbrev) }
  .debug_line      0 : { *(.debug_line) }
  .debug_frame     0 : { *(.debug_frame) }
  .debug_str       0 : { *(.debug_str) }
  .debug_loc       0 : { *(.debug_loc) }
  .debug_macinfo   0 : { *(.debug_macinfo) }
  .debug_ranges    0 : { *(.debug_ranges) }
  /*
   * DWARF 2 control flow extension
   */
  .debug_control_flow 0 : { *(.debug_control_flow) }
  /*
   * SGI/MIPS DWARF 2 extensions
   */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /*
   * Optional sections that may only appear when relocating.
   */
  /*
   * Optional sections that may appear regardless of relocating.
   */
  .version_info    0 : { *(.version_info) }
}
