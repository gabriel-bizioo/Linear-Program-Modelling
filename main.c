#include <stdio.h>

#define PESO 0
#define VOLUME 1
#define GANHO 2
#define DENSIDADE 3


int main() {
    int i, j;
    int k, n;

    scanf("%d %d", &k, &n);

    // Mapeia os dados dos compartimentos (peso e volume) e dos carregamentos
    // (peso, volume, ganho e m3/tonelada) em suas respectivas matrizes
    float compartimentos[k][2];
    float carregamentos[n][4];

    for(i = 0; i < k; i++)
        scanf("%f %f", &compartimentos[i][PESO], &compartimentos[i][VOLUME]);
    for(i = 0; i < n; i++) {
        scanf("%f %f %f", &carregamentos[i][PESO], &carregamentos[i][VOLUME],
                &carregamentos[i][GANHO]);
        carregamentos[i][DENSIDADE] = carregamentos[i][VOLUME]/carregamentos[i][PESO];
    }

    /* Modela o programa linear no formato de lp_solve,
     de acordo com o tamanho de k e n */

    // Max:
    for(i = 1; i < n; i++)
        printf("%fx%d + ", carregamentos[i-1][GANHO], i);
    printf("%fx%d;\n\n", carregamentos[i-1][GANHO], i);

    // S.T.:
    // Limite de cada compartimento
    for(i = 1; i <= k; i++) {
        for(j = 1; j < n; j++)
            printf("x%d%d + ", j, i);
        printf("x%d%d = y%d;\n", j, i, i);

        for(j = 1; j < n; j++)
            printf("%fx%d%d + ",
                    carregamentos[j-1][DENSIDADE], j, i);
        printf("%fx%d%d <= %f;\n\n",
                carregamentos[j-1][DENSIDADE], j, i, compartimentos[i-1][VOLUME]);

    }

    // Limite da quantidade de carregamento
    for(i = 1; i <= n; i++) {
        for(j = 1; j < k; j++)
            printf("x%d%d + ", i, j);
        printf("x%d%d = x%d;\n", i, j, i);
        printf("x%d <= %f;\n", i, carregamentos[i-1][PESO]);
    }

    // Balanceamento dos pesos dos compartimentos
    printf("\n%fy1 <= 1;\n", 1/compartimentos[0][PESO]);
    for(i = 1; i < k-1; i++)
        printf("%fy%d = %fy%d;\n", 1/compartimentos[i-1][PESO], i,
                1/compartimentos[i][PESO], i+1);
    printf("%fy%d = %fy%d;\n", 1/compartimentos[i-1][PESO], i,
                1/compartimentos[i][PESO], i+1);
}

























