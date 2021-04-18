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

    //unsigned char X = 0x00;
    //unsigned char Y = 0x00;
    //unsigned char H = 0x00; // #
    //unsigned char I = 0x00; // inside
    unsigned char code[4] = {0x04, 0x01, 0x02, 0x01};   // #XYX
	unsigned char input = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
    unsigned char i = 0x00;

    enum LOCK {LOCKED, PRESS, UNLOCKED, LPRESS} LOCK_STATE;
	while(1) {
        input = PINA & 0xFF;
        // X = PINA & 0x01;	// 0x01
        // Y = PINA & 0x02;	// 0x02
        // H = PINA & 0x04;	// 0x04
        // I = PINA & 0x80;
        
        switch (LOCK_STATE) {
            case LOCKED:
                if (input == code[i]) {
                    i++;
                    if (i == 4) {
                        LOCK_STATE = UNLOCKED;
                        i = 0x00;
                    }
                    else {
                        LOCK_STATE = PRESS;
                    }
                }
                else {
                   i = 0x00; 
                }
                break;
            case PRESS:
                if (!input) {
                    LOCK_STATE = LOCKED;
                }
                else if (input == code[i - 1]) {
                    LOCK_STATE = PRESS;
                }
                else {
                    i = 0x00;
                    LOCK_STATE = LOCKED;
                }
                break;
            case UNLOCKED:
                if (input == 0x80) {
                    LOCK_STATE = LOCKED;
                }
                else if (input == code[i]) {
                    i++;
                    if (i == 4) {
                        LOCK_STATE = LOCKED;
                        i = 0x00;
		            }
                    else {
                        LOCK_STATE = LPRESS;
                    }
                }
                else {
                    i = 0x00;
                }
                break;
            case LPRESS:
                if (!input) {
                    LOCK_STATE = UNLOCKED;
                }
                else if (input == code[i - 1]) {
                    LOCK_STATE = LPRESS;
                }
                else {
                    i = 0x00;
                    LOCK_STATE = UNLOCKED;
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
            case PRESS:
                tmpC = PRESS;
                break;
            case UNLOCKED:
                tmpB = 0x01;
                tmpC = UNLOCKED;
                break;
            case LPRESS:
                tmpC = LPRESS;
                break;
        }

        PORTB = tmpB;
        PORTC = tmpC;
	}
	return 0;
}
