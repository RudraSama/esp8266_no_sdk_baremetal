````markdown
# Compiling Source

xtensa-lx106-elf-as -o crt0.o crt0.S
xtensa-lx106-elf-gcc -nostdlib -c main.c -o main.o
xtensa-lx106-elf-ld -T linker.ld crt0.o main.o -o firmware.elf
xtensa-lx106-elf-objcopy -O binary firmware.elf firmware.bin
esptool.py --port /dev/ttyUSB0 write_flash 0x00000 firmware.bin
````

---

# Important Instructions in Xtensa Arch.
| Instruction | Detail |
|-------------|--------|
|   s32i r1, r2, 0     | Store value of r1 at address [r2 + 0] |
|   l32i r1, r2, 0     | Load value from [r2 + 0] address into r1 |
|   movi r1, const     | Store any 12bit value (-2048..2047) into r1. It has narrow version movi.n for 6 bit. |
|   rsr * r1 / rsr r1, * | Read from special register (\*). Both syntax are correct. |
|   wsr r1, * | Store value of r1 into special register (\*). |
|   rsync | Waits for wsr to complete its operation, so next instruction can read value of special register correctly. |
|   rsil r1, 0..15 | saves old PS INTLEVEL into r1 and mask all PS INTLEVEL <= level (0..15). |
|   xsr  | Exchange Special register |
|   entry sp size | It will create space in stack frame with size bytes |


---

# Registers
## a0
Hold return address. When your function calls another function. This register holds the address of caller function.
```
call0 my_func   ; Call function -> CPU jumps to my_func
                 ; and automatically saves return address (next instruction)
                 ; into register a0
```
## a1
Stack Pointer

## a2-a7
Incoming arguments.
Used to pass arguments to functions and for temporary storage.

## a8
Static chain register. 
Static chain register (used to hold the static chain pointer for nested functions).
If nested functions are not used, this register is treated as a temporary.
a8 holds the address of outer function's stack frame.

## a12 - a15
Callee-saved.
The function you call (the callee) must ensure that this register has the same value when it returns as it did when it was called.

## a15
Points to fixed position at current function's stack frame.

## INTENABLE
Interrupt enable mask.
There is one bit for each level-1 and high-priority interrupt, except non-maskable interrupt (NMI) and Debug interrupt.

## INTERRUPT
This register shows which interrupts are currently pending or active.

## INTCLEAR
Manually clearing pending interrupt.

## INTSET
Manually set pending interrupt.

## CCOUNT
It is a special register inside the Xtensa CPU core that counts every CPU clock cycle since reset.

## CCOMPARE0-CCOMPARE2
Compare value of CCOUNT with value stored inside CCOMPARE register. When CCOUNT == CCOMPARE0, it fires level 1 interrupt to CPU.

## PS
It’s a 32-bit special register that stores the current processor state.
Layout - 
```
PS.INTLEVEL → INTLEVEL (Current interrupt level (0–15). Higher = more privileged)
PS.EXCM     → Exception mode flag. (1 = CPU is inside an exception or interrupt).
PS.UM         User vector mode. (0 - Kernel Mode, 1 - User mode)
PS.RING       Defines what kind of code is executing, kernel or user code. 
PS.OWB        ESP8266 (Xtensa LX106) has 64 registers but only 16 registers are visible.
              After each function call (nested), it shifts window by 8 registers.
              On interrupt or function call, Current Window context (index) is saved into OWB.
              ESP8266 is based on call0 and not on Window ABI.
PS.CALLINC    When new function is called, CPU looks at PS.CALLINC to know how far to move the window base.
              If CALLINC value is 2 and current windows shows a0-a15 registers, then new will be (2 * 4 = 8) a8a-23 registers.
PS.WOE        Window Overflow Enable.
```


# CPU Clock Frequency

When ESP8266 comes out of Boot rom, its CPU frequency is 52MHz.
Frameworks like ESP8266_FREERTOS and Platformio `ets_update_cpu_frequency(uint32_t freq)` function which is defined at `0x40002f04`.
We can use this function by flashing bin file provided by Esp8266 SDK at location `0x40000000`.
But right now we are not using external bin file, so our CPU frequency is just 52MHz.


