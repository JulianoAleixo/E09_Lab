#define TRIMPOT 4
#define LED (1 << PD6)

unsigned int Leitura_AD;
float pwm_power = 0.0;

int main(){
  DDRD |= LED;
  PORTD &= ~LED;

  // PWM
  TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
  TCCR0B |= (1 << CS02) | (1 << CS00);
  OCR0A = 0;

  // ADC
  ADMUX = (0 << REFS1) + (1 << REFS0);
  ADCSRA = (1 << ADEN) + (1 << ADPS2) + (1 << ADPS1) + (1 << ADPS0); 
  ADCSRB = 0;
  DIDR0 = (1 << TRIMPOT);

  sei();
  
  for(;;){
    ADMUX = (ADMUX & 0xF8) | TRIMPOT;
    ADCSRA |= (1 << ADSC); 
    while((ADCSRA & (1<<ADSC)) == (1<<ADSC));
    
    Leitura_AD = ADC;
    pwm_power = map(Leitura_AD, 0, 1023, 0, 255);
    OCR0A = pwm_power;
  }
}
