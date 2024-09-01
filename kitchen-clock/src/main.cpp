#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "io.h"
#include "ds1302.h"
#include "ds1302-model.h"
#include "mode.h"
#include "digit_segments.h"
#include "bcd.h"

int main(void) {
	initDDRB();
	initDDRC();
	initDDRD();
	DS1302_InitIo();

	uint8_t previousRotaryData = readRotaryData();
	uint8_t previousRotaryPush = readRotaryPush();

	uint16_t ds1302ReadMillis = 0;
	uint16_t millis = 0;

	DS1302Clock timeData, previousTimeData;
	Mode mode = Mode::Normal;

	uint8_t renderingDigit = 0;
	uint8_t display[4] = { 0, 0, 0, 0 };

	for (;;) {
		uint8_t rotaryClock = readRotaryClock();
		uint8_t rotaryData = readRotaryData();
		uint8_t rotaryPush = readRotaryPush();

		int8_t rotaryDelta = 0;

		if(previousRotaryData == 1 && rotaryData == 0) {
			rotaryDelta = rotaryClock ? 1 : -1;
		}
		
		if (previousRotaryPush == 1 && rotaryPush == 0) {
			mode = mode == Mode::Normal ? Mode::Editing : Mode::Normal;
		}

		if (ds1302ReadMillis >= 900 && ds1302ReadMillis % 50 == 0) {

			DS1302_Select();
			DS1302_TransmitByte(DS1302_READ | ADDR_CLOCK_BURST);

			for (size_t i = 0; i < 8; i++) {
				timeData.raw[i] = DS1302_ReceiveByte();
			}

			DS1302_Deselect();

			if (!DS1302Clock_equals(timeData, previousTimeData)) {
				DS1302Clock_copy(previousTimeData, timeData);
				ds1302ReadMillis = 0;

				display[0] = BCD_1(timeData.seconds);
				display[1] = BCD_10(timeData.seconds);
				display[2] = BCD_1(timeData.minutes);
				display[3] = BCD_10(timeData.minutes);
			}
		}

		// render

		uint8_t segments = pgm_read_byte(&digitSegments[display[renderingDigit]]);
		uint8_t extraSegments = renderingDigit == 2 && (display[0] & 1) ? DIGIT_DECIMAL_SEGMENT : 0;
		if (mode == Mode::Normal || millis % 200 < 100) {
			setSegmentsOn(segments | extraSegments);
		} else {
			setSegmentsOn(0);
		}

		setDigitsOn(1 << renderingDigit);

		// advance

		renderingDigit = renderingDigit == 3 ? 0 : renderingDigit + 1;
		ds1302ReadMillis++;
		millis++;
		
		if (millis == 1000) {
			millis = 0;
		}

		// previous state
		previousRotaryData = rotaryData;
		previousRotaryPush = rotaryPush;

		_delay_ms(1);
	}

	return 0;
}