# DPORT 
Dport provideds bridge between CPU and Peripherals.
DPORT_BASE → 0x3FF000000
EDGE_INT_ENABLE_REG → (DPORT_BASE + 0x04)
```
BIT(0) → WDT Interrupt Enable/Disable.
BIT(1) → FRC1 Timer Interrupt Enable/Disable.
// more bits are unknown.
```

DPORT_CTRL_REG → (DPORT_BASE + 0x14)
```
BIT(0) → If set, double CPU clock.
```



# I/O

* Address range: `0x60000000` → `0x60001200`

## UART

* **UART0** → Starts at `0x60000000`, size `0x80`
* **UART1** → Starts at `0x60000F00`, size `0x80`

- If we do not set baud rate, then by default baud rate of ESP8266 is 74880.


UART_BASE        →  0x60000000
UART_FIFO_REG    →  (UART_BASE + 0x0)
                    We can read 8 LSB while masking other bits.
                    Masking other bits remove garbage values.

UART_INT_RAW     →  (UART_BASE + 0x4)
                    This is RAW interrupt register.
                    Unmasked interrupts are visible in this.
```
BIT(0)  →   RX FIFO Full Interrupt.
BIT(1)  →   TX FIFO Empty Interrupt.
BIT(2)  →   PARTITY Error Interrupt. 
BIT(3)  →   FRAME Error Interrupt.
BIT(4)  →   RX FIFO Overflow Interrupt.
BIT(5)  →   DATA SET READY CHANGE Interrupt. Interrupt when DSR signal changes. DSR is used by old-school RS232 devices to tell CPU when it is ready to communicate.
BIT(6)  →   CLEAR TO SEND CHANGE Interrupt. Interrupt when CTS signal changes. CTS is used when devices is ready to receive data.
BIT(7)  →   BREAK DETECTED Interrupt. When device remains low for too long.
BIT(8)  →   RX FIFO TIMEOUT Interrupt.
```

UART_INT_ST     →  (UART_BASE + 0x8)
                   This is masked interrupt register. 
                   This is basically what CPU sees if enabled.
                   This register has similar bits as of UART_INT_RAW

UART_INT_ENA    →  (UART_BASE + 0xC)
                   Enabling masked interrupts.
                   If not enabled, interrupt remains till Hardware and CPU doesn't those interrupts.
```
BIT(0)  →   ENABLE FIFO FULL INT 
BIT(1)  →   ENABLE TX FIFO EMPTY INT
BIT(2)  →   ENABLE PARITY ERROR INT
BIT(3)  →   ENABLE FRAME ERROR INT
BIT(4)  →   ENABLE RX FIFO OVERFLOW INT
BIT(5)  →   ENABLE DST CHANGE INT
BIT(6)  →   ENABLE CTS CHANGE INT
BIT(7)  →   ENABLE BREAK DETECTED INT
BIT(8)  →   ENABLE RX FIFO TIMEOUT INT
```

UART_INT_CLR    →  (UART_BASE + 0x10) 
```
BIT(0)  →   CLEAR FIFO FULL INT 
BIT(1)  →   CLEAR TX FIFO EMPTY INT
BIT(2)  →   CLEAR PARITY ERROR INT
BIT(3)  →   CLEAR FRAME ERROR INT
BIT(4)  →   CLEAR RX FIFO OVERFLOW INT
BIT(5)  →   CLEAR DST CHANGE INT
BIT(6)  →   CLEAR CTS CHANGE INT
BIT(7)  →   CLEAR BREAK DETECTED INT
BIT(8)  →   CLEAR RX FIFO TIMEOUT INT
```

UART_CLKDIV     →  (UART_BASE + 0x14)   
                   It is used for Baud rate generator which helps in converting SysClk into lower CLK for UART.
                   For Example your SysClk is 80Mhz or 80000000 and you want baud rate of 57600. Then you do - 
                   80000000 / (16 * 57600) = 86.8056 or 87. You set this 87 into UART_CLKDIV.
                   Now after every 87 SysClk cycles, it will tick 1 for UART.
                   Mask to set value to this register is 0x000FFFFF.

