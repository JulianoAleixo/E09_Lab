#include <stdio.h>

void countEvensAndOdds(int numbers[5]) {
    int evens = 0, odds = 0;
    for (int i = 0; i < 5; i++) {
        if (numbers[i] % 2 == 0) {
            evens++;
        } else {
            odds++;
        }
    }

    printf("Quantidade de numeros pares: %d\n", evens);
    printf("Quantidade de numeros impares: %d\n", odds);
}

void countPositivesAndNegatives(int numbers[5]) {
    int positives = 0, negatives = 0;
    for (int i = 0; i < 5; i++) {
        if (numbers[i] >= 0) {
            positives++;
        } else {
            negatives++;
        }
    }

    printf("Quantidade de numeros positivos: %d\n", positives);
    printf("Quantidade de numeros negativos: %d\n", negatives);
}

int main() {
    int quantity;

    while (1) {
        scanf("%d", &quantity);
        if (quantity > 0){
            break;
        }
        printf("[Erro] Quantidade invalida. Entre com um numero inteiro positivo.\n");
    };

    int numbers[5];

    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < 5; j++) {
            scanf("%d", &numbers[j]);
        }

        countEvensAndOdds(numbers);
        countPositivesAndNegatives(numbers);
        printf("\n");
    }
    
    return 0;
}