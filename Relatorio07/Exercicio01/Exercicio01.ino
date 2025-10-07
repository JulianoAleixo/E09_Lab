int flag_PD7 = 0;
int flag_PD6 = 0;
int flag_PB1 = 0;

ISR(PCINT2_vect) {
    if (!(PIND & 0b00010000)) {   // PCINT20
        flag_PB1 = 1;
    }
}

ISR(PCINT0_vect) {
    if (!(PINB & 0b00000001)) {   // PCINT0
        flag_PD7 = 1;
    }
    if (!(PINB & 0b00000100)) {   // PCINT2
        flag_PD6 = 1;
    }
}

int main(void) {
    DDRD |= 0b11100000;
    DDRB |= 0b00000010;

    PORTD &= ~(0b11100000);
    PORTD |= 0b00010000;

    DDRB &= ~(0b00000010);
    PORTB |= 0b00000101;

    PCICR |= 0b00000101;
    PCMSK2 |= 0b00010000;
    PCMSK0 |= 0b00000101;

    sei();

    while (1) {
        PORTD ^= 0b00100000;
        _delay_ms(250);

        if (flag_PD7) {
            PORTD |= 0b10000000;
            _delay_ms(1000);
            PORTD &= ~(0b10000000);
            flag_PD7 = 0;
        }

        if (flag_PD6) {
            PORTD |= 0b01000000;
            _delay_ms(500);
            PORTD &= ~(0b01000000);
            flag_PD6 = 0;
        }

        if (flag_PB1) {
            PORTB |= 0b00000010;
            _delay_ms(2000);
            PORTB &= ~(0b00000010);
            flag_PB1 = 0;
        }
    }
}
 
