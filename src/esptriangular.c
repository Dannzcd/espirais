#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_CARACTERES 64
#define MAX_DIRECOES 6

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

    getPredictedPoint(&ponto, numero);
    printf("Ponto: (%d, %d)\n", ponto.x, ponto.y);

    /* printf("\nTeste\n");
    setCoordenadas(&ponto, 0, 0);

    for (int i = 0; i <= 20; i++){
        getPredictedPoint(&ponto, i);
        printf("Ponto: (%d, %d)\n", ponto.x, ponto.y);
    } */

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

void getPredictedPoint(Ponto *ponto, int nthpoint){
    int x,y, semiciclo, i, aux_int;
    Ponto aux, ref_left, ref_right;
    //bool acabou = false;

    //O padrão se repete a cada vez que a espiral cruza o eixo y
    const Ponto direcoes[MAX_DIRECOES] = {
        {1,0},
        {-1,1},
        {-1,-1}
    };

    semiciclo = 0;
    i = 4;

    //printf("Para k = %d, temos (%d, %d)\n", k, ponto->x, ponto->y);
    if (nthpoint <= 4){
        switch (nthpoint){
            case 0:
                x = 0;
                y = 0;
                break;

            case 1:
                x = 1;
                y = 0;
                break;
            
            case 2:
                x = 0;
                y = 1;
                break;
    
            case 3:
                x = -1;
                y = 0;
                break;
    
            case 4:
                x = -2;
                y = -1;
                break;
            }
    } 
    else{
        setCoordenadas(&ref_left, -2, -1);
        setCoordenadas(&ref_right, 1, 0);
        x = -2;
        y = -1;

        for (i = 4; i < nthpoint; i++){
            aux_int = semiciclo % 3;
            aux = direcoes[aux_int];
            switch(aux_int){
                case 0:
                    x += aux.x;
                    y += aux.y;

                    if (x == ref_right.x+2){
                        semiciclo++;
                        setCoordenadas(&ref_right, x, y);
                    }
                    break;
                case 1:
                    x += aux.x;
                    y += aux.y;

                    if (x == 0){
                        semiciclo++;
                    }
                    break;
                case 2:
                    x += aux.x;
                    y += aux.y;

                    if (x == ref_left.x-2){
                        semiciclo++;
                        setCoordenadas(&ref_left, x, y);
                    } 
                    break;
            }
        }
    }
    
    setCoordenadas(ponto, x, y);
}
