#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>

void *runner(void* param);
#define N 4
int A[N][N] ={{5, -2, 2, 7}, 
				{1, 0, 0, 3}, 
				{-3, 1, 5, 0}, 
				{3, -1, -9, 4}}; 
  
int adj[N][N];  	// To store adjoint of A[][] 
float inv[N][N]; 	// To store inverse of A[][] 

struct passing{
	int temp[N][N],p,q,n;
};

void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n){ 
    int i = 0, j = 0; 
  
    for (int row = 0; row < n; row++){ 
        for (int col = 0; col < n; col++){ 

            if (row != p && col != q){ 
                temp[i][j++] = A[row][col]; 
  
                if (j == n - 1){ 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 
  
int determinant(int A[N][N], int n){ 

    int D = 0; 

    if (n == 1) 
        return A[0][0]; 
  
    int temp[N][N]; 
  
    int sign = 1;
  
    for (int f = 0; f < n; f++){ 

        getCofactor(A, temp, 0, f, n); 
        D += sign * A[0][f] * determinant(temp, n - 1); 

        sign = -sign; 
    } 
  
    return D; 
} 
  
void adjoint(int A[N][N],int adj[N][N]){ 
    
	if (N == 1){ 
        adj[0][0] = 1; 
        return; 
    } 
  
    int sign = 1, temp[N][N];

	for (int i = 0; i < N; i++){
		pthread_t tid[N];
		struct passing p[N];
		for (int j = 0; j < N; j++){
			p[j].p = i;
			p[j].q = j;
			p[j].n = N;
			pthread_create(&tid[j], NULL, runner, &p[j]);
		}
		for (int j = 0; j < N; j++){
			pthread_join(tid[j], NULL);
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			adj[j][i] = (sign) * (determinant(p[j].temp, N - 1));
		}
	}
}

bool inverse(int A[N][N], float inverse[N][N]){ 

    int det = determinant(A, N); 
    if (det == 0){ 
        printf("Singular matrix, can't find its inverse"); 
        return 0; 
    } 
  
    int adj[N][N]; 
    adjoint(A, adj); 
  
    for (int i=0; i<N; i++) 
        for (int j=0; j<N; j++) 
            inverse[i][j] = adj[i][j]/(float)(det); 
  
    return 1; 
} 

void display(int A[N][N]){ 
    for (int i=0; i<N; i++){ 
        for (int j=0; j<N; j++) 
            printf("%d ",A[i][j]); 
        printf("\n"); 
    } 
} 

void disinv(float A[N][N]){
	for (int i=0; i<N; i++){ 
    for (int j=0; j<N; j++) 
      printf("%f ",A[i][j]); 
    printf("\n"); 
  } 
}

int main(){ 
    
  
    printf("Input matrix is :\n"); 
    display(A); 
  
    printf("\nThe Adjoint is :\n"); 
    adjoint(A, adj); 
    display(adj); 
  
    printf("\nThe Inverse is :\n"); 
    if (inverse(A, inv)) 
        disinv(inv); 

		return 0;
}

void* runner(void* param){
	struct passing *p=(struct passing*)param;
	getCofactor(A, p->temp, p->p,p->q, p->n); 
}