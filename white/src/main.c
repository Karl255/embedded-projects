#include <stdint.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <light.h>

#define N 18

struct cRGB leds[N];

int main(void) {
	int i = 0;
	
	for (i = 0; i < N ; i++) {
		leds[i] = (struct cRGB){ .r = 255, .g = 255, .b = 255};
		
	}

	ws2812_setleds(leds, N);
		
	for (;;) {
		// 10s delay before total shutdown, just in case
		_delay_ms(10000);
		
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_enable();
		sleep_bod_disable();
		sleep_cpu();
		sleep_disable();
	}

	return 0;
}
