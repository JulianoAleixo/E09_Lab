#define FOSC    16000000U
#define BAUD    9600
#define MYUBRR  FOSC/16/BAUD - 1

#define GREEN_LED   PB0
#define RED_LED     PB1

char msg_rx[2];
int pos_msg_rx = 0;
int msg_rx_length = 1;

void UART_Init(unsigned int ubrr);
void UART_Transmit(char *data);

int main(void) {
    UART_Init(MYUBRR);
    sei();

    DDRB |= (1<<GREEN_LED) | (1<<RED_LED);

    UART_Transmit("Envie 9 ou 8\n");

    while(1) {
        char cmd = msg_rx[0];

        if (cmd == '9') {
            PORTB |=  (1<<RED_LED);
            PORTB &= ~(1<<GREEN_LED);
            UART_Transmit("Vermelho ON, Verde OFF\n");
        }

        if (cmd == '8') {
            PORTB |=  (1<<GREEN_LED);
            PORTB &= ~(1<<RED_LED);
            UART_Transmit("Verde ON, Vermelho OFF\n");
        }
    }
}

ISR(USART_RX_vect) {
    msg_rx[pos_msg_rx++] = UDR0;
    if (pos_msg_rx == msg_rx_length)
        pos_msg_rx = 0;
}

void UART_Transmit(char *data) {
    while (*data != 0) {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = *data++;
    }
}

void UART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}
