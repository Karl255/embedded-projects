#include "ssd1306.h"

void initializeOled(const uint8_t address) {
	TinyI2C.start(address, 0);

	TinyI2C.write((uint8_t)SSD1306_ControlByte::AllCommand);
	
	TinyI2C.write((uint8_t)SSD1306_Command::SetSegmentMappingMirrored);
	TinyI2C.write((uint8_t)SSD1306_Command::SetComDirectionMirrored);
	
	TinyI2C.write((uint8_t)SSD1306_Command::SetComPins);
	TinyI2C.write(0x12);
	
	TinyI2C.write((uint8_t)SSD1306_Command::SetChargePump);
	TinyI2C.write(0x14);
	
	TinyI2C.write((uint8_t)SSD1306_Command::SetAddressingMode);
	TinyI2C.write(0x00);
	
	TinyI2C.write((uint8_t)SSD1306_Command::SetPrecharge);
	TinyI2C.write(0xF1);
	
	TinyI2C.write((uint8_t)SSD1306_Command::SetVComhDeselect);
	TinyI2C.write(0x40);
	
	TinyI2C.write((uint8_t)SSD1306_Command::DisplayOn);
	
	TinyI2C.stop();
}

void renderToOled(const uint8_t address, const uint8_t spriteTable[SCREEN_SIZE], const uint8_t attributeTable[SCREEN_SIZE / 2]) {
	TinyI2C.start(address, 0);
	
	TinyI2C.write((uint8_t)SSD1306_ControlByte::AllData);
	
	for (size_t i = 0; i < SCREEN_SIZE; i++) {
		SpriteAttributes attr;
		attr.byte = (attributeTable[i >> 1] >> ((i & 1) ? 0 : 4));
		uint8_t spriteId = attr.visible ? spriteTable[i] : SPRITE_BLANK;
		uint8_t j = attr.hMirror ? 7 : 0;
		uint8_t delta = attr.hMirror ? -1 : 1;
		
		for (j = j; j < 8 && j >= 0; j += delta) {
			uint8_t bits = pgm_read_byte(&sprites[spriteId][j]);
			
			if (attr.vMirror) {
				bits = avr_reverse_byte(bits);
			}
			
			TinyI2C.write(bits);
		}
	}
	
	TinyI2C.stop();
}
