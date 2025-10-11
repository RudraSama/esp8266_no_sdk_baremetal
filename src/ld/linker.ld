MEMORY
{
    dport0_0_seg (rx):                        org = 0x3FF00000, len = 0x10
    dram0_0_seg (rw):                         org = 0x3FFE8000, len = 0x18000
    iram0_0_seg (rx):                         org = 0x40100000, len = 0x8000

    /* This is basically where Flash Memory is Mapped in ESP8266. Because 
     * Esp8266 doesn't have internal Flash.
     */
    irom0_0_seg (rx):                         org = 0x40200010, len = 0x3C000
}

ENTRY(app_entry)

SECTIONS
{
    .init : ALIGN(4) {
        _inti_start = ABSOLUTE(.);
        *(.init*) 
        _inti_end = ABSOLUTE(.);
    } > iram0_0_seg 

    /* Every IRAM section will go into internal IRAM memory.
     */
    .iram0.text : ALIGN(4) {
        _iram0_text_start = ABSOLUTE(.);
        *(.iram0.text* .iram0.literal* .iram0.literal.*)
        *(.literal .text)
        _iram0_text_end = ABSOLUTE(.);
    } > iram0_0_seg

    /* Every IROM section will go into SPI Flash Memory.
     */
    .irom0.text : ALIGN(4) {
        _irom0_text_start = ABSOLUTE(.);
        *(.irom0.literal .irom0.text )
        *(.irom.literal .irom.text)
        _irom0_text_end = ABSOLUTE(.);
    } > irom0_0_seg

    .dram0.data : ALIGN(4) {
        _dram0_data_start = ABSOLUTE(.);
        *(.dram0.data*)
        _dram0_data_end = ABSOLUTE(.);
    } > dram0_0_seg

    .dram0.bss (NOLOAD) : ALIGN(4) {
        _dram0_bss_start = ABSOLUTE(.);
        *(.dram0.bss*)
        _dram0_bss_end = ABSOLUTE(.);
    } > dram0_0_seg

    .dram.rodata : ALIGN(4) {
        _dram0_rodata_start = ABSOLUTE(.);
        *(.dram0.rodata*) 
        *(.rodata. .rodata*)
        _dram0_rodata_end = ABSOLUTE(.);
    } > dram0_0_seg

    .irom0.rodata : ALIGN(4) {
        _irom0_rodata_start = ABSOLUTE(.);
        *(.irom0.rodata*) 
        _irom0_rodata_end = ABSOLUTE(.);
    } > irom0_0_seg

    .dport0.rodata : ALIGN(4) {
        _dport0_rodata_start = ABSOLUTE(.);
        *(.dport0.rodata)
        *(.dport.rodata)
        _dport0_rodata_end = ABSOLUTE(.);
    } >dport0_0_seg

    .dport0.literal : ALIGN(4) {
       _dport0_literal_start = ABSOLUTE(.);
        *(.dport0.literal)
        *(.dport.literal)
       _dport0_literal_end = ABSOLUTE(.);
    } >dport0_0_seg

    .dport0.data : ALIGN(4) {
       _dport0_literal_start = ABSOLUTE(.);
        *(.dport0.data)
        *(.dport.data)
       _dport0_literal_end = ABSOLUTE(.);
    } >dport0_0_seg
}
