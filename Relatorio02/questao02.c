/*
                (BUTTON_ON=1)                 (BUTTON_ON=1) 
        +------------------------+     +------------------------+
        |                        v     v                        |
+-------------------+     +-------------------+     +-------------------+     +-------------------+
| Estado 0          |     | Estado 1          |     | Estado 2          |     | Estado 3          |
| RED_OFF           |     | RED_ON            |     | RED_OFF           |     | RED_ON             |
| GREEN_OFF         |     | GREEN_OFF         |     | GREEN_ON          |     | GREEN_ON           |
|                   |     |                   |     |                   |     |                   |
+-------------------+     +-------------------+     +-------------------+     +-------------------+
        ^                                                        |
        |                                                        |
        +--------------------------------------------------------+
        
                      (BUTTON_ON=1 após Estado 3 → Estado 0)

*/

#define BUTTON_ON  (PIND & 0b00010000)

#define LED_RED_ON   PORTD = PORTD | 0b10000000
#define LED_RED_OFF  PORTD = PORTD & ~(0b10000000)
#define LED_GREEN_ON PORTD = PORTD | 0b00100000
#define LED_GREEN_OFF PORTD = PORTD & ~(0b00100000)

#define DELAY _delay_ms(500)

char estado = 0;

int main(void)
{
    DDRD = DDRD | 0b10100000;   // Configurando pino 5 e 7 como saída
    PORTD = PORTD | 0b00010000; // Habilita resistor de PULL-UP

    for (;;)
    {
        switch (estado)
        {
        case 0:
            LED_RED_OFF;  // desliga LED do pino 7
            LED_GREEN_OFF; // desliga LED do pino 5
            if (BUTTON_ON)
            {
                estado = estado + 1; // incrementa o estado
                DELAY;                // delay para evitar o Bouncing
            }
            break;

        case 1:
            LED_RED_ON;   // liga LED do pino 7
            LED_GREEN_OFF; // desliga LED do pino 5
            if (BUTTON_ON)
            {
                estado = estado + 1;
                DELAY;
            }
            break;

        case 2:
            LED_RED_OFF;  // desliga LED do pino 7
            LED_GREEN_ON; // liga LED do pino 5
            if (BUTTON_ON)
            {
                estado = estado + 1;
                DELAY;
            }
            break;

        case 3:
            LED_RED_ON;   // liga LED do pino 7
            LED_GREEN_ON; // liga LED do pino 5
            if (BUTTON_ON)
            {
                estado = estado + 1;
                DELAY;
            }
            break;

        default:
            estado = 0;
            break;
        }
    }
}
