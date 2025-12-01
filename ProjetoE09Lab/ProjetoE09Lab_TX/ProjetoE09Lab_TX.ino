#include <stdlib.h> // Usado no itoa -> Responsável por transformar INT em ASCII. Casting não é suficiente pois só altera o tipo do dado, não a representação dele.

#define DHT_PIN PD3

volatile uint8_t segundos = 0;


void timer1_init() {
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);
    OCR1A = 15624;
    TIMSK1 |= (1 << OCIE1A);
}

void uart_init() {
    uint16_t ubrr = 103;
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); 
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
}

void adc_init() {
    ADMUX = (1 << REFS0); 
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void int0_init() {
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);
    EICRA |= (1 << ISC01);    
    EIMSK |= (1 << INT0);
}


void uart_tx(char c) {
    while (!(UCSR0A & (1 << UDRE0))); 
    UDR0 = c;
}

void uart_print(char *s) {
    while (*s) uart_tx(*s++);
}


uint16_t adc_read() {
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return (ADCL | (ADCH << 8));
}


uint8_t dht_read_byte() {
    uint8_t r = 0;
    for (uint8_t i = 0; i < 8; i++) {
        while (!(PIND & (1 << DHT_PIN)));
        
        _delay_us(30);

        if (PIND & (1 << DHT_PIN)) { 
            r |= (1 << (7 - i));
        }

        while (PIND & (1 << DHT_PIN));
    }
    return r;
}

uint8_t dht_read(float *hum, float *temp) {
    uint8_t h_i, h_d, t_i, t_d, chk;

    DDRD |= (1 << DHT_PIN);
    PORTD &= ~(1 << DHT_PIN);
    _delay_ms(18);

    PORTD |= (1 << DHT_PIN); 
    _delay_us(30);

    DDRD &= ~(1 << DHT_PIN);

    _delay_us(40);
    if (PIND & (1 << DHT_PIN)) return 1;

    while (!(PIND & (1 << DHT_PIN)));
    while (PIND & (1 << DHT_PIN));

    h_i = dht_read_byte(); // Umidade (Parte Inteira)
    h_d = dht_read_byte(); // Umidade (Parte Decimal)
    t_i = dht_read_byte(); // Temperatura (Parte Inteira)
    t_d = dht_read_byte(); // Temperatura (Parte Decimal)
    chk = dht_read_byte(); // Checksum

    if ((h_i + h_d + t_i + t_d) != chk) return 2;

    *hum = h_i;
    *temp = t_i;

    return 0;
}


int main() {
    float hum = 0, temp = 0;
    uint16_t ldr = 0;
    char buffer[50];

    uart_init();
    adc_init();
    int0_init();
    timer1_init();

    sei();

    uart_print("Sistema iniciado...\r\n");

    while (1) {
        if (segundos >= 10) {
            cli();
            segundos = 0;
            sei();
            
            ldr = adc_read();
            uint8_t status = dht_read(&hum, &temp);

            uart_print("\r\n--- Dados ---\r\n");

            if (status == 0) {
                itoa((int)temp, buffer, 10);
                uart_print("Temperatura: ");
                uart_print(buffer);
                uart_print(" C\r\n");

                itoa((int)hum, buffer, 10);
                uart_print("Umidade: ");
                uart_print(buffer);
                uart_print(" %\r\n");

                itoa((int)ldr, buffer, 10);
                uart_print("Luminosidade: ");
                uart_print(buffer);
                uart_print(" ADC\r\n");
            } else {
                uart_print("Erro no DHT11\r\n");
            }
        }
    }
}


ISR(TIMER1_COMPA_vect) {
    segundos++;
}

ISR(INT0_vect) {
    uart_print("\r\n/health OK\r\n");
    _delay_ms(500);
}
