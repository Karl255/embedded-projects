#pragma once

#include <TinyI2C.h>
#include <stdint.h>
#include "util.h"
#include "graphics.h"

enum class SSD1306_ControlByte : uint8_t {
	Command = 0x80,
	AllCommand = 0x00,
	Data = 0xC0,
	AllData = 0x40
};

enum class SSD1306_Command : uint8_t {
	SetContrast = 0x81,
	DisplayRam = 0xA4,
	DisplayAllPixels = 0xA5,
	DisplayNoninverted = 0xA6,
	DisplayInverted = 0xA7,
	DisplayOff = 0xAE,
	DisplayOn = 0xAF,
	
	// skipping scrolling section
	
	SetColumnStartLower4 = 0x00,
	SetColumnStartUpper4 = 0x10,
	SetAddressingMode = 0x20,
	SetColumnAddress = 0x21,
	SetPageAddress = 0x22,
	SetPageStart = 0xB0,
	
	SetStartLine = 0x40,
	SetSegmentMappingNoraml = 0xA0,
	SetSegmentMappingMirrored = 0xA1,
	SetMultiplexRatio = 0xA8,
	SetComDirectionNormal = 0xC0,
	SetComDirectionMirrored = 0xC8,
	SetDisplayOffset = 0xD3,
	SetComPins = 0xDA,
	
	SetClockAndOscilator = 0xD5,
	SetPrecharge = 0xD9,
	SetVComhDeselect = 0xDB,
	NOP = 0xE3,
	
	SetChargePump = 0x8D,
};

void initializeOled(const uint8_t address);

void renderToOled(const uint8_t address, const uint8_t spriteTable[SCREEN_SIZE], const uint8_t attributeTable[SCREEN_SIZE / 2]);
