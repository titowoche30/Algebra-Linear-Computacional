#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <time.h>

//Aloca vetor float com tamanho size
float* aloc(int size){
    float* vector = (float*) malloc(size* sizeof(float));
    return vector;
}

//Printa matriz de inteiros
void printMi(int* vetor,int n,int esp){
    //Vetor, tamanho dele, numero de elementos numa linha
    for(int i = 1; i <= n; i++){
        printf("%d ",vetor[i-1]);
        if(i%esp == 0)
            printf("\n");
    }
    printf("\n");
}

//Printa matriz de float
void printMf(float* vetor,int n,int esp){
    //Vetor, tamanho dele, numero de elementos numa linha
    for(int i = 1; i <= n; i++){
        printf("%.3f ",vetor[i-1]);
        if(i%esp == 0)
            printf("\n");
    }
    printf("\n");
}

//Preenche uma matriz de floats com numeros aleatórios
float* fillRandMatrix(int m,int n){
    //linha,coluna
    int size = m*n;
    float *matrix = aloc(size);
    
    if (matrix == NULL){
        printf("Deu ruim :( \n");
        exit(0);
    }

    for(int i = 0; i <= size; i++)
        matrix[i] = rand() % 10;
    
    return matrix;
} 

//retorna matriz[i][j]
void acesso(float* matrix,int i,int j,int n){
    //n = número de colunas da matriz
    printf("%d,%d = %f \n",i,j,matrix[i*n + j]);

}


//Multiplicacao matriz com vetor por comb.linear
float* matVec(float* matrix,float* vetor,int m,int n,int p){
    //matriz,vetor,linhas da matriz,colunas da matriz,linhas do vetor
    if (n != p){
        printf("Colunas da matriz != Linhas do vetor");
        exit(0);
    }

    float* b = (float*) malloc(m*p*sizeof(float));
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            b[i] = b[i] + matrix[i*n +j] * vetor[j];
    
    return b;
}

float* matMult(float* matrix0,float* matrix1,int l0, int c0,int l1,int c1){
    //Linha e coluna da matriz 0 e da matriz1 
    if (c0 != l1){
        printf("Colunas da matriz0 != Linhas da matriz1");
        exit(0);
    }

    float* b = (float*) malloc(l0*c1*sizeof(float));

    for(int i = 0; i < l0; i++)
        for(int j = 0; j < c1; j++)
            for(int k = 0; k < c0; k++)
                b[i*c1 +j] = b[i*c1 + j] + matrix0[i*c0 + k] * matrix1[k*c1 +j];
                
    return b;
}


int main() {
    //srand(time(NULL));
    int m = 100;
    int n = 100;
    int p = 100;

    float* matrix = fillRandMatrix(m,n);
    float* matrix1 = fillRandMatrix(n,p);
    //float* vector = fillRandMatrix(n,1);

    //printMf(matrix,m*n,n);
    //printMf(matrix1,p*n,p);
    //printMf(vector,n,1);
    clock_t t = clock();  
    //float* b = matVec(matrix,vector,m,n,n); 
    float* b = matMult(matrix,matrix1,m,n,n,p);
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%f segundos \n \n",time_taken);
    //printMf(b,m*p,p);

    free(matrix);
    free(matrix1);
    //free(vector);
    free(b);

    return 0;
}
