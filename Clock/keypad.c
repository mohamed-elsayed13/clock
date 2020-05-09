/*
 * keypad.c
 *
 * Created: 30/03/2020 11:16:18 PM
 *  Author: M
 */ 
#include "keypad.h"

const uint8_t keypad_matrix[] = {
	'h','9','8','7',
	'm','6','5','4',
	's','3','2','1',
	'e','o','0','C'
};

void keypad_init(){
	CLRBIT(DDRD,2);
	CLRBIT(DDRD,3);
	CLRBIT(DDRD,4);
	CLRBIT(DDRD,5);
	PORTD |= 0b00111100; // internal pull up in case of protues
	SETBIT(DDRB,4);
	SETBIT(DDRB,5);
	SETBIT(DDRB,6);
	SETBIT(DDRB,7);
}
int8_t keypad_read(){
	for(uint8_t i=0;i<4;i++){
		
	PORTB = PORTB & 0b00001111;	
	if(i==0) PORTB  |= 0b11100000;
	if(i==1) PORTB  |= 0b11010000;
	if(i==2) PORTB  |= 0b10110000;
	if(i==3) PORTB  |= 0b01110000;
	
	if(GETBIT(PIND,2)==0) return keypad_matrix[0+4*i];
	if(GETBIT(PIND,3)==0) return keypad_matrix[1+4*i];
	if(GETBIT(PIND,4)==0) return keypad_matrix[2+4*i];
	if(GETBIT(PIND,5)==0) return keypad_matrix[3+4*i];
	_delay_ms(1);
	}    
    return -1;
	}
