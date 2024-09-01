#include "graphics.h"

void stringToSprites(const char* PROGMEM string, uint8_t* destinaton) {
	size_t i = 0;
	char c = pgm_read_byte(&string[i]);

	while (c) {
		if (c >= 'A' && c <= 'Z') {
			destinaton[i] = c - 'A' + SPRITE_A;
		} else if (c >= 'a' && c <= 'z'){
			destinaton[i] = c - 'a' + SPRITE_SEGMENT_HORIZONTAL;
		} else if (c >= '0' && c <= '9'){
			destinaton[i] = c - '0' + SPRITE_0;
		} else if (c == '!'){
			destinaton[i] = SPRITE_EXCLAMATION_MARK;
		} else {
			destinaton[i] = SPRITE_BLANK;
		}
		
		i++;
		c = pgm_read_byte(&string[i]);
	}
}

void init7SegmentSprites(uint8_t spriteTable[SCREEN_SIZE], uint8_t attributeTable[SCREEN_SIZE / 2], uint8_t topLeft){
	// a
	spriteTable[topLeft +  0 + 1] = SPRITE_SEGMENT_HORIZONTAL;
	spriteTable[topLeft +  0 + 2] = SPRITE_SEGMENT_HORIZONTAL;
	// d
	spriteTable[topLeft + 80 + 1] = SPRITE_SEGMENT_HORIZONTAL;
	spriteTable[topLeft + 80 + 2] = SPRITE_SEGMENT_HORIZONTAL;
	
	// b
	spriteTable[topLeft + 16 + 3] = SPRITE_SEGMENT_VERTICAL;
	spriteTable[topLeft + 32 + 3] = SPRITE_SEGMENT_VERTICAL + 1;
	// c
	spriteTable[topLeft + 48 + 3] = SPRITE_SEGMENT_VERTICAL + 1;
	spriteTable[topLeft + 64 + 3] = SPRITE_SEGMENT_VERTICAL;
	// e
	spriteTable[topLeft + 48 + 0] = SPRITE_SEGMENT_VERTICAL + 1;
	spriteTable[topLeft + 64 + 0] = SPRITE_SEGMENT_VERTICAL;
	// f
	spriteTable[topLeft + 16 + 0] = SPRITE_SEGMENT_VERTICAL;
	spriteTable[topLeft + 32 + 0] = SPRITE_SEGMENT_VERTICAL + 1;
	
	// g
	spriteTable[topLeft + 32 + 1] = SPRITE_SEGMENT_MIDDLE;
	spriteTable[topLeft + 32 + 2] = SPRITE_SEGMENT_MIDDLE;
	spriteTable[topLeft + 48 + 1] = SPRITE_SEGMENT_MIDDLE;
	spriteTable[topLeft + 48 + 2] = SPRITE_SEGMENT_MIDDLE;
	
	topLeft >>= 1;
	attributeTable[topLeft +  0 + 0] = 0x00;
	attributeTable[topLeft +  0 + 1] = 0x20;
	attributeTable[topLeft +  8 + 0] = 0x20;
	attributeTable[topLeft +  8 + 1] = 0x00;
	attributeTable[topLeft + 16 + 0] = 0x20;
	attributeTable[topLeft + 16 + 1] = 0x20;
	attributeTable[topLeft + 24 + 0] = 0x64;
	attributeTable[topLeft + 24 + 1] = 0x64;
	attributeTable[topLeft + 32 + 0] = 0x60;
	attributeTable[topLeft + 32 + 1] = 0x04;
	attributeTable[topLeft + 40 + 0] = 0x04;
	attributeTable[topLeft + 40 + 1] = 0x60;
}

void set7SegmentAttributes(uint8_t attributeTable[SCREEN_SIZE / 2], uint8_t digit, uint8_t topLeft) {
	digit = digit7Segments[digit & 0xf];
	topLeft >>= 1;
	
	uint8_t on = digit & 0b1000000;
	setBitAt(&attributeTable[topLeft +  0 + 0], 0, on);
	setBitAt(&attributeTable[topLeft +  0 + 1], 4, on);
	
	on = digit & 0b0100000;
	setBitAt(&attributeTable[topLeft +  8 + 1], 0, on);
	setBitAt(&attributeTable[topLeft + 16 + 1], 0, on);
	
	on = digit & 0b0010000;
	setBitAt(&attributeTable[topLeft + 24 + 1], 0, on);
	setBitAt(&attributeTable[topLeft + 32 + 1], 0, on);

	on = digit & 0b0001000;
	setBitAt(&attributeTable[topLeft + 40 + 0], 0, on);
	setBitAt(&attributeTable[topLeft + 40 + 1], 4, on);
	
	on = digit & 0b0000100;
	setBitAt(&attributeTable[topLeft + 24 + 0], 4, on);
	setBitAt(&attributeTable[topLeft + 32 + 0], 4, on);
	
	on = digit & 0b0000010;
	setBitAt(&attributeTable[topLeft +  8 + 0], 4, on);
	setBitAt(&attributeTable[topLeft + 16 + 0], 4, on);
	
	on = digit & 0b0000001;
	setBitAt(&attributeTable[topLeft + 16 + 0], 0, on);
	setBitAt(&attributeTable[topLeft + 16 + 1], 4, on);
	setBitAt(&attributeTable[topLeft + 24 + 0], 0, on);
	setBitAt(&attributeTable[topLeft + 24 + 1], 4, on);
}
