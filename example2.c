#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


volatile int adc_value;
volatile unsigned long millis;
volatile unsigned long count_ms;
ISR(TIMER0_COMPA_vect)
{
   
    millis++;
    
    count_ms++;
    if(count_ms > adc_value){
        count_ms = 0;
        PORTD ^= (1<<PORTD3);
     
}
}

ISR(ADC_vect)
{
    adc_value = ADC;
    adc_value = adc_value*(400.0/1023.0)+100;
    ADCSRA |= _BV(ADSC);
}
 

void delay(unsigned long ms)
{
    unsigned long entry_time = millis;
    while (millis - entry_time < ms)
    {
 
    ;
    }
}

int main(void)
{
    
    DDRD=(1<<PORTD4);
    DDRD=(1<<PORTD3);
  
   
    ADMUX = 0b01000010;
    ADCSRA = 0b10001111; //0b10001111
    ADCSRB = 0b00000000;  
    sei();
    ADCSRA |= _BV(ADSC);
   
    TCCR0A = 0b00000010;
    TCCR0B = 0b00000000;
    TIMSK0 = 0b00000010;

    //1sec-->16000000 ticks will occur
    //1ms -->16000 ticks will occur as 1sec=1000ms
    //16000/64=250 -->prescalar 64

    OCR0A = 250-1;

    TCCR0B |= (_BV(CS01) | _BV(CS00));

    while(1)
    {
        
        PORTD |= (1<<PORTD4);
		delay(1000);

	    PORTD &= ~(1<<PORTD4);
		delay(1000);
  
    }
}
