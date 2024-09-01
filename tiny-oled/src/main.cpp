#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <TinyI2C.h>
#include "graphics.h"
#include "ssd1306.h"

#define OLED_ADDRESS 0x3C

const char str[] PROGMEM =
	"HELLO DLROW!    "
	"                "
	" !!  !!  !!  !! "
	"!  !!  !!  !!  !"
	"!!!!!!!!!!!!!!!!"
	"!!!!!!!!!!!!!!!!"
	"!  !!  !!  !!  !"
	" !!  !!  !!  !! ";

volatile uint8_t adcFlag = 0;
uint8_t digits[4];

uint8_t spriteTable[SCREEN_SIZE];
uint8_t spriteAttributeTable[SCREEN_SIZE / 2];

void initAdc(void);
uint16_t readAdc(void);

int main(void) {
	initAdc();
	TinyI2C.init();
	
	sei();
	
	initializeOled(OLED_ADDRESS);
	
	stringToSprites(str, spriteTable);
	for (size_t i = 0; i < SCREEN_SIZE / 2; i++) {
		spriteAttributeTable[i] = 0x11;
	}
	
	init7SegmentSprites(spriteTable, spriteAttributeTable, 32);
	init7SegmentSprites(spriteTable, spriteAttributeTable, 36);
	init7SegmentSprites(spriteTable, spriteAttributeTable, 40);
	init7SegmentSprites(spriteTable, spriteAttributeTable, 44);
	
	spriteAttributeTable[3] = 0x77;
	spriteAttributeTable[4] = 0x77;
	spriteAttributeTable[5] = 0x71;
	
	digits[0] = 1;
	digits[1] = 2;
	digits[2] = 3;
	digits[3] = 4;
	
	while (1) {
		uint10ToDigits(readAdc(), digits);
		
		set7SegmentAttributes(spriteAttributeTable, digits[3], 32);
		set7SegmentAttributes(spriteAttributeTable, digits[2], 36);
		set7SegmentAttributes(spriteAttributeTable, digits[1], 40);
		set7SegmentAttributes(spriteAttributeTable, digits[0], 44);
		
		renderToOled(OLED_ADDRESS, spriteTable, spriteAttributeTable);
		
		_delay_ms(50);
	}
	
	return 0;
}

void initAdc(void) {
	ADMUX = 0 << MUX3 | 0 << MUX2 | 1 << MUX1 | 1 << MUX0; // select ADC3 input and leave it there
	
	ADCSRA = 0
		| 1 << ADEN // enable ADC
		| 1 << ADIE; // enable ADC done interrupt
		
	DIDR0 = 1 << ADC3D; // disable digital input on PB3/ADC3
	
}

uint16_t readAdc(void) {
	adcFlag = 1;
	ADCSRA |= 1 << ADSC;
	
	while (adcFlag);
	
	return ADC;
}

ISR(ADC_vect) {
	adcFlag = 0;
}
