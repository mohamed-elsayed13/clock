/*
 * Clock.c
 *
 * Created: 22/04/2020 9:42:42 AM
 *  Author: Mohamed Elsayed
 */ 

#include "LCD.h"
#include "EEPROM.h"
#include "Timer0.h"
uint8_t min  ;
uint8_t hour ; 
uint8_t sec  ;
uint8_t counter=0;
uint8_t state=1;
int main(void)
{	
    CLRBIT(SREG,7);
	LCD_init();
	LCD_write_command(0x01);
	LCD_write_string("2 reset time use");
	_delay_ms(500);
	LCD_write_command(0x01);
	LCD_write_string("PD2 & PD3 & PD4");
	_delay_ms(500);
	CLRBIT(DDRD,2);
	CLRBIT(DDRD,3);
	CLRBIT(DDRD,4);
	SETBIT(MCUCR,ISC00);
	SETBIT(MCUCR,ISC01);
	SETBIT(GICR,INT0);
	SETBIT(MCUCR,ISC10);
	SETBIT(MCUCR,ISC11);
	SETBIT(GICR,INT1);
	sei();
	sec  =EEPROM_read(6);
    min  =EEPROM_read(7);
    hour =EEPROM_read(8);
	timer_normal_init();
	
	while(1)
    {
	
	while((GETBIT(PIND,4)==1)){}
	_delay_ms(500);
	counter++;
		}
	
    }

ISR(TIMER0_OVF_vect){
static uint16_t count = 0;

count++;
	
if (count ==62){
	
	sec++;
	if (sec>=60){
		sec=0 ;
		min ++ ;
		if (min>=60){
			min=0;
			hour++;
			if (hour==12){TOGBIT(state,0);}
			if(hour >=13){
				hour=1;
					}
		}
		}
	EEPROM_write(6,sec);
	EEPROM_write(7,min);
	EEPROM_write(8,hour);	
	count=0;
	LCD_write_command(0x01);
	LCD_write_command(0x84);
	LCD_write_string("My Clock");
	LCD_write_command(0xc3);
	LCD_write_num(hour);
	LCD_write_char(':');
	LCD_write_num(min);
	LCD_write_char(':');
	LCD_write_num(sec);
	if(state==1){LCD_write_string(" AM");}
	else {LCD_write_string(" PM");}	
}

}
ISR(INT0_vect){
if (counter==0){
	sec++;
	if (sec>=60){
		sec=0 ;
			}
	EEPROM_write(6,sec);		
	}
else if (counter==1){
	min++;
	if (min>=60){
		min=0;
			}
	EEPROM_write(7,min);		
	}
else if (counter==2){
	hour++;
	if(hour ==13){
		hour=1;
	}
	EEPROM_write(8,hour);
}
else if (counter==3){TOGBIT(state,0);}
	else if (counter>3){counter=0;}
	}		
ISR(INT1_vect){
	if (counter==0){
		sec--;
		if (sec<=0){
		sec=59;}
		EEPROM_write(6,sec);
	}
	else if (counter==1){
		min--;
		if (min<=0){
			min=59;}
		EEPROM_write(7,min);	
	}
	else if (counter==2){
		hour--;
		if(hour<1){    
			hour=12;
		 }
		EEPROM_write(8,hour);
	}
else if (counter==3){TOGBIT(state,0);}
	else if (counter>3){counter=0;}
	}