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
	DDRB = 0xFE; PORTB = 0x00; // ooo oooi 
    unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;

    enum LED {OFF, OFF_WAIT, ON, ON_WAIT} LED_STATE;
    LED_STATE = OFF_WAIT;
	while(1) {
        tmpA = PINA & 0x03;
        
        switch (LED_STATE) {
            case OFF:
                tmpB = 0x01;
                if (!(tmpA)) {
                    LED_STATE = OFF_WAIT;
                }
                break;
            case OFF_WAIT:
                tmpB = 0x01;
                if (tmpA) {
                    tmpB = 0x02;
                    LED_STATE = ON;
                }
                break;
            case ON:
                tmpB = 0x02;
                if (!(tmpA)) {
                    LED_STATE = ON_WAIT;
                }
                break;
            case ON_WAIT:
                tmpB = 0x02;
                if (tmpA) {
                    tmpB = 0x01;
                    LED_STATE = OFF;
                }
                break;
            default:
                LED_STATE = OFF_WAIT;
                break;
        }

        PORTB = tmpB;
	}
	return 0;
}
