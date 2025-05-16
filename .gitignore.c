#include <stdio.h>

int main() {
    float n1, n2, r;
    char op;

    printf("Digite o 1° numero: ");
    scanf("%f", &n1);
    
    printf("Digite o 2° numero: ");
    scanf("%f", &n2);
    
    printf("Escolha a operacao (+, -, *, /): ");
    scanf(" %c", &op);

    switch(op) {
        case '+': r = n1 + n2; break;
        case '-': r = n1 - n2; break;
        case '*': r = n1 * n2; break;
        case '/':
            if(n2 != 0) r = n1 / n2;
            else { printf("Erro: divisao por zero!\n"); return 1; }
            break;
        default: printf("Operacao invalida!\n"); return 1;
    }

    printf("Resultado: %.2f %c %.2f = %.2f\n", n1, op, n2, r);
    return 0;
}
