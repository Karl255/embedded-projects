#pragma once

/*
PB0 = DS1302 CLK
PB1 = DS1302 DATA
PB2 = DS1302 CE
PB3 = SPI MOSI
PB4 = SPI MISO
PB5 = SPI SCK
PB6 = rotary encoder CLK
PB7 = rotary encoder DATA

PC0 = digit 0
PC1 = digit 1
PC2 = digit 2
PC3 = digit 3
PC4 = rotary encoder PUSH
PC5 = NC

PDx = SEGMENT x
*/

// NOTE: check avr-ds1302 library code for pin DS1302 pin initialization

#define initDDRB() (DDRB = 0b00000000)
#define initDDRC() (DDRC = 0b001111)
#define initDDRD() (DDRD = 0xff)

#define readRotaryClock() ((PINB & (1 << PB6)) >> PB6)
#define readRotaryData() ((PINB & (1 << PB7)) >> PB7)
#define readRotaryPush() ((PINC & (1 << PC4)) >> PC4)

#define setDigitsOn(digits) (PORTC = (PORTC & 0xf0) | ((digits) & 0x0f))
#define setSegmentsOn(segments) (PORTD = ~(segments))

#define DS1302_CLK        PB0
#define DS1302_CLK_DDR    DDRB
#define DS1302_CLK_PORT   PORTB

#define DS1302_DIO        PB1
#define DS1302_DIO_DDR    DDRB
#define DS1302_DIO_PORT   PORTB
#define DS1302_DIO_PIN    PINB

#define DS1302_CE         PB2
#define DS1302_CE_DDR     DDRB
#define DS1302_CE_PORT    PORTB
