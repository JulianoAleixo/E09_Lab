#define OFF   0
#define ON    1
#define ALARM 2

int main(void) {
  DDRD |= 0b11000000;     // PD7 -> MOTOR; PD6 -> ALARME
  PORTD |= 0b00111000;    // Pull-ups: PD5->NA, PD4->NF, PD3->S1
  PORTD &= ~(0b11000000);
  int state = OFF;
  
  while (true) {
    int NA = PIND & 0b00100000;
    int NF = PIND & 0b00010000;
    int S1 = PIND & 0b00001000;

    switch (state) {
      case OFF:
        PORTD &= ~(0b11000000);
        if (!NA && S1) {
          state = ON;
        }
        break;

      case ON:
        PORTD |= 0b10000000;
        PORTD &= ~(0b01000000);
  
        if (!NF) {
          state = OFF;
        }
        if (!S1) {
          state = ALARM;
        }
        break;

      case ALARM:
        PORTD &= ~(0b10000000);
        PORTD |= 0b01000000;
  
        if (!NA && S1) {
          state = ON;
        }
        break;
    }
  }
}