UART_AUTOBAUD   →  (UART_BASE + 0x18) 
                   AutoBaud automatically detects baud rate of incoming data.
```
BIT(0)          →  Enabling AutoBaud
                   UART_GLITCH_FILT is basically a filter which allow MCU to ignore short spikes of data.
                   For example if there is sudden rise and flow in signal then MCU will ignore it, without considering it a valid bit.
                   UART_GLITCH_FILT is at 8 bits shift from LSB in UART_AUTOBAUD.
                   MASK for UART_GLITCH_FILT is 0x000000FF. 00 means no filtering. 05, ignore pulse shorter than 5 clock cycles. 
                   FF, ingore pulse shorter than 257.
```

UART_STATUS     → (UART_BASE + 0x1C)
```
BIT(0)-BIT(7)   → Stores Number of Bytes currently in RX FIFO Register. RX_CNT
BIT(13)         → State of Data Set Ready pin.   
BIT(14)         → State of Clear to Send pin.   
BIT(15)         → State of RXD Pin.
BIT(16)-BIT(23) → Stores Number of Bytes currently in TX FIFO Register. TX_CNT 
BIT(29)         → Shows the current state of the DTR control pin.
BIT(30)         → Shows the current state of the RTS hardware flow control pin.
BIT(31)         → State of TXD Pin.
```

UART_CONF0      → (UART_BASE + 0x20)
```
BIT(0)          → Parity Type. 0 - Even, 1 - Odd.
BIT(1)          → Parity Enable.
BIT(2)-BIT(3)   → Word Length. 00 - 5 Bits, 01 - 6 Bits, 10 - 7 Bits, 11 - 8 Bits.
BIT(4)-BIT(5)   → Stop Bit. 01 - 1 Stop Bit time. 10 - 1.5 stop bits time. 11 - 2 stop bits time.
BIT(6)          → Software driven RTS.
BIT(7)          → Software driven DTR.
BIT(8)          → TX Break. Hold 0 continously to create break condition. 
BIT(9)          → UART_IRDA_DPLX 
BIT(10)         → UART_IRDA_TX_EN 
BIT(11)         → UART_IRDA_WCTL 
BIT(12)         → UART_IRDA_TX_INV
BIT(13)         → UART_IRDA_RX_INV 
BIT(14)         → Connects TX → RX internally, useful for self-test/debug.
BIT(15)         → Enables automatic hardware flow control (uses RTS/CTS).
BIT(16)         → UART_IRDA_EN
BIT(17)         → RST RX FIFO Buffer. When sets to 1.
BIT(18)         → RST TX FIFO BUffer.
```
                
For Inverted Logics. (idle = low, start bit = high, etc).
```
BIT(19)         → RXD INV
BIT(20)         → CTS INV
BIT(21)         → DSR INV
BIT(22)         → TXD INV
BIT(23)         → RTS INV
BIT(24)         → DTR INV
```

UART_CONF1      → (UART_BASE + 0x24)
```
BIT(0)-BIT(6)   → RX FIFO FULL THRESHOLD 
BIT(8)-BIT(14)  → TX FIFO EMPTY THRESHOLD 
BIT(16)-BIT(22) → RX FLOW THRESHOLD. When to stop asking trasmitter to stop sending bytes.
BIT(23)         → RX FLOW ENABLE 
BIT(24)-BIT(30) → RX TIMEOUT THRESHOLD. How many bit times (or internal clocks, depending on the UART design) to wait after last RX edge before declaring timeout. 
BIT(31)         → RX TIMEOUT ENABLE
```

UART_LOWPULSE   → (UART_BASE + 0x28)
                  Used by AutoBaud register. Stores the minimum duration (in UART clock cycles) of the low-level pulse seen on RX since autobaud started. 
                  The counter increments using the UART clock.
                  Example:
                      SysClk = 80 MHz → 12.5 ns per cycle.
                      If the low pulse lasted 8680 cycles → 8680 × 12.5 ns ≈ 108 µs.
                      That’s about 1 bit-time at 9600 baud.
                  MASK For UART_LOWPULSE - 0x000FFFFF.

UART_HIGHPULSE  → (UART_BASE + 0x2C)

