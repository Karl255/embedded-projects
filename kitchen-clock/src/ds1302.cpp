// based on: https://github.com/afiskon/avr-ds1302/blob/master/main.c

#include <avr/io.h>
#include <util/delay.h>

#include "io.h"
#include "ds1302.h"

void DS1302_InitIo(void) {
    // CE - output, set low
    DS1302_CE_DDR |= (1 << DS1302_CE);
    DS1302_CE_PORT &= ~(1 << DS1302_CE);

    // CLK - output, set low
    DS1302_CLK_DDR |= (1 << DS1302_CLK);
    DS1302_CLK_PORT &= ~(1 << DS1302_CLK);

    // DIO - output, set low (for now)
    DS1302_DIO_DDR |= (1 << DS1302_DIO);
    DS1302_DIO_PORT &= ~(1 << DS1302_DIO);
}

void DS1302_Select(void) {
    // set CE high
    DS1302_CE_PORT |= (1 << DS1302_CE);
}

void DS1302_Deselect(void) {
    // set CE low
    DS1302_CE_PORT &= ~(1 << DS1302_CE);
}

void DS1302_TransmitByte(uint8_t byte) {
    // DIO - output, set low
    DS1302_DIO_DDR |= (1 << DS1302_DIO);
    DS1302_DIO_PORT &= ~(1 << DS1302_DIO);

    // transmit byte, lsb-first
    for(uint8_t i = 0; i < 8; i++) {
        if((byte >> i) & 0x01) {
            // set high
            DS1302_DIO_PORT |= (1 << DS1302_DIO);
        } else {
            // set low
            DS1302_DIO_PORT &= ~(1 << DS1302_DIO);
        }

        // send CLK signal
        DS1302_CLK_PORT |= (1 << DS1302_CLK);
        _delay_us(DS1302_DELAY_USEC);
        DS1302_CLK_PORT &= ~(1 << DS1302_CLK);
    }
}

uint8_t DS1302_ReceiveByte(void) {
    // DIO - input
    DS1302_DIO_DDR &= ~(1 << DS1302_DIO);

    // NB: receive is always done after transmit, thus
    // falling edge of CLK signal was already sent
    // see "Figure 4. Data Transfer Summary" for more details

    // receive byte, lsb-first
    uint8_t byte = 0;
    for(uint8_t i = 0; i < 8; i++) {
        if(DS1302_DIO_PIN & (1 << DS1302_DIO)) {
            byte |= (1 << i);
        }

        // send CLK signal
        DS1302_CLK_PORT |= (1 << DS1302_CLK);
        _delay_us(DS1302_DELAY_USEC);
        DS1302_CLK_PORT &= ~(1 << DS1302_CLK);
    }

    return byte;
}
