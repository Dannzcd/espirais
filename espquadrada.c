#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARACTERES 64

typedef struct Ponto{
    int x;
    int y;
}Ponto;

void forceCorrection(char *number);
int getInputNumber(int argc, char **argv);
void getPredictedPoint(Ponto *ponto, int nthpoint);

int main(int argc, char **argv){
    int numero = 0;
    Ponto ponto;

    numero = getInputNumber(argc, argv);
    if (numero == -1) return -1;

    printf("O numero eh %d\n", numero);

    return 0;
}

void forceCorrection(char *number){
    int lenNumber = strlen(number);
    for (int i = 0; i < lenNumber; i++){
        if (number[i] < 48){
            number[i] = '0';
        } else if (number[i] > 56){
            number[i] = '9';
        }
    }
}

int getInputNumber(int argc, char **argv){
    char buffer[MAX_CARACTERES] = {0};
    int numero = 0;
    
    if (argc > 1){
        strcpy(buffer, argv[1]);
        forceCorrection(buffer);
        numero = atoi(buffer);
    } else{
        printf("Digite o n-ésimo ponto: ");
        fgets(buffer, MAX_CARACTERES, stdin);
        forceCorrection(buffer);
        numero = atoi(buffer);
    }

    return numero;
}

void getPredictedPoint(Ponto *ponto, int nthpoint){
    int actualpoint = 0;

}