UART_PULSE_NUM  → (UART_BASE + 0x30) 
                  Holds the number of pulses counted in the current autobaud measurement.
                  MASK - 0x0003FF 

UART_DATE       → (UART_BASE + 0x78)
UART_ID         → (UART_BASE + 0x7C)

---

## SPI
* **SPI0** → Starts at `0x60000200`, size `0x100`
* **SPI1** → Starts at `0x60000100`, size `0x100`

SPI0_BASE        →  0x60000200

SPI0_CMD         →  (SPI0_BASE + 0x00)
`BIT(18)         →  User-Defined SPI transaction`
```
BIT(20)          →  Read Electronic Signature
BIT(22)          →  Chip Erase
BIT(23)          →  Block Erase
BIT(24)          →  Sector Erase 
BIT(25)          →  Page Program 
BIT(26)          →  Write Status Register 
BIT(27)          →  Read Status Register 
BIT(28)          →  Read JEDEC ID
BIT(29)          →  Write Disable Flash 
BIT(30)          →  Write Enable Flash 
BIT(31)          →  Read From Flash 
```

SPI0_ADDR        →  (SPI0_BASE + 0x04)
                    Holds a 24-bit flash address for read/write/erase operations.

SPI0_CTRL        →  (SPI0_BASE + 0x08)
```
BIT(13)          →  Fast Read Mode
BIT(14)          →  Dual Output
BIT(20)          →  Quad Output
BIT(23)          →  Dual I/O Mode
BIT(24)          →  Quad I/O Mode
BIT(25)          →  Read BIT Order (LSB First)
BIT(26)          →  Write BIT Order (LSB First)
```

SPI0_CTRL1        →  (SPI0_BASE + 0x0C)
```
BIT(28)-BIT(31)  →  CS Hold Delay. It is 4 bits value (0xF).
                    This sets how long Chip Select (CS) stays asserted (LOW) after finishing a SPI transaction.
BIT(16)-BIT(27)  →  This is a resolution divider or prescaler for the CS hold timing. It is 12 bits value (0xFFF).
```

SPI0_RD_STATUS   →  (SPI0_BASE + 0x10)
                    When in Slave Mode, It acts as a status register that the SPI master can read from the slave. 
                    When in Master Mode, It contains status received from the external device.

SPI0_CTRL2       →  (SPI0_BASE + 0x14)
```
BIT(16)-BIT(17)  →  MISO Signals are delayed relative to SPI Clock. 0 - No Delay, 1 - Half Cycle, 2 - One Cycle.
BIT(18)-BIT(20)  →  MISO Signals are delayed by 80MHz clock cycle. 
BIT(21)-BIT(22)  →  MOSI Signals are delayed relative to SPI Clock. 0 - No Delay, 1 - Half Cycle, 2 - One Cycle.
BIT(23)-BIT(25)  →  MOSI Signals are delayed by 80MHz clock cycle.
BIT(26)-BIT(27)  →  SPI CS Signal is delayed relative to SPI Clock. 0 - No Delay, 1 - Half Cycle, 2 - One Cycle.
BIT(28)-BIT(31)  →  SPI CS Signal are delayed by 80MHz clock cycle.
```

