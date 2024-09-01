/*
MIT License

Copyright (c) 2023 Karlo B.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <ir_NEC.h>
#include <control.h>

// 0.02 ms timeout
#define IR_TIMER_TIMEOUT 640

enum class IrCommStep : uint8_t {
	idle = 0,
	sync = 1,
	/// @brief Measuring the first HIGH pulse that determines a regular transmission or a repeat transmission.
	mode = 2,
	payload = 3,
	pause = 4,
};

volatile uint16_t ir_timer = 0;

/// @brief The measured NEC protocil "u" unit measured in ir_timer units. "u" is the largest common divisor between all pulse lengths in an NEC protocol transmission (562.5 us).
volatile uint8_t measured_u = 1;
volatile struct IrReadout ir_readout;

volatile IrCommStep step = IrCommStep::idle;
volatile uint8_t payload[4] = { 0 };
volatile uint8_t payload_index = 0;
volatile uint8_t payload_bit = 0;

void handle_error() {
	ir_timer = 0;
	step = IrCommStep::idle;
}

ISR(INT0_vect) {
	#define _read_ir() ((PINB >> PB2) & 1)

	switch (step) {
		case IrCommStep::idle:
			if (_read_ir() == 0) {
				ir_timer = 0;

				payload[0] = 0;
				payload[1] = 0;
				payload[2] = 0;
				payload[3] = 0;
				payload_index = 0;
				payload_bit = 0;
				step = IrCommStep::sync;
			} else {
				handle_error();
			}

			break;

		case IrCommStep::sync:
			if (_read_ir() == 1) {
				uint8_t _measured_u = ir_timer / 16;
				measured_u = _measured_u > 0 ? _measured_u : 1;
				ir_timer = 0;

				step = IrCommStep::mode;
			} else {
				handle_error();
			}

			break;

		case IrCommStep::mode:
			if (_read_ir() == 0) {
				uint8_t pulse = ir_timer;

				if (pulse > 5 * measured_u) {
					step = IrCommStep::payload;
				} else {
					step = IrCommStep::pause;
					ir_readout.event = IrEvent::repeat;
				}
			} else {
				handle_error();
			}

			break;

		case IrCommStep::payload:
			if (_read_ir() == 1) {
				ir_timer = 0;
			} else {
				uint8_t pulse = ir_timer;

				if (pulse > 2 * measured_u) {
					payload[payload_index] |= 1 << payload_bit;
				}

				payload_bit++;

				if (payload_bit == 8) {
					payload_bit = 0;
					payload_index++;
				}

				if (payload_index == 4) {
					step = IrCommStep::pause;

					if (payload[2] == (uint8_t)~payload[3]) {
						ir_readout.command = (Command)payload[2];
						ir_readout.event = IrEvent::transmission;
					}

					payload[0] = 0;
					payload[1] = 0;
					payload[2] = 0;
					payload[3] = 0;
					payload_index = 0;
					payload_bit = 0;
				}
			}

			break;

		case IrCommStep::pause:
			step = IrCommStep::idle;
			break;

		default:
			break;
	}

	#undef _read_ir
}

ISR(TIMER1_OVF_vect) {
	ir_timer++;

	if (ir_timer > IR_TIMER_TIMEOUT) {
		handle_error();
	}
}
