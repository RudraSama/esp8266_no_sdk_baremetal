

````markdown
# Compiling Source

```bash
xtensa-lx106-elf-as -o crt0.o crt0.S
xtensa-lx106-elf-gcc -nostdlib -c main.c -o main.o
xtensa-lx106-elf-ld -T linker.ld crt0.o main.o -o firmware.elf
xtensa-lx106-elf-objcopy -O binary firmware.elf firmware.bin
esptool.py --port /dev/ttyUSB0 write_flash 0x00000 firmware.bin
````

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

# CPU Clock Frequency

When ESP8266 comes out of Boot rom, its CPU frequency is 52MHz.
Frameworks like ESP8266_FREERTOS and Platformio `ets_update_cpu_frequency(uint32_t freq)` function which is defined at `0x40002f04`.
We can use this function by flashing bin file provided by Esp8266 SDK at location `0x40000000`.
But right now we are not using external bin file, so our CPU frequency is just 52MHz.


# I/O

* Address range: `0x60000000` → `0x60001200`

## UART

* **UART0** → Starts at `0x60000000`, size `0x80`
* **UART1** → Starts at `0x60000F00`, size `0x80`

- If we do not set baud rate, then by default baud rate of ESP8266 is 74880.


UART_BASE      →  0x60000000
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

## GPIOs

| GPIO   | Pin | Function     |
| ------ | --- | ------------ |
| GPIO0  | 15  | GPIO0\_U     |
| GPIO1  | 26  | U0TXD\_U     |
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

```

---

Do you also want me to **convert the long IOMUX mapping list** (GPIO0 → GPIO15 functions) into a compact table like I did for the GPIO pins?
```

## ESP8266 Startup (Got from Platformio ELF for Esp8266)
_start  -    and a0, a0, a0 (basicall NOP)
        -    execw          (Waits for any exceptions of previously executed instructions to occur)

_user_call_section
        -    l32r a2, 0x40100000      (loading address of _start in a0)
        -    wsr.vecbase a2           (vecbase is Vector Base Register) 
                                      (Telling CPU that all vectors will start from _start)
        -    call0 call_user_start    (call to next stage of boot)

call_user_start
        -  
        -    addi	a1, a1, -16
        -    s32i	a0, a1, 0
        -    call0	4010548c <wdt_feed+0x154>           (starts watchdog)
        -    l32r	a0, 401051b0 <NMI_Handler+0x54>     (No Mask Interrupt Handler)
        -    callx0	a0
        -    l32i	a0, a1, 0
        -    addi	a1, a1, 16
        -    ret


