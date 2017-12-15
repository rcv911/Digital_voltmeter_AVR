#include <avr\io.h>              // Most basic include files
#include <avr\interrupt.h>       // Add the necessary ones
#include <avr\signal.h>          // here
#include <indicator.h>

ISR(ADC_vect){
	unsigned int value;
  	TIFR|=(1<<OCF1B); // Output Compare 1 B

	value = ADCH;  // 8bit 0-255
	value = value*0.02; // range 0...5.1 V
	adcSEG(value); // from headfile indicator.h		
}

void adc_init(void) {
 	ADMUX=(1<<REFS0)|(1<<ADLAR); //ADC0 SE, VREF=AVCC, 8bit (<-left)
	SFIOR=(1<<ADTS2)|(1<<ADTS0);
	ADCSRA=(1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADSC);
}

void main(void) {

	// led
	DDRC = 255;
	PORTC = 0;

	asm("cli");
	// t/c1
	TCCR1A=0;
	TCCR1B=(1<<WGM12)|(1<<CS11)|(1<<CS10); //TCNT1 (CTC mode), CLK/64
	OCR1B=5760-1; // frequency 10 Hz
	OCR1A=OCR1B;

	adc_init();  // ADC
	
	asm("sei");
	
	while(1) {
		asm("nop");
	}
}



