#include <stdio.h>

int main() {
    int quantity;
    float unitPrice, totalPrice;

    while (1) {
        scanf("%d", &quantity);
        if (quantity > 0){
            break;
        }
        printf("[Erro] Quantidade invalida. Entre com um numero inteiro positivo.\n");
    };

    
    if (quantity < 12) {
        unitPrice = 0.8;
    } else {
        unitPrice = 0.65;
    }

    totalPrice = quantity * unitPrice;

    printf("Preco da unidade: R$%.2f\n", unitPrice);
    printf("Preco total: R$%.2f\n", totalPrice);

    return 0;
}
