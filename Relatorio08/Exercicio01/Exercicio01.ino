/*
    Juliano Moreira Aleixo
    GES 501
    https://julianoaleixo.dev
*/

#define LED_VERMELHO (1 << PD6)
#define LED_AMARELO (1 << PD7)
#define BOTAO_S1 (1 << PB0)
#define BOTAO_S2 (1 << PB1)

volatile int8_t esteira1 = 0b10101100, esteira2 = 0;  // 0b00000000

int main() {
    DDRD |= LED_VERMELHO + LED_AMARELO;
    PORTB |= BOTAO_S1 + BOTAO_S2;

    EICRA &= ~(1 << ISC00);
    EICRA |= (1 << ISC01);
    EIMSK |= BOTAO_S1;

    PCICR = (1 << PCIE0);
    PCMSK0 |= BOTAO_S2;

    sei();

    while(1) {
    }

    return 0;
}

ISR(INT0_vect) {
    while (esteira1 != 0) {
        if (esteira1 & 0b10000000) {
            PORTD |= LED_VERMELHO;
            esteira2 = (esteira2 << 1) | 1;
        } else {
            PORTD &= ~LED_VERMELHO;
            esteira2 = (esteira2 << 1);
        }

        esteira1 <<= 1;
        _delay_ms(500);  // Tempo de movimentação simulado
    }

    PORTD &= ~LED_VERMELHO;
}

ISR(PCINT0_vect){
    if (!(PINB & BOTAO_S2)) {
        while (esteira2 != 0) {
            if (esteira2 & 0b00000001) {
                PORTD |= LED_AMARELO;
            } else {
                PORTD &= ~LED_AMARELO;
            }

            esteira2 >>= 1;
            _delay_ms(500);  // Tempo de movimentação simulado
        }

        PORTD &= ~LED_AMARELO;
    }
}