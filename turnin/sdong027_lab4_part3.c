/*	Author: sdong027
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4 Exercise #3
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
	DDRC = 0xFF; PORTC = 0x00;

    unsigned char X = 0x00;
    unsigned char Y = 0x00;
    unsigned char H = 0x00; // #
    unsigned char I = 0x00; // inside
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;

    enum LOCK {LOCKED, HPRESS, HRELEASE, UNLOCKED} LOCK_STATE;
	while(1) {
        X = PINA & 0x01;	// 0x01
        Y = PINA & 0x02;	// 0x02
        H = PINA & 0x04;	// 0x04
        I = PINA & 0x80;
        
        switch (LOCK_STATE) {
            case LOCKED:
                if ((!X && H) && !Y) {
                    LOCK_STATE = HPRESS;
                }
                break;
            case HPRESS:
                if ((!X && !H) && !Y) {
                    LOCK_STATE = HRELEASE;
                }
                else if ((!X && H) && !Y) {
                    LOCK_STATE = HPRESS;
                }
                else {
                    LOCK_STATE = LOCKED;
                }
                break;
            case HRELEASE:
                if ((!X && !H) && Y) {
                    LOCK_STATE = UNLOCKED;
                }
		else if ((!X && !H) && !Y) {
		    LOCK_STATE = HRELEASE;
		}
                else {
                    LOCK_STATE = LOCKED;
                }
                break;
            case UNLOCKED:
                if (I) {
                    LOCK_STATE = LOCKED;
                }
                break;
            default:
                LOCK_STATE = LOCKED;
                break;
        }

        switch (LOCK_STATE) {
            case LOCKED:
                tmpB = 0x00;
                tmpC = LOCKED;
                break;
            case HPRESS:
                tmpB = 0x00;
                tmpC = HPRESS;
                break;
            case HRELEASE:
                tmpB = 0x00;
                tmpC = HRELEASE;
                break;
            case UNLOCKED:
                tmpB = 0x01;
                tmpC = UNLOCKED;
                break;
        }

        PORTB = tmpB;
        PORTC = tmpC;
	}
	return 0;
}
