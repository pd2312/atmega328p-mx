#include<avr/io.h>
#include<util/delay.h>
 
int main(void)
{
PORTD = (1<<PORTD2); //PD2
DDRD = (1<<PORTD3)|(1<<PORTD4); // PD3 | PD4
 
while(1){
	if ((PIND & (1<<PIND2)) == (1<<PIND2) )
		{
			PORTD |= (1<<PORTD3);
			_delay_ms(500);

			PORTD &= ~(1<<PORTD3);
			_delay_ms(500);
		} 

	else
        {
            PORTD |= (1<<PORTD4);
            _delay_ms(500);
            
            PORTD &= ~(1<<PORTD4);
            _delay_ms(500);
        }
	
	
 }
 return 0;
}

