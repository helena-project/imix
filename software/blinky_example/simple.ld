ENTRY(main)

SECTIONS {
    . = 0x0;
    .vectors : { *(.vectors) }

    . = 0x00010000;
    .text : { *(.text) }

    . = 0x20000000;
    .data : { *(.data) }
    .bss : { *(.bss) }

    __stack_end = 0x2000FFFC;
}