SPI0_CLK         →  (SPI0_BASE + 0x18)
```
BIT(0)-BIT(5)    →  (spi_clkcnt_L)In the master mode, it must be eqaul to spi_clkcnt_N. In the slave mode, it must be 0. It defines how long clock stays LOW.
BIT(6)-BIT(11)   →  (spi_clkcnt_H) In the master mode, it must be floor((spi_clkcnt_N+1)/2-1). In the slave mode, it must be 0. It defines how long clock stays HIGH.
BIT(12)-BIT(17)  →  In the master mode, it is the divider of spi_clk. So spi_clk frequency is 80MHz/(spi_clkdiv_pre+1)/(spi_clkcnt_N+1).
BIT(18)-BIT(30)  →  In the master mode, it is pre-divider of spi_clk. 
BIT(31)          →  In the master mode, 1: spi_clk is eqaul to 80MHz, 0: spi_clk is divided from 80 MHz clock.
```
SPI0_USER        → (SPI0_BASE + 0x1C)
```
BIT(6)           →  (spi_ck_i_edge) Slave mode: 1 = rising edge, 0 = falling edge.
BIT(10)          →  (spi_rd_byte_order) MISO byte order: 1 = little-endian, 0 = big-endian.
BIT(11)          →  (spi_wr_byte_order) MOSI/command/address byte order: 1 = little-endian, 0 = big-endian.
BIT(12)          →  (spi_fwrite_dual) Read-data phase uses 2 signals.
                    Here MOSI becomes IO0 and MISO becomes IO1.
BIT(13)          →  (spi_fwrite_quad) Read-data phase uses 4 signals.
                    Here two additional data pins are added IO2 and IO3.
                    In both Dual and Quad mode, SPI works in Half Duplex.
BIT(14)          →  (spi_fwrite_dio) Write operation uses 2 signals for address + read-data phases.
BIT(15)          →  (spi_fwrite_qio) Write operation uses 4 signals for address + read-data phases.
BIT(16)          →  (spi_sio) 1: MOSI and MISO share the same pin (single-wire mode).
BIT(24)          →  (reg_usr_miso_highpart) Read-data phase uses only high buffer (spi_w8 ~ spi_w15).
BIT(25)          →  (reg_usr_mosi_highpart) Write-data phase uses only high buffer (spi_w8 ~ spi_w15).
BIT(27)          →  (spi_usr_mosi) Enables the "write-data" phase (data sent on MOSI).
BIT(28)          →  (spi_usr_miso) Enables the "read-data" phase (data received on MISO).
BIT(29)          →  (spi_usr_dummy) Enables the "dummy" phase used for read timing alignment.
BIT(30)          →  (spi_usr_addr) Enables the "address" phase of the transaction.
                    For flash reads/writes you normally set this to 1 and write the 24 or 32 bit address into the address register(s) before starting the transaction.
BIT(31)          →  (spi_usr_command) Enables the "command" phase of an SPI transaction.
```

SPI0_USER1       → (SPI0_BASE + 0x20)
```
BIT(0)–BIT(7)     →  (reg_usr_dummy_cyclelen) Number of dummy cycles during the dummy phase. Value stored = (cycle_count - 1).
BIT(8)–BIT(16)    →  (reg_usr_miso_bitlen) Length (in bits) of the "read-data" (MISO) phase. Value stored = (number_of_bits - 1).
BIT(17)–BIT(25)   →  (reg_usr_mosi_bitlen) Length (in bits) of the "write-data" (MOSI) phase. Value stored = (number_of_bits - 1).
BIT(26)–BIT(31)   →  (reg_usr_addr_bitlen) Length (in bits) of the "address" phase. Value stored = (number_of_bits - 1). 
```

SPI0_USER2        →  (SPI0_BASE + 0x24)
```
BIT(0)-BIT(15)    →  The value of "command" phase.
BIT(28)-BIT(31)   →  The length in bits of "command" phase. The register value shall be (bit_num-1).
```

SPI0_WR_STATUS    →  (SPI0_BASE + 0x28)
```
BIT(0)-BIT(31)    →  In the slave mode, this register are the status register for the master to write into
```

SPI0_PIN    →  (SPI0_BASE + 0x2C)
```
BIT(0)      →  1: disable CS0; 0: spi_cs signal is from/to CS0 pin
BIT(1)      →  1: disable CS1; 0: spi_cs signal is from/to CS1 pin
BIT(2)      →  1: disable CS0; 0: spi_cs signal is from/to CS0 pin
```

