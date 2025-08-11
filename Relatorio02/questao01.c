/*

|----------------------|         |---------------------| 
|        VERDE         |         |        YELLOW       |
|  traffic_light = 12  | ----->  |  traffic_light = 3  | 
|----------------------|         |---------------------|  
          ^                                 |
          |                                 |
          |                                 |
          |                                 v
          |                      |----------------------| 
          |                      |         RED          |
          |--------------------- |  traffic_light = 15  | 
                                 |----------------------| 

*/

#include <stdio.h>
#include <windows.h>

#define GREEN 12
#define YELLOW 3
#define RED 15

unsigned char traffic_light = GREEN;

int main()
{
    while (1)
    {
        switch (traffic_light)
        {
        case GREEN:
            printf("Semaforo verde.\n");
            Sleep(traffic_light * 1000);
            traffic_light = YELLOW;
            break;
        case YELLOW:
            printf("Semaforo amarelo.\n");
            Sleep(traffic_light * 1000);
            traffic_light = RED;
            break;
        case RED:
            printf("Semaforo vermelho.\n");
            Sleep(traffic_light * 1000);
            traffic_light = GREEN;
            break;
        default:
            break;
        }
    }
    return 0;
}
