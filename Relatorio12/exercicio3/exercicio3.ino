#define FOSC    16000000U
#define BAUD    9600
#define MYUBRR  FOSC/16/BAUD - 1

char msg_rx[4];
int pos_msg_rx = 0;
int msg_rx_length = 3;

void UART_Init(unsigned int ubrr);
void UART_Transmit(char *data);
void PWM_Init(void);

int main(void) {
    UART_Init(MYUBRR);
    PWM_Init();
    sei();

    UART_Transmit("Envie DUTY (000 a 100):\n");

    while(1) {
        int duty =
            (msg_rx[0]-48)*100 +
            (msg_rx[1]-48)*10  +
            (msg_rx[2]-48)*1;

        if (duty >= 0 && duty <= 100) {
            OCR0A = (duty * 255) / 100;
        }
    }
}

ISR(USART_RX_vect) {
    msg_rx[pos_msg_rx++] = UDR0;

    if (pos_msg_rx == msg_rx_length) {
        pos_msg_rx = 0;
    }
}

void PWM_Init(void) {
    DDRD |= (1<<PD6);

    TCCR0A = (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
    TCCR0B = (1<<CS01); 
    OCR0A = 0;
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
