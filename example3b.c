#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


volatile int adc_value;

ISR(ADC_vect)
{

    adc_value = ADC;
    adc_value = adc_value*(3000.0/1023.0)+1000;
    OCR1A = adc_value;
    ADCSRA |= _BV(ADSC);
    
 }

int main(void)
{
    DDRD |= (1<<PORTD3)|(1<<PORTD4);
    DDRB |= _BV(DDB1);

    ADMUX = 0b01000010;
    ADCSRA = 0b10001111; //0b10001111
    ADCSRB = 0b00000000;
   
    sei();
    ADCSRA |= _BV(ADSC);

    TCCR1A = 0b10000010;
    TCCR1B = 0b00011000;

    OCR1A = 0xFF; //change to liking
    ICR1 = 39999;     //prescalar-->TOP=(16000000/(50*8))-1
    TCCR1B |= _BV(CS11);
    

    while(1)
    {
        for(int adc_value=0;adc_value<4000;adc_value++)
      {
        OCR1A = OCR1A+adc_value;
      }

        PORTD |= (1<<PORTD4);
		_delay_ms(500);

	    PORTD &= ~(1<<PORTD4);
		_delay_ms(500);
  
    }
}