SPI0_SLAVE        →  (SPI0_BASE + 0x30)
```
BIT(0)            →  (slv_rd_buf_done) Interrupt raw bit for completion of "read-buffer" operation (slave mode).
                     Master set this bit to 1 after completing read operation.
BIT(1)            →  (slv_wr_buf_done) Interrupt raw bit for completion of "write-buffer" operation (slave mode).
BIT(2)            →  (slv_rd_sta_done) Interrupt raw bit for completion of "read-status" operation (slave mode).
BIT(3)            →  (slv_wr_sta_done) Interrupt raw bit for completion of "write-status" operation (slave mode).
BIT(4)            →  (spi_trans_done) Interrupt raw bit for completion of any SPI operation (valid in both master & slave modes).
                     Transaction starts when CS goes LOW and it ends when CS goes HIGH. 
BIT(5)–BIT(9)     →  (spi_int_en) Interrupt enable bits for the above 5 source (slv_rd_buf_done, slv_wr_buf_done, slv_rd_sta_done, slv_wr_sta_done, spi_trans_done).
BIT(23)–BIT(26)   →  (spi_trans_cnt) Read-only operation counter (counts SPI transactions).
BIT(27)           →  (slv_cmd_define)
                     1: Slave-mode command codes come from SPI_SLAVE3.
                     0: Slave-mode commands are fixed:
                        1 = write-status
                        4 = read-status
                        2 = write-buffer
                        3 = read-buffer
BIT(30)           →  (spi_slave_mode)
                     1: SPI runs in slave mode.
                     0: SPI runs in master mode.
BIT(31)           →  (spi_sync_reset) Synchronous reset of the SPI module. Write 1 → module resets → bit auto-clears.
```

SPI0_SLAVE1       → (SPI0_BASE + 0x34) 
```
BIT(0)            →  (slv_rdbuf_dummy_en) Enable bit for the "dummy" phase in read-buffer operations (slave mode).
BIT(1)            →  (slv_wrbuf_dummy_en) Enable bit for the "dummy" phase in write-buffer operations (slave mode).
BIT(2)            →  (slv_rdsta_dummy_en) Enable bit for the "dummy" phase in read-status operations (slave mode).
BIT(3)            →  (slv_wrsta_dummy_en) Enable bit for the "dummy" phase in write-status operations (slave mode).
BIT(4)–BIT(9)     →  (slv_wr_addr_bitlen) Address length (in bits) for **write-buffer** operations (slave mode) Register value = (bit_num - 1).
BIT(10)–BIT(15)   →  (slv_rd_addr_bitlen) Address length (in bits) for **read-buffer** operations (slave mode) Register value = (bit_num - 1).
BIT(16)–BIT(24)   →  (slv_buf_bitlen) Data length (in bits) for **write-buffer** and **read-buffer** operations (slave mode) Register value = (bit_num - 1).
BIT(27)–BIT(31)   →  (slv_status_bitlen) Status length (in bits) for **write-status** and **read-status** operations (slave mode) Register value = (bit_num - 1).
```

SPI0_SLAVE2       → (SPI0_BASE + 0x38)
```
BIT(0)-BIT(7)     → In the slave mode, it is the length in spi_clk cycles of "dummy" phase for "read-status" operations. The register value shall be (cycle_num-1)
BIT(8)-BIT(15)    → In the slave mode, it is the length in spi_clk cycles of "dummy" phase for "write-status" operations. The register value shall be (cycle_num-1)
BIT(16)-BIT(23)   → In the slave mode, it is the length in spi_clk cycles of "dummy" phase for "read-buffer" operations. The register value shall be (cycle_num-1
BIT(24)-BIT(31)   → In the slave mode, it is the length in spi_clk cycles "dummy" phase for "write-buffer" operations. The register value shall be (cycle_num-1)
```

SPI0_SLAVE3       → (SPI0_BASE + 0x3C)
```
BIT(0)-BIT(7)     → In slave mode, it is the value of "read-buffer" command
BIT(8)-BIT(15)    → In slave mode, it is the value of "write-buffer" command
BIT(16)-BIT(23)   → In slave mode, it is the value of "read-status" command
BIT(24)-BIT(31)   → In slave mode, it is the value of "write-status" command
```

SPI0_W0 - SPI0_W15 → (SPI0_BASE + 0x40) - (SPI0_BASE + 0x7C)
The data buffer inside SPI module. There are 64byte, i.e., 16 words. Note that only 32bit accessing are supported.

SPI0_EXT3         → (SPI0_BASE + 0xFC)
```
BIT(0)-BIT(1)     → This register is for two SPI masters to share the same cs, clock and data signals.
```
---               
                  
## GPIOs          
                  
