#include <avr/io.h>

/*
Timer4 OCs:
- PC7 - OC4A
- PC6 - !OC4A
- PB6 - OC4B
- PB5 - !OC4B
- PB7 - OC4D
- PB6 - !OC4D

*/


void init(void) {
	// PLL runs at 96 MHz
	
	PLLCSR |= 0
		| 0 << PINDIV // PLL input prescaler, should be 1 with a 16MHz clock source, but we're cheeky here
		| 1 << PLLE; // PLL enabled
	
	PLLFRQ |= 0
		| 0b01 << PLLTM0 // PLL Postcaler Factor = 2
		| 0b1010 << PDIV0; // PLL output frequency = 96 MHz
	
	OCR4C = 0xff; // count to 255, Timer4 in 8 bit mode (default)
	
	TCCR4A |= 0
		| 0b10 << COM4A0 // in phase-correct PWM mode, connect OC4A pin
		| 1 << PWM4A; // enable PWM mode based on OCR4A comparator
	
	TCCR4B |= 0
		| 0b0001 << CS40; // clock = PCK in asynchoronous mode
	
	TCCR4D |= 0
		| 0b01 << WGM40; // Phase and Frequency Correct PWM, when PWM4x = 1
}

int main() {
	init();
	OCR4A = 127;
	
	for (;;) {
	}
	
	return 0;
}
