#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_CARACTERES 64
#define MAX_DIRECOES 4

typedef struct Ponto{
    int x;
    int y;
}Ponto;

void forceCorrection(char *number);
int getInputNumber(int argc, char **argv);
void getPredictedPoint(Ponto *ponto, int nthpoint);
void setCoordenadas(Ponto *ponto, int x, int y);

int main(int argc, char **argv){
    int numero = 0;
    Ponto ponto;

    ponto.x = 0;
    ponto.y = 0;

    numero = getInputNumber(argc, argv);
    if (numero == -1) return -1;

    printf("Numero: %d\n", numero);

    getPredictedPoint(&ponto, numero);

    printf("Ponto: (%d, %d)\n", ponto.x, ponto.y);

    return 0;
}

inline void setCoordenadas(Ponto *ponto, int x, int y){    
    ponto->x = x;
    ponto->y = y;
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
        numero = atoi(buffer) / 10;
    } else{
        printf("Digite o n-ésimo ponto: ");
        fgets(buffer, MAX_CARACTERES, stdin);
        forceCorrection(buffer);
        numero = atoi(buffer) / 10;
    }

    return numero;
}

//feito baseado em https://math.stackexchange.com/questions/4688548/what-is-an-algorithm-to-spiral-outwards-from-0-0-in-increments-of-1

//RANT: O QUE SERÁ ESCRITO ABAIXO NÃO É DOCUMENTAÇÃO
/*
    A distância começa em 1
    Existem ciclos de crescimento e decrescimento
    Cada distância repete duas vezes
    Sobe, esquerda, desce, direita
*/
void getPredictedPoint(Ponto *ponto, int nthpoint){
    int x,y, nro_segmentos, semiciclo, i, j;
    Ponto aux;
    bool acabou = false;

    const Ponto direcoes[MAX_DIRECOES] = {
        {0,1},
        {-1,0},
        {0,-1},
        {1,0}
    };

    x = y = 0;
    nro_segmentos = 1;
    semiciclo = 0;
    i = 1;

    //printf("Para k = %d, temos (%d, %d)\n", k, ponto->x, ponto->y);
    if (nthpoint == 0){
        return;
    }

    while(true){
        aux = direcoes[semiciclo % 4];
        
        for (j = 1; j <= nro_segmentos; j++){
            x += aux.x;
            y += aux.y;
            if (i++ == nthpoint){
                acabou = true;
                break;
            }
        }

        if (acabou) break;

        if ((semiciclo+1) % 2 == 0)
            ++nro_segmentos;
        
        ++semiciclo;
    }
    
    setCoordenadas(ponto, x, y);
}