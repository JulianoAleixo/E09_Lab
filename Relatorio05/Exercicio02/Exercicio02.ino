#define M1_HP 30
#define M2_HP 50
#define M3_HP 70

int main(void) {
  DDRD |= 0b11100000;     // PD7 -> M1; PD6 -> M2; PD5 -> M3
  PORTD |= 0b00000111;    // Pull-ups: PD2->A, PD1->B, PD0->C
  PORTD &= ~(0b11100000);

  while (1) {
    int A = PIND & 0b00000100;
    int B = PIND & 0b00000010;
    int C = PIND & 0b00000001;

    int reqM1 = !A;
    int reqM2 = !B;
    int reqM3 = !C;

    int totalHP = 0;
    if (reqM1) {
      totalHP += M1_HP;
    }
    if (reqM2) {
      totalHP += M2_HP;
    }
    if (reqM3) {
      totalHP += M3_HP;
    }

    PORTD &= ~(0b11100000);

    if (totalHP <= 90) {
      if (reqM1) {
        PORTD |= 0b10000000;
      }
      if (reqM2) {
        PORTD |= 0b01000000;
      }
      if (reqM3) {
        PORTD |= 0b00100000;
      }
    }
    else {
      if (reqM1 && totalHP > 90) {
        totalHP -= M1_HP;
        reqM1 = 0;
      }
      if (reqM2 && totalHP > 90) {
        totalHP -= M2_HP;
        reqM2 = 0;
      }
      if (reqM3 && totalHP > 90) {
        totalHP -= M3_HP;
        reqM3 = 0;
      }

      if (reqM1) {
        PORTD |= 0b10000000;
      }
      if (reqM2) {
        PORTD |= 0b01000000;
      }
      if (reqM3) {
        PORTD |= 0b00100000;
      }
    }
  }
}
