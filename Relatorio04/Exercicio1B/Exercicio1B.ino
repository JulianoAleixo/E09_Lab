int main() {
  DDRD = DDRD | 0b11000000;
  PORTD = PORTD | 0b00110000;
  PORTD = PORTD & ~(0b11000000);

  while (1) {
    int button1 = PIND & 0b00100000;
    int button2 = PIND & 0b00010000;
    
    if (!button1) {
      PORTD = PORTD | 0b10000000;
      PORTD = PORTD & ~(0b01000000);
    } else if (!button2) {
      PORTD = PORTD & ~(0b10000000);
      PORTD = PORTD | 0b01000000;
    }
    PORTD = PORTD & ~(0b11000000);
  }

  return 0;
}