| GPIO   | Pin |  Function     |
| ------ | --- |  ------------ |
| GPIO0  | 15  |  GPIO0\_U     |
| GPIO1  | 26  |  U0TXD\_U     |
| GPIO2  | 14  | GPIO2\_U     |
| GPIO3  | 25  | U0RXD\_U     |
| GPIO4  | 16  | GPIO4\_U     |
| GPIO5  | 24  | GPIO5\_U     |
| GPIO6  | 21  | SD\_CLK\_U   |
| GPIO7  | 22  | SD\_DATA0\_U |
| GPIO8  | 23  | SD\_DATA1\_U |
| GPIO9  | 18  | SD\_DATA2\_U |
| GPIO10 | 19  | SD\_DATA3\_U |
| GPIO11 | 20  | SD\_CMD\_U   |
| GPIO12 | 10  | MTDI\_U      |
| GPIO13 | 12  | MTCK\_U      |
| GPIO14 | 9   | MTMS\_U      |
| GPIO15 | 13  | MTDO\_U      |

### Boot Function Notes

* **GPIO0** → HIGH: Flash Boot, LOW: UART Flashing
* **GPIO2** → HIGH: Flash Boot, LOW: Boot fails
* **GPIO15** → HIGH: Boot fails, LOW: Flash Boot

### Special Case: GPIO16

* Belongs to RTC module (not general GPIO).
* Can **wake from deep-sleep**, configurable as input/output.
* Cannot trigger IO interrupts.

---

## GPIO Control

Base address:
`GPIO_BASE = 0x60000300`

### Registers

```text
GPIO_OUT_W1TS    (BASE + 0x04) → Set HIGH
GPIO_OUT_W1TC    (BASE + 0x08) → Set LOW

GPIO_ENABLE_W1TS (BASE + 0x10) → Set as OUTPUT
GPIO_ENABLE_W1TC (BASE + 0x14) → Set as INPUT (Hi-Z)

GPIO_IN_ADDRESS  (BASE + 0x18) → Read actual pin states
  [0-15]  = GPIO states
  [16-31] = Strapping (boot mode)

GPIO_STATUS_ADDRESS (BASE + 0x1C) → Interrupt pending status  
GPIO_STATUS_ADDRESS_W1TS (BASE + 0x20) → Atomic set  
GPIO_STATUS_ADDRESS_W1TC (BASE + 0x24) → Atomic clear  
```

### Pin Configuration Registers

Each pin has its own register with the same layout.

```text
BIT0         Source (1 = Peripheral, 0 = GPIO)
BIT2         Driver (1 = Open Drain, 0 = Push-Pull)
BIT7–BIT9    INT_TYPE (edge/level config)
BIT10        WAKEUP ENABLE
BIT11–BIT12  Extra config (mux / open-drain)
```

Registers (BASE = `GPIO_BASE`):

```
PIN0  → BASE + 0x28
PIN1  → BASE + 0x2C
...
PIN15 → BASE + 0x64
```

---

## IOMUX Pin Registers

* Range: `0x60000804` → `0x60000843`
* Base: `0x60000800`

### Register Layout

```text
BIT0 → Output Enable
BIT1 → Output Enable During Sleep
BIT2 → Pull Down During Sleep
BIT3 → Pull Up During Sleep
BIT6 → Pull Down
BIT7 → Pull Up
BIT4, BIT5, BIT8 → Function Select
```

### Example: GPIO2 as UART0\_TXD

```c
SET_PERI_REG_MASK(PIN_NAME, 256)
```

---

## PAD\_XPD\_DCDC\_CONF (GPIO16 Special)

* **XPD\_DCDC** = External Power Down, DC-DC regulator control
* Allows GPIO16 to control internal voltage regulator

RTC Base: `0x60000700`

```text
RTC_GPIO_OUT      (BASE + 0x068) → Output (like GPIO_OUT_W1TS)
RTC_GPIO_ENABLE   (BASE + 0x074) → Output Enable
RTC_GPIO_IN_DATA  (BASE + 0x08C) → Input state
RTC_GPIO_CONF     (BASE + 0x090) → Unknown
PAD_XPD_DCDC_CONF (BASE + 0x0A0) 
   BIT0-1: Function (01 = Normal GPIO, 00 = XPD_DCDC)
```

