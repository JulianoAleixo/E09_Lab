unsigned int count = 0;

void ConfigTimer0(void) {
  TCCR0B |= (1 << CS01);
  TCCR0A |= (1 << WGM01);
  OCR0A = 200;
  TIMSK0 |= (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
  count++;
  if (count >= 1500) {
    PORTD ^= 0b00100000;
    count = 0;
  }
}

int main() {
  DDRD |= 0b00100000;
  PORTD &= ~(0b00100000);

  ConfigTimer0();
  sei();

  while(1){}
}
