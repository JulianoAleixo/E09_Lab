/*

Máquina de estado do funcionamento de uma lâmpada

|----------------------|         |---------------------| 
|         ON           |         |         OFF         |
|  logic_state = 1     | ----->  |  logic_state = 0     | 
|----------------------|         |---------------------|  
          ^                                 |
          |                                 |
          |                                 |
          |---------------------------------|

*/


#include <stdio.h>

#define ON 1
#define OFF 0

unsigned char logic_state = OFF;

int main()
{
    char input;
    do
    {
        printf("\n");
        switch (logic_state)
        {
        case ON:
            printf("Lampada ligada...\n");
            logic_state = OFF;
            break;
        case OFF:
            printf("Lampada desligada...\n");
            logic_state = ON;
            break;
        default:
            break;
        }
        printf("Deseja mudar estado? (s/n)\n");
        scanf("%c", &input);
    } while (input != 'n');

    return 0;
}