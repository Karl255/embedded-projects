// based on: https://github.com/afiskon/avr-ds1302/blob/master/main.c

#pragma once

#include <stdint.h>

#define DS1302_DELAY_USEC 3

#define ADDR_SECONDS 0
#define ADDR_MINUTES 2
#define ADDR_HOURS 4
#define ADDR_DAY 6
#define ADDR_MONTH 8
#define ADDR_DOW 10
#define ADDR_YEAR 12
#define ADDR_WRITE_PROTECT 14
#define ADDR_TRICKLE_CHARGE 16
#define ADDR_CLOCK_BURST 0xbe

#define ADDR_RAM 0xc0
#define ADDR_RAM_BURST 0xfe

#define DS1302_WRITE 0x80
#define DS1302_READ 0x81

void DS1302_InitIo(void);

void DS1302_Select(void);

void DS1302_Deselect(void);

void DS1302_TransmitByte(uint8_t byte);

uint8_t DS1302_ReceiveByte(void);