## Timer Registers

TIME_BASE: `0x60000600`

FRC1 →  (TIME_BASE + 0x0)
        (Intitial Counter value)
```
BIT(0)-BIT(22) → Initial value of counter
                 Mask - 0x007FFFFF
```

FRC1_COUNT → (TIME_BAE + 0x04)
```
BIT(0)-BIT(22) → Current value of counter
                 Mask - 0x007FFFFF
```

FRC1_CTRL → (TIME_BASE + 0x08)
```
BIT(0)          → Interrupt type, 0:edge, 1:level
BIT(1)          →   
BIT(2)-BIT(3)   → Prescale-divider. 0: divided by 1, 1: divided
                  by 16, 2 or 3: divided by 256
BIT(4)          →
BIT(5)          →
BIT(6)          → Automatically reload, when the counter is
                  equal to zero.
BIT(7)          → Timer enable.
BIT(8)          → Timer interrupt flag. (Not exactly know what it does)
```

FRC1_INT → (TIME_BASE + 0x0c)
```
BIT(0) → Set when timer expires.
```

FRC2 →  (TIME_BASE + 0x20)
        (Intitial Counter value)
```
BIT(0)-BIT(22) → Initial value of counter
                 Mask - 0x007FFFFF
```

FRC2_COUNT → (TIME_BAE + 0x24)
```
BIT(0)-BIT(22) → Current value of counter
                 Mask - 0x007FFFFF
```

FRC2_CTRL → (TIME_BASE + 0x28)
```
BIT(0)-BIT(7) → Control bits 
                 Mask - 0x000000FF
BIT(8)        → Timer interrupt flag
```

FRC2_INT → (TIME_BASE + 0x2c)
```
BIT(0) → Set when timer expires. 
```
FRC2_ALARM → (TIME_BASE + 0x30)
```
BIT(0) - BIT(31) → Alarm value.
                   Mask - 0xFFFFFFFF
                   When FRC2 counter starts from LOAD value, it get increment 
                   and when it reaches value stored in FRC2_ALARM, interrupt is triggered.
```

# Interrupt related info (from ESP8266 RTOS)
```
/* interrupt related */
#define ETS_SLC_INUM        1
#define ETS_SPI_INUM        2
#define ETS_GPIO_INUM       4
#define ETS_UART_INUM       5
#define ETS_MAX_INUM        6
#define ETS_SOFT_INUM       7
#define ETS_WDT_INUM        8
#define ETS_FRC_TIMER1_INUM 9
#define ETS_INT_MAX         14
```


# Setting CPU Frequency in ESP8266 
found this code on internet -
```
    if(rom_i2c_readReg(103,4,1) != 136) { // 8: 40MHz, 136: 26MHz
        //if(get_sys_const(sys_const_crystal_26m_en) == 1) { // soc_param0: 0: 40MHz, 1: 26MHz, 2: 24MHz
            // set 80MHz PLL CPU
            rom_i2c_writeReg(103,4,1,136);
            rom_i2c_writeReg(103,4,2,145);
        //}
    }
```
After finding`rom_i2c_writeReg` and `rom_i2c_readReg` in ESP8266 SDK compiled ELF file and disassmbling it using ghidra, I found that it access `0x60000D10` register. And modify this register like this - 
```
#define REG 0x60000D10

volatile uint32_t *reg = (volatile uint32_t *)REG;

int main(){
	*reg = 0x1880167;
	do {
		__asm__ __volatile__("memw");
	} while ((*reg & 0x2000000) != 0);
	*reg = 0x1910267;
	do {
		__asm__ __volatile__("memw");
	} while ((*reg & 0x2000000) != 0);
}
```


# References
https://dl.espressif.com/github_assets/espressif/xtensa-isa-doc/releases/download/latest/Xtensa.pdf
https://www.espressif.com/sites/default/files/documentation/esp8266-technical_reference_en.pdf?utm_source
https://github.com/esp8266/esp8266-wiki/wiki/Memory-Map
https://github.com/espressif/ESP8266_RTOS_SDK/tree/d412ac601befc4dd024d2d2adcfaa319c7463e36
