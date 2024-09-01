/*
 * PD0 = forward
 * PD1 = reverse
 * PD2 = mode
 * PD3 = adjust
*/

#define BUTTON A0

// maps chars to their ordinal number in the e-Data char table
// 0 = default char = space
const int charMap[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	    // 0-31 don't map to anything
	0,  // 32, space
	72, // 33, '!'
	79, // 34, '"'
	71, // 35, '#'
	0,  // 36, '$'
	73, // 37, '%'
	81, // 38, '&'
	77, // 39, '''
	84, // 40, '('
	85, // 41, ')'
	63, // 42, '*'
	83, // 43, '+'
	78, // 44, ','
	64, // 45, '-'
	74, // 46, '.'
	68, // 47, '/'
	53, // 48, '0'
	54, // 49, '1'
	55, // 50, '2'
	56, // 51, '3'
	57, // 52, '4'
	58, // 53, '5'
	59, // 54, '6'
	60, // 55, '7'
	61, // 56, '8'
	62, // 57, '9'
	75, // 58, ':'
	76, // 59, ';'
	0,  // 60, '<'
	82, // 61, '='
	0,  // 62, '>'
	70, // 63, '?'
	66, // 64, '@'
	27, // 65, 'A'
	28, // 66, 'B'
	29, // 67, 'C'
	30, // 68, 'D'
	31, // 69, 'E'
	32, // 70, 'F'
	33, // 71, 'G'
	34, // 72, 'H'
	35, // 73, 'I'
	36, // 74, 'J'
	37, // 75, 'K'
	38, // 76, 'L'
	39, // 77, 'M'
	40, // 78, 'N'
	41, // 79, 'O'
	42, // 80, 'P'
	43, // 81, 'Q'
	44, // 82, 'R'
	45, // 83, 'S'
	46, // 84, 'T'
	47, // 85, 'U'
	48, // 86, 'V'
	49, // 87, 'W'
	50, // 88, 'X'
	51, // 89, 'Y'
	52, // 90, 'Z'
	0,  // 91, '['
	69, // 92, '\'
	0,  // 93, ']'
	80, // 94, '^'
	65, // 95, '_'
	0,  // 96, '`'
	1,  // 97, 'a'
	2,  // 98, 'b'
	3,  // 99, 'c'
	4,  // 100, 'd'
	5,  // 101, 'e'
	6,  // 102, 'f'
	7,  // 103, 'g'
	8,  // 104, 'h'
	9,  // 105, 'i'
	10, // 106, 'j'
	11, // 107, 'k'
	12, // 108, 'l'
	13, // 109, 'm'
	14, // 110, 'n'
	15, // 111, 'o'
	16, // 112, 'p'
	17, // 113, 'q'
	18, // 114, 'r'
	19, // 115, 's'
	20, // 116, 't'
	21, // 117, 'u'
	22, // 118, 'v'
	23, // 119, 'w'
	24, // 120, 'x'
	25, // 121, 'y'
	26, // 122, 'z'
	0,  // 123, '{'
	0,  // 124, '|'
	0,  // 125, '}'
	67, // 126, '~'
	0   // 127, DEL
};

const char *allowedChars = R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-_@~/\?#!%.:;',"^&=+())";
const char *printString = "Hi!";

enum class Button {
	Forward = 0,
	Reverse = 1,
	Mode = 2,
	Adjust = 3
};

// haven't played much with this, could probably be set lower
const int delayTime = 100;

void setup() {
	// set the pins to output and high
	DDRD |= B1111;
	PORTD |= B1111;
	pinMode(13, OUTPUT);
	// at this point all pins are set high and the watch's ground can be connected to the Arduino's ground
	// this process can be automated with a MOSFET like mentioned in README.md
	digitalWrite(13, HIGH);
	pinMode(BUTTON, INPUT_PULLUP);
}

// single press to the specified button with an equal high and low time defined by delayTime
void press(Button n) {
	PORTD &= ~(1 << (int)n);
	delay(delayTime);
	PORTD |= (1 << (int)n);
	delay(delayTime);
}

void loop() {
	// wait for button to be pressed
	// before doing that the watch should be in the e-Data mode and ready to write
	while (digitalRead(BUTTON));
	
	int i = 0;
	
	while (printString[i] != '\0') {
		// writes the string into the e-Data memory
		int count = charMap[printString[i]];
		
		// increment until at the right character
		for (int j = 0; j < count; j++) {
			press(Button::Forward);
		}
		
		// next position
		press(Button::Mode);
		i++;
	}
	
	// save and exit
	press(Button::Adjust);
}
