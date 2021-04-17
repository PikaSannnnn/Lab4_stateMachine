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
	DDRB = 0xFF; PORTB = 0x00;
    unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;

    enum LED {OFF, OFF_WAIT, ON, ON_WAIT} LED_STATE;
	while(1) {
        tmpA = PINA & 0x01;
        
        switch (LED_STATE) {
            case OFF:
                if (!(tmpA)) {
                    LED_STATE = OFF_WAIT;
                }
                break;
            case OFF_WAIT:
                if (tmpA) {
                    LED_STATE = ON;
                }
                break;
            case ON:
                if (!(tmpA)) {
                    LED_STATE = ON_WAIT;
                }
                break;
            case ON_WAIT:
                if (tmpA) {
                    LED_STATE = OFF;
                }
                break;
            default:
                LED_STATE = OFF_WAIT;
                break;
        }

        switch (LED_STATE) {
            case OFF:
                tmpB = 0x01;
                break;
            case OFF_WAIT:
                tmpB = 0x01;
                break;
            case ON:
                tmpB = 0x02;
                break;
            case ON_WAIT:
                tmpB = 0x02;
                break;
            default:
                LED_STATE = 0x01;
                break;
        }

        PORTB = tmpB;
	}
	return 0;
}
