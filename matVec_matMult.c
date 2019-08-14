#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <time.h>

//Aloca vetor double com tamanho size
double* aloc(int size){
    double* vector = (double*) calloc(size,sizeof(double));
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

//Printa matriz de double
void printMf(double* vetor,int n,int esp){
    //Vetor, num de elementos, numero de elementos numa linha(num de colunas)
    for(int i = 1; i <= n; i++){
        printf("%.3f ",vetor[i-1]);
        if(i%esp == 0) printf("\n");
    }
    printf("\n");
}

//Preenche uma matriz de doubles com numeros aleatórios de 0 a 10
double* fillRandMatrix(int m,int n){
    //linha,coluna
    int size = m*n;
    double *matrix = aloc(size);
    
    if (matrix == NULL){ printf("Deu ruim :( \n"); exit(0); }

    for(int i = 0; i <= size; i++)
       // matrix[i] = ((double)rand()) / RAND_MAX;
        matrix[i] = rand() % 10;
    
    return matrix;
} 

//printa matriz[i][j]
void acesso(double* matrix,int i,int j,int n){
    //n = número de colunas da matriz
    printf("%d,%d = %f \n",i,j,matrix[i*n + j]);

}

//Soma duas matrizes
double* matSum(double* matrix0,double* matrix1,double* b,int l0, int c0,  int l1, int c1){
    if ((l0 != l1) || (c0!=c1)){ printf("Matrizes de tamanhos diferentes"); exit(0); }

    int size = l0 * c0;
    for (int i = 0; i < size; i++)
        b[i] = matrix0[i] + matrix1[i];
    return b;

}


//Multiplicacao matriz com vetor
double* matVec(double* matrix,double* vetor,double* b,int m,int n,int p){
    //matriz,vetor,linhas da matriz,colunas da matriz,linhas do vetor
    if (n != p){ printf("Colunas da matriz != Linhas do vetor"); exit(0); }

    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            b[i] = b[i] + matrix[i*n +j] * vetor[j];
    
    return b;
}

//Multiplicação de matrizes
void matMult(double* matrix0,double* matrix1,double* b,int l0, int c0,int l1,int c1){
    //Linha e coluna da matriz 0 e da matriz1 
    if (c0 != l1){ printf("Colunas da matriz0 != Linhas da matriz1"); exit(0); }

    for(int i = 0; i < l0; i++)
        for(int j = 0; j < c1; j++)
            for(int k = 0; k < c0; k++)
                b[i*c1 +j] += matrix0[i*c0 + k] * matrix1[k*c1 +j];

          
   // return b;
}

//Multiplicação de matrizes quadradas por bloco
void matMultBlock(double* matrix0,double* matrix1,double* b,int n,int s){
//Matrizes,dimensão e tam do bloco
    if (n % s) return;                      // Se s não for divisor de n(se for tratado antes,nunca vai entrar aqui)
    
    //dimensão dos blocos
    int BS = s * s;
    //num de blocos
    int r = n/s;
    
    for (int i = 0; i < r; i++)
        for (int j = 0; j < r; j++)
            for (int k = 0; k < r; k++){
                double* aik = &(matrix0[i * r * BS + k * BS]);
                double* xkj = &(matrix1[k * r * BS + j * BS]);
                double* bij = &(b[i * r * BS + j * BS]);
                matMult(aik,xkj,bij,s,s,s,s);
            }
}

int main() {
    srand(time(NULL));
    int samples = 5;
    int dim = 2000;
    printf("AAAAAAAAAAA\n"); 
    double* matrix = fillRandMatrix(dim,dim);
    double* matrix1 = fillRandMatrix(dim,dim);
    double* b = aloc(dim*dim);
    
    printf("dim=%d \namostras=%d\n",dim,samples);
    //printMf(matrix,dim*dim,dim);
    //printMf(matrix1,dim*dim,dim);

    clock_t t = clock();
    for (int i = 0; i < samples; i++)
        matMult(matrix,matrix1,b,dim,dim,dim,dim);
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("0 - %.5f segundos \n",time_taken / samples);
    
    for (int bs = 1; bs <= dim/2; bs++){
        if(dim % bs) continue;                  //Se nao conseguir dividir igualmente, vai pra proxima iteracao
        clock_t t = clock();
        for (int j = 0; j < samples; j++)
            matMultBlock(matrix,matrix1,b,dim,bs);
        t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("%d - %.5f segundos \n",bs,time_taken / samples);
    }
    
    free(matrix);
    free(matrix1);
    return 0;
}
