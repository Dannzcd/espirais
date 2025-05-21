//Polyline(l1=Sequência($point(floor(n cos(n*60°)),floor(n sen(n*60°))),n,0,150))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#define EPSILON 1e-10

#define MAX_CARACTERES 64
#define MAX_DIRECOES 6
#define _USE_MATH_DEFINES

#define VERDE "\033[92m"
#define BRANCO "\033[39m"
#define VERMELHO "\033[91m"

typedef struct Ponto{
    int x;
    int y;
}Ponto;

void forceCorrection(char *number);
int getInputNumber(int argc, char **argv);
void getPredictedPoint(Ponto *ponto, int nthpoint);
void setCoordenadas(Ponto *ponto, int x, int y);
void testar(char *nome_arquivo, Ponto *ponto);

int main(int argc, char **argv){
    int numero = 0;
    Ponto ponto;
    char argumento[32];

    ponto.x = 0;
    ponto.y = 0;

    if (argc > 1){
        strcpy(argumento, argv[1]);
    }

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

/* inline long double rad_to_deg(long double rad){
    
} */

void getPredictedPoint(Ponto *ponto, int nthpoint){
    int x, y = 0;
    long double real_x, real_y;

    const long double anuglo_notavel_rad = nthpoint * (60.0 * M_PI / 180.0);

    //Polyline(Sequence(floor(n * cos(n * 60°)), floor(n * sin(n * 60°)), n, 0, 150))
    real_x = nthpoint*cos(anuglo_notavel_rad);
    real_y = nthpoint*sin(anuglo_notavel_rad);
    
    if (fabs(real_x - round(real_x)) < EPSILON) real_x = round(real_x);
    if (fabs(real_y - round(real_y)) < EPSILON) real_y = round(real_y);

    x = floor(real_x+EPSILON);
    y = floor(real_y+EPSILON);

    setCoordenadas(ponto, x, y);
}

/* void testar(char *nome_arquivo, Ponto *ponto){
    FILE *arquivo_teste = NULL;
    char linha[64] = {0};
    char resultado[32] = {0};
    int i = 0;

    arquivo_teste = fopen(nome_arquivo, "r");

    if (arquivo_teste == NULL){
        printf("Arquivo de debug não encontrado\n");
        return;
    }
    
    //teste
    while (fgets(linha, sizeof(linha), arquivo_teste)){
        linha[strlen(linha)-1] = '\0';
        getPredictedPoint(ponto, i++);
        snprintf(resultado, 32, "(%d, %d)", ponto->x, ponto->y);
        printf("%s %s\n", resultado, linha);
    }

    printf("\n%sTESTES BEM SUCEDIDOS!%s\n", VERDE, BRANCO);

    fclose(arquivo_teste);
} */