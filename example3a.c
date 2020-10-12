//rotates servo using timer not potentiometer.

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int adc_value=0;
volatile unsigned long count_ms=0;
volatile unsigned long count_ms2=0;

ISR(TIMER0_OVF_vect)  
{
  count_ms++;  
  count_ms2++;
  adc_value = (ADCH<<8)|(ADCL);
  
  if(count_ms>adc_value)
  {
    count_ms=0;
    PORTB = PORTB ^ (1<<5); 
                            
    PORTD = PORTD ^ (1<<3);
  }
} 

ISR(ADC_vect)
{
  adc_value = ADC;
  ADCSRA |= _BV(ADSC);
}

int main(void)
{
  
  DDRB |= _BV(DDB1);

  ADMUX = 0b01000010;
    ADCSRA = 0b10001111; //0b10001111
    ADCSRB = 0b00000000;
    
    sei();
    ADCSRA |= _BV(ADSC);

    TCCR1A = 0b10000010;
    TCCR1B = 0b00011000;

    OCR1A = 1000; 
    ICR1 = 39999;     //prescalar-->TOP=(16000000/(50*8))-1
    TCCR1B |= _BV(CS11);


    while(1)
    {
      for (int i = 0; i <= 5000; i += 100)
	  {
		  OCR1A = 0 + i;
		  _delay_ms(50);
		  /* code */
	  }

	  for (int i = 4000; i >= 1000; i -=10)
	  {
		  OCR1A = i;
		  _delay_ms(10);
	  }
	  
	  
    }
  
}
