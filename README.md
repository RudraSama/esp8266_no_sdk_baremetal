# ESP8266 No-SDK Framework
A lightweight framework for experimenting with the ESP8266 architecture without using the official SDK.
This project is designed for learning purposes — to understand the ESP8266 memory map, UART, interrupts, and peripheral handling at the bare-metal level.

## Requirements
- Xtensa lx106 toolchain. [Link](https://dl.espressif.com/dl/xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz)
- Esptool.

## Build
`make <project_name>`
- use V=1 with make for verbose.
## clean
`make clean`

## Elf2Image
`esptool --chip esp8266 elf2image build/firmware.elf`

## Flashing
`esptool --port /dev/ttyUSB0 write-flash 0x00000 build/firmware.elf-0x00000.bin`

## NOTE
- This is for experimenting with ESP8266's architecture so most of the functionality will not work.
- This is basic framework so we can't use SPI flash to execute program in ESP8266. (Or maybe I am too dump to make it work)
- To learn about memmory mapping and register mapping of ESP8266, read docs.md file.
