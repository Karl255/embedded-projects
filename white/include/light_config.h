// original source: https://github.com/cpldcpu/light_ws2812 (GNU GPL v2+)

#pragma once

/*
 * WS2813 needs 300 µs reset time
 * WS2812 and clones only need 50 µs
 */

#define ws2812_resettime  300

#define ws2812_port B
#define ws2812_pin 2
