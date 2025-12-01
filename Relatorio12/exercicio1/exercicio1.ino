#define FOSC    16000000U
#define BAUD    9600
#define MYUBRR  FOSC/16/BAUD - 1

char msg_tx[20];
char msg_rx[32];
int pos_msg_rx = 0;
int msg_rx_length = 5; 
volatile unsigned long count = 0;

void UART_Init(unsigned int ubrr);
void UART_Transmit(char *data);
void INT0_Init(void);

int main(void) {
    UART_Init(MYUBRR);
    INT0_Init();
    sei();


    while(1) {
        if (msg_rx[0]=='z' &&
            msg_rx[1]=='e' &&
            msg_rx[2]=='r' &&
            msg_rx[3]=='a' &&
            msg_rx[4]=='r') {
            count = 0;
            UART_Transmit("Contagem zerada!\n");
        }
    }
}

ISR(INT0_vect) {
    count++;

    UART_Transmit("Pressionado: ");
    itoa(count, msg_tx, 10);
    UART_Transmit(msg_tx);
    UART_Transmit("\n");
}

ISR(USART_RX_vect) {
    msg_rx[pos_msg_rx++] = UDR0;
    if (pos_msg_rx == msg_rx_length) {
        pos_msg_rx = 0;
    }
}

void UART_Transmit(char *data) {
    while (*data != 0) {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = *data;
        data++;
    }
}

void UART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

void INT0_Init(void) {
    EICRA = (1<<ISC01);   
    EIMSK = (1<<INT0);    
    DDRD &= ~(1<<PD2);    
    PORTD |= (1<<PD2);    
}
