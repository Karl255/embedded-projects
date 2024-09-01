#include <avr/interrupt.h>
#include <init.h>
#include <control.h>

void init(void) {
	DDRB =
		1 << PB4 | // output for OC1B; R
		0 << PB2 | // input with INT0 for IR receiver
		1 << PB1 | // output for OC0B; B
		1 << PB0; // output for OC0A; G

	TCCR0A =
		0b10 << COM0A0 | // PWM on OC0A, non-inverting mode
		0b10 << COM0B0 | // PWM on OC0B, non-inverting mode
		0b01 << WGM00; // phase correct PWM mode (halves frequency)

	TCCR0B = 0b010 << CS00; // Timer 0 = CLK / 8 (/ 2) = ~2 kHz PWM

	// dual use of Timer 1: PWM + ticking software timer to measure IR pulses
	TCCR1 = 0b0001 << CS10; // Timer 1 = CLK = ~32 kHz PWM
	GTCCR = 1 << PWM1B | 0b10 << COM1B0; // PWM mode

	PWM_R = 0; // OCR0B
	PWM_G = 0; // OCR1B
	PWM_B = 0; // OCR0A

	MCUCR = 0b01 << ISC00; // INT0 triggers on both edges
	GIMSK = 1 << INT0; // enable INT0

	TIMSK = 1 << TOIE1 | 1 << TOIE0; // enable timer 0 and timer 1 overflow interrupts
}
