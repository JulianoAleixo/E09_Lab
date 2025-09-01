#define ON 1
#define OFF 0

unsigned char logic_state = OFF;

int main() {
  unsigned char last_button = 0b00100000;

  DDRD = DDRD | 0b11000000;
  PORTD = PORTD | 0b00110000;
  PORTD = PORTD & ~(0b11000000);

  while (1) {
    int button1 = PIND & 0b00100000;

    if (last_button && !button1) {
      if (logic_state == OFF) {
        logic_state = ON;
      } else {
        logic_state = OFF;
      }
    }

    switch (logic_state) {
      case ON:
        PORTD = PORTD | 0b10000000;
        break;

      case OFF:
        PORTD = PORTD & ~(0b10000000);
        break;

      default:
        break;
    }

    last_button = button1;
  }

  return 0;
}
