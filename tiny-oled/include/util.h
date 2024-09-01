#pragma once

#include <stdint.h>

inline __attribute__ ((always_inline))
uint8_t avr_reverse_byte (uint8_t x)
{
    x = ((x & 0x55) << 1) | ((x & 0xaa) >> 1);
    x = ((x & 0x33) << 2) | ((x & 0xcc) >> 2);

    /* x = ((x & 0x0f) << 4) | ((x & 0xf0) >> 4); */

    __asm__ ("swap %0" : "=r" (x) : "0" (x)); /* swap nibbles. */

    return x;
}

inline __attribute ((always_inline))
void setBitAt(uint8_t* byteAddress, uint8_t n, bool state) {
	uint8_t mask = 1 << n;
	if (state) {
		*byteAddress |= mask;
	} else {
		*byteAddress &= ~mask;
	}
}

inline __attribute ((always_inline))
void uint10ToDigits(uint16_t num, uint8_t digits[4]) {
	digits[0] = num % 10;
	num /= 10;
	digits[1] = num % 10;
	num /= 10;
	digits[2] = num % 10;
	num /= 10;
	digits[3] = num % 10;
}
