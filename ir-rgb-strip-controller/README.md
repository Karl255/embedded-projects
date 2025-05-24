# tiny-ir-rgb

An IR RGB LED strip controller powered by an ATtiny45/85.

Features:
- fade between static colors
- color-cycle animations - easily customisable state machines
- remembers state in EEPROM - to instantly resume after an unexpected power loss
- infrared remote control (via custom library)
    - Samsung32-like pulse-distance protocol (customisable for different pulse-distance protocols)
	- reliable operation even with the internal RC oscillator due to start bit sync
	- non-blocking operation so animations remain smooth
- low MCU program memory requirements - 2656 bytes (could probably be reduced to fit into 2k)

Feel free to use the IR code and adjust it for your own purpose.

For a remote control button reference see src/include/control.h

Dependencies: none.

This project is made using [PlatformIO](https://platformio.org/).

## Setup

| pin | uC function | function  |
|-----|-------------|-----------|
| 1   | PB5         | NC        |
| 2   | PB3         | NC        |
| 3   | PB4 OC1B    | R PWM out |
| 4   | GND         | power     |
| 5   | PB0 OC0A    | G PWM out |
| 6   | PB1 OC0B    | B PWM out |
| 7   | PB2 INT0    | IR in     |
| 8   | VCC         | power     |

Internal oscillator at 8 MHz

**Timer0**

Frequency: CLK / 8 / 2 / 256 = ~2 kHz PWM

Outputs:
- OC0A (pin 5) - G channel PWM
- OC0B (pin 6) - B channel PWM

Misc:
- phase correct PWM (halves frequency)
- CLK/8 prescaler
- counts 0x00 - 0xFF

Interrupts:
- Timer0 overflow (TIMER0_OVF) - mode/animation state machine ticking

**Timer1**

Frequency: CLK / 256 = ~32 kHz PWM

Outputs:
- OC1B (pin 3) - R channel PWM

Interrupts:
- Timer1 overflow (TIMER1_OVF) - IR pulse measurement
