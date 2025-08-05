#include <stdio.h>

int main() {
    int number;

    while (1) {
        scanf("%d", &number);
        if (number <= 50 && number >= 0) {
            break;
        }
        printf("[Erro] Valor invalido. Digite um numero entre 0 e 50.\n");
    }

    for (int i = number - 1; i > 0; i--) {
        int module = number % i;
        printf("O resto da divisao de %d por %d: %d\n", number, i, module);
    }
}