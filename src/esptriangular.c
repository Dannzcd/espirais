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
    int x,y, semiciclo, i;
    Ponto aux, ref_left, ref_right;
    bool acabou = false;

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

        while(true){
            aux = direcoes[semiciclo % 3];
            
            switch(semiciclo % 3){
                case 0:
                    while (x < ref_right.x+2 && i < nthpoint){
                        x += aux.x;
                        y += aux.y;
                        ++i;
                    }

                    if (i == nthpoint) acabou = true;
                    else setCoordenadas(&ref_right, x, y);
                    break;
                case 1:
                    while (x > 0 && i < nthpoint){
                        x += aux.x;
                        y += aux.y;
                        ++i;
                    }    

                    if (i == nthpoint) acabou = true;
                    break;
                case 2:
                    while (x > ref_left.x-2 && i < nthpoint){
                        x += aux.x;
                        y += aux.y;
                        ++i;
                    }

                    if (i == nthpoint) acabou = true;
                    else setCoordenadas(&ref_left, x, y);
                    break;
            }
    
            if (acabou) break;
    
            ++semiciclo;
        }
    }
    
    setCoordenadas(ponto, x, y);
}