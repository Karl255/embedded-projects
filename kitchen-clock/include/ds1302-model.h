#pragma once

#include <stdint.h>

/** Values are in BCD encoding (per nibble) unless explicitly specified otherwise. */
typedef union {
	struct {
		/** Bit 7 is clock halt. */
		uint8_t seconds;
		uint8_t minutes;
		/** Upper nibble is either: 00xx in BCD in 24-hour format or 10Px in 12-hour format where P denotes AM (0) or PM (1) */
		uint8_t hours;
		uint8_t day;
		uint8_t month;
		uint8_t dayOfWeek;
		uint8_t year;
		/** Only contains the write protect flag in bit 7. */
		uint8_t writeProtect;
	};
	uint8_t raw[8];
} DS1302Clock;

// TODO: use C++ features

uint8_t DS1302Clock_equals(DS1302Clock& a, DS1302Clock& b);
void DS1302Clock_copy(DS1302Clock& destination, DS1302Clock& source);
