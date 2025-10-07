ISR(INT0_vect) {
  PORTD |= 0b00010000;
  _delay_ms(1 * 1000);
  PORTD &= ~0b00010000;
}

int main() {
  DDRD = 0b00110000;
  PORTD = 0b00000100;
  EICRA = 0b00000011;
  EIMSK = 0b00000001;

  sei();

  while (1) {
    PORTD ^= 0b00100000;
    _delay_ms(500);
  }

  return 0;
}
