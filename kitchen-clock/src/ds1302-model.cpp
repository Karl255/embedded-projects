#include "ds1302-model.h"

uint8_t DS1302Clock_equals(DS1302Clock& a, DS1302Clock& b) {
	return a.seconds == b.seconds
		&& a.minutes == b.minutes
		&& a.hours == b.hours;
	//	&& a.day == b.day
	//	&& a.month == b.month
	//	&& a.dayOfWeek == b.dayOfWeek
	//	&& a.year == b.year
	//	&& a.writeProtect == b.writeProtect;
}

void DS1302Clock_copy(DS1302Clock& destination, DS1302Clock& source) {
	destination.seconds = source.seconds;
	destination.minutes = source.minutes;
	destination.hours = source.hours;
	//destination.day = source.day;
	//destination.month = source.month;
	//destination.dayOfWeek = source.dayOfWeek;
	//destination.year = source.year;
	//destination.writeProtect = source.writeProtect;
}
