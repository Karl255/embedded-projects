# tiny-ir-rgb

An IR (NEC) RGB LED strip controller powered by an ATtiny45/85.

Features:
- color-cycle animations - easily customisable state machines
- remembers state in EEPROM - to instantly resume after a power loss
- NEC infrared remote control (custom library)
	- reliable operation even with the internal RC oscillator
	- non-blocking operation so animations remain smooth
- low MCU program memory requirements - 2634 bytes (could probably be reduced to fit the ATtiny25)

Feel free to use the NEC IR code and adjust it for your own purpose.

Dependencies: none.

This project is made using [PlatformIO](https://platformio.org/).
