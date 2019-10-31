//MERIMI Mohammed 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

#define n 30
#define m 2
#define k 3
#define NUMTHREADS 3

int A[n][m],B[m][k],C[n][k];
void *produit_matriciel(void * num_thread){
	long tid;
	tid=*((long*)(&num_thread));
	int debut,fin;
	
	debut=tid*(n/NUMTHREADS);
    fin=debut+(n/NUMTHREADS)-1;
    if(tid==NUMTHREADS-1){
      fin=n-1;
    }
	
	printf("threard numero  %d \n",num_thread);
	printf("debut = %d ,fin = %d \n",debut,fin);
    int i,j,l;
    for(i=debut;i<fin;i++){
    	for(j=0;j<m;j++){
    		C[i][j]=0;
    		for(l=0;l<k;l++){
    		    C[i][j]=C[i][j]+A[i][l]*B[l][j]	;
			}
		}
	}
	pthread_exit(NULL);	
}


int main(){
	pthread_t threads[NUMTHREADS]; 
    int rc; 
    int i,j;
    long th;
    srand(time(NULL));
    void *ret ;
    double debut,fin;
    
    srand(time(NULL));
    debut=clock();
    printf("matrice A : \n");
    for(i=0;i<n;i++){
    	for(j=0;j<m;j++){
    		A[i][j]=rand()%3;
    		printf("%d \t",A[i][j]);
		}
    	
	}
	
	printf("\n");
	
	printf("matrice B : \n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			B[i][j]=rand()%3;
			printf("%d \t",B[i][j]);
		}
	}
	
	printf("\n");
	
	for(th= 0; th<NUMTHREADS ; th++){ 

	      rc = pthread_create(&threads[th], NULL, produit_matriciel, (void *)th); 	
	     (void)pthread_join(threads[th],&ret);      
	      if (rc){ 
                    	printf("Erreur de creation de thread; code erreur = %d\n", rc); 
	            	exit(-1); 
              } 
	 }
	
	for(th = 0; th < NUMTHREADS; th++){ 
	      (void)pthread_join(threads[th],&ret);
         }
	
	printf("\n");
	printf("matrice C :\n");
	for(i=0;i<n;i++){
		for(j=0;j<k;j++){
			printf("%d  \t",C[i][j]);
		}
	}
	printf("\n");
	fin=clock();
    printf("temps parallele=%f\n", (double)(fin-debut)/CLOCKS_PER_SEC); 
    
    
    
    //sequentiel 
    int l;
    debut=clock();
    printf("matrice A : \n");
    for(i=0;i<n;i++){
    	for(j=0;j<m;j++){
    		A[i][j]=rand()%3;
    		printf("%d \t",A[i][j]);
		}
    	
	}
	printf("\n");
	
	printf("matrice B : \n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			B[i][j]=rand()%3;
			printf("%d \t",B[i][j]);
		}
	}
	
	printf("\n");
	
    for(i=0;i<n;i++){
    	for(j=0;j<m;j++){
    		C[i][j]=0;
    		for(l=0;l<k;l++){
    		    C[i][j]=C[i][j]+A[i][l]*B[l][j]	;
			}
		}
	}
    printf("\n");
	printf("partie sequentiel");
	printf("\n");
	printf("matrice C :\n");
	for(i=0;i<n;i++){
		for(j=0;j<k;j++){
			printf("%d \t",C[i][j]);

		}
	}
	fin=clock();
    printf("temps execution sequetiel=%f\n",  (double)(fin-debut)/CLOCKS_PER_SEC); 
	
	
	return 0 ;
	
	
	
	
}
