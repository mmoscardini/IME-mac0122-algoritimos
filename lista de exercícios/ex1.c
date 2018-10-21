#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *Histograma(int **M, int m, int n){
    int i, j;
    int *L=NULL;

    L = (int *)calloc(256, sizeof(int));

    for (i=0;i<m;i++){
        for (j=0;j<n;j++){
            L[M[i][j]] += 1;
        }
    }

    return L;
}

int main (){
    int nlinhas, ncolunas, i, j;
    int **M = NULL;
    int *hist;
    
    scanf("%d %d", &nlinhas, &ncolunas);
    M = (int **)malloc(sizeof(int *)*nlinhas);
    if(M == NULL){
        printf("Erro ao alocar a matriz\n");
        return 0;
    }
    for (i=0; i< nlinhas ;i++){
        M[i] = (int *)malloc(sizeof(int)*ncolunas);
    };

    for (i=0;i<nlinhas;i++){
        for (j=0;j<ncolunas;j++){
            M[i][j] = rand() % 256;
            printf("%3d ", M[i][j]);
        }
        printf("\n");
    }
    
    hist = Histograma(M, nlinhas, ncolunas);

     for (i=0;i<256;i++){
        printf("%d ", hist[i]);
    };
    return 0;
}