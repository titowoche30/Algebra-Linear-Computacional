#include <stdio.h>
#include <stdlib.h>
#include "cblas.h"

//Aloca vetor double com tamanho size
double* aloc(int size){
    double* vector = (double*)malloc(sizeof(double)*size);
    return vector;
}

//Printa matriz de float
void printMf(float* vetor,int n,int esp){
    //Vetor, num de elementos, numero de elementos numa linha(num de colunas)
    for(int i = 1; i <= n; i++){
        printf("%.3f ",vetor[i-1]);
        if(i%esp == 0) printf("\n");
    }
    printf("\n");
}

//Printa matriz de double/
void printMd(double* vetor,int n,int esp){
    //Vetor, num de elementos, numero de elementos numa linha(num de colunas)
    for(int i = 1; i <= n; i++){
        printf("%.3f ",vetor[i-1]);
        if(i%esp == 0) printf("\n");
    }
    printf("\n");
}

//Preenche uma matriz de doubles com o numero num 
double* fillMatrix(int m,int n,double num){
    //linha,coluna,numero
    int size = m*n;
    double *matrix = aloc(size);
    
    if (matrix == NULL){ printf("Deu ruim :( \n"); exit(0); }

    for(int i = 0; i <= size; i++)
       matrix[i] = num;
    
    return matrix;
} 

//Preenche uma matriz de doubless com numeros aleatórios de 0 a 10
double* fillRandMatrix(int m,int n){
    //linha,coluna
    int size = m*n;
    double *matrix = aloc(size);
    
    if (matrix == NULL){ printf("Deu ruim :( \n"); exit(0); }

    for(int i = 0; i <= size; i++)
       // matrix[i] = ((float)rand()) / RAND_MAX;
        matrix[i] = rand() % 10;
    
    return matrix;
} 

void acesso(float* matrix,int i,int j,int n){
    //n = número de colunas da matriz
    printf("%d,%d = %f \n",i,j,matrix[i*n + j]);
}


//Multiplica um vetor por um escalar
float* vetorEscalar(int n,float escalar,float *vetor,int incx,int print){
   //N de elementos no vetor,escalar, vetor, espacamento, printar ou nao
   cblas_sscal(n, escalar, vetor,incx);

   if(print==1){
      for(int i = 0; i < n; i++)
         printf("x%d = %f\n",i,vetor[i]);
      printf("\n");
   }   
   return vetor;
}

//Efetua o  produto interno de vetores
float prodInterno(int n,float *vetor1,int inc1,float *vetor2,int inc2,int print){
   //N de elementos nos vetores,vetor1 ,espacamento1,vetor2 ,espacamento2, printar ou n
   float resultado = cblas_sdot(n,vetor1,inc1,vetor2,inc2);

   if(print==1){
    printf("Produto Interno entre:\n");
    printMf(vetor1,n,1);   
    printf("\n e \n");
    printMf(vetor2,n,1);
    printf("= %f\n",resultado);
   }
   return resultado;
}

double* matVec(CBLAS_INDEX order, CBLAS_INDEX trans,int m,int n, 
               double alpha, double* A, int LDA, double* X, int incx, 
               double beta, double* Y,int incy,int print) {
   //
   cblas_dgemv(order,trans,m,n,alpha,A,LDA,X,incx,beta,Y,incy);

   if(print==1){
    printf("Mat Vec entre:\n");
    printMd(A,m*n,n);
    printf("\n e \n");   
    printMd(X,n,1);
    printMd(Y,m,1);
   }
   return Y;
}

double* matMult (CBLAS_INDEX Order,CBLAS_INDEX TransA, CBLAS_INDEX TransB, 
               int m, int n, int k, double alpha, double *A,
               int lda, double *B, int ldb, double beta, 
               double *C, int ldc, int print){
                  
   cblas_dgemm(Order,TransA,TransB,m,n,k,alpha,A,lda,B,ldb,beta,C,ldc);

   if(print==1){
    printf("Mat mult entre:\n");
    printMd(A,m*k,k);
    printf("\n e \n");   
    printMd(B,k*n,n);
    printMd(C,m*n,n);
   }
   return C;
}
             

int main ( ){
   enum CBLAS_ORDER order;
   enum CBLAS_TRANSPOSE trans;
   enum CBLAS_TRANSPOSE transA;
   enum CBLAS_TRANSPOSE transB;

   //order = CblasColMajor;
   //trans = CblasNoTrans;

   double *a, *x, *y, *y2;
   double alpha, beta;
   int m,n,k,lda,ldb,ldc ,incx, incy, i;

   m = 3; 
   n = 3;
   k = 3; 
   lda = 4; /* Leading dimension of 5 * 4 matrix is 5 */
   incx = 1; 
   incy = 1;
   alpha = 1;
   beta = 0;

   //a = (double *)malloc(sizeof(double)*m);
   //x = (double *)malloc(sizeof(double)*m*n);
   //y = (double *)malloc(sizeof(double)*m);
   //y2 = (double *)malloc(sizeof(double)*m);

   //x = fillRandMatrix(m,n);
   //y = fillMatrix(m,1,2);
   
   //printMd(x,m*n,n);
   //printMd(y,m*1,1);
   
   /*--------------
   //printMf(y,m*n,n);
   //y=vetorEscalar(m*n,alpha,x,incx,1);
   //printMf(x,5,1);

   //float prodInter = prodInterno(3,x,incx,y,incy,1);
   //printf("Produto interno= %f\n",prodInter);
   -------------------*/
   
   /*---------------
   lda = m;
   order = CblasRowMajor;
   trans = CblasNoTrans;
   a = matVec(order,trans,m,n,alpha,x,lda,y,1,beta,y2,1,1);
   printMd(a,m,1);
   ---------------*/


   double *A = aloc(m*k);
   double *B = aloc(k*n);
   double *C = aloc(m*n);
   order = CblasRowMajor;
   transA = CblasNoTrans;
   transB = CblasNoTrans;
   lda = 3;
   ldb = 3;
   ldc = 3;
   beta = 0;
   alpha = 1;
   A = fillRandMatrix(m,k);
   B = fillRandMatrix(k,n);

   C = matMult(order,transA,transB,m,n,k,alpha,A,lda,B,ldb,beta,C,ldc,1);
   printMd(C,m*n,n);

   free(a);
   free(x);
   free(y);
   free(y2);
   free(A);
   free(B);
   free(C);
   return 0;
}
