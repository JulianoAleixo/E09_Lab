#define LED (1 << PD6)
#define BOTAO (1 << PB0)

float pwm_power = 0.0;

int main(){
  //Configurações de entrada e saída
  DDRD |= LED; // configura saída PD6 para o PWM
  PORTD &= ~LED; // PWM inicia desligado
  
  PORTB |= BOTAO; // Ativa resistor de pull-up interno do pino PB0
  
  // Configura modo FAST PWM e modo do comparador A não-inversor
  TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00); //0b100000011

  // Ativa o PWM com Pre-Scaler 1024 (Frequência de 15,625KHz)
  TCCR0B |= (1 << CS02) | (1 << CS00); //0b00000101

  // Inicia o PWM com DC = 0%
  OCR0A = 0;

  //Configuração da interrupção externa no portal B
  PCICR = (1 << PCIE0);
  PCMSK0 |= BOTAO; //Ativa a interrupção no pino PB0
  
  //Ativa as interrupções globais
  sei();
  
  for (;;){
    
  }

}

//Vetor da interrupção do portal B
ISR(PCINT0_vect){
  if((PINB & BOTAO) == 0){ //Quando botão for precionado (botao = 0)
    pwm_power += 25.5;
    if (pwm_power >= 255) {
      pwm_power = 0.0;
    }
    OCR0A = pwm_power; //Modifica o DC para 50% (50% de 255)
    _delay_ms(500);
  }
}
