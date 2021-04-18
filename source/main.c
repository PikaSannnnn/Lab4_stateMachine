/*	Author: sdong027
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4 Exercise #2
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
	DDRC = 0xFF; PORTC = 0x00;
    unsigned char tmpA = 0x00;
	unsigned char tmpC = 0x00;

    enum OUT {RST, WAIT, WAIT_RELEASE, INC, DEC} OUT_STATE;
	while(1) {
        tmpA = PINA & 0x03;
        
        switch (OUT_STATE) {
            case RST:
                if (!tmpA) {
                    OUT_STATE = WAIT;
                }
                else if ((tmpA & 0x01) && !(tmpA & 0x02)) {
                    OUT_STATE = INC;
                }
                else if ((tmpA & 0x02) && !(tmpA & 0x01)) {
                    OUT_STATE = DEC;
                }
                break;
            case WAIT:
                if ((tmpA & 0x01) && !(tmpA & 0x02)) {
                    OUT_STATE = INC;
                }
                else if ((tmpA & 0x02) && !(tmpA & 0x01)) {
                    OUT_STATE = DEC;
                }
                else if ((tmpA & 0x01) && (tmpA & 0x02)) {
                    OUT_STATE = RST;
                }
                break;
            case WAIT_RELEASE:
                if (!tmpA) {
                    OUT_STATE = WAIT;
                }
                else if ((tmpA & 0x01) && (tmpA & 0x02)) {
                    OUT_STATE = RST;
                }
                break;
            case INC:
                OUT_STATE = WAIT_RELEASE;
                break;
            case DEC:
                OUT_STATE = WAIT_RELEASE;
                break;
            default:
                tmpC = 0x07;
                OUT_STATE = WAIT_RELEASE;
                break;
        }

        switch (OUT_STATE) {
            case RST:
                tmpC = 0x00;
                break;
            case WAIT:
                break;
            case WAIT_RELEASE:
                if (!tmpA) {
                    OUT_STATE = WAIT;
                }
                else if ((tmpA & 0x01) && (tmpA & 0x02)) {
                    OUT_STATE = RST;
                }
                break;
            case INC:
                if (tmpC < 9) {
                    tmpC++;
                }
                break;
            case DEC:
                if (tmpC > 0) {
                    tmpC--;
                }
                break;
        }

        PORTC = tmpC;
	}
	return 0;
}
