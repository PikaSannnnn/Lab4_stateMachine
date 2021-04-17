/*	Author: sdong027
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4 Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
  	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFE; PORTC = 0x00; // ooo oooi 
    unsigned char tmpA = 0x00;
	unsigned char tmpC = 0x00;

    enum OUT {INIT, INC, DEC} OUT_STATE;
    OUT_STATE = INIT;
	while(1) {
        tmpA = PINA & 0x03;
        
        switch (OUT_STATE) {
            case INIT:
                tmpC = 0x07;
                break;
            default:
                LED_STATE = OFF_WAIT;
                break;
        }

        PORTB = tmpB;
	}
	return 0;
}
