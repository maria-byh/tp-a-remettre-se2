#include <pthread.h>
#include <stdio.h>
int t;
int A[100][100],B[100][100],C[100][100],E[100][100];
int n,m,k;


void remplir_matrice(){

	int i,j;

	printf("Entrez le nombre de lignes et de colones de la matrice A:\n");
	scanf("%d%d",&n,&m);
	   
	printf("Entrez les elements de la matrice A\n");

	for(i=0; i<n; i++)
   		for(j=0; j<m; j++)
     	scanf("%d",&A[i][j]);
    
    printf("Le nombre de lignes est %d entrez le nombre de colones de la matrice B:\n",m);
	scanf("%d",&k);
	
	printf("Entrez les elements de la matrice B\n");

	for(i=0; i<m; i++)
		for(j=0; j<k; j++)
	    scanf("%d",&B[i][j]);
        
}

void afficher_matrice(int D[100][100], int a, int b){

  	int i,j;
  
    for(i=0; i<a; i++){
      	for(j=0; j<b; j++)
      	printf("\t%d\t",D[i][j]);
    }
    printf("\n");
      
}

//thread pour calculer le produit de chaque élément de la matrice 
void * fonc1(void *arg){

	int i,j,l;
  
	for(i=0; i<n; i++){
	    for(j=0; j<k; j++){
	    	C[i][j] = 0;
	    	for(l=0; l<m; l++){
	    		C[i][j] += A[i][l] * B[l][j];
	    	}
	    }  
	}
   printf("\nle produit de deux matrices est : \n");
   afficher_matrice(C,n,k);
}

//thread pour calculer le produit de chaque ligne de la matrice
void * fonc2(void *arg){
	
	int i = (void*)arg;
	int j,l;
	
	   	if (i==0) {
		    printf("\nla matrice C contient %d lignes et %d colognes:",n,k);
		}
		printf("\nle produit de la ligne %d est : \n",i+1);
		
	    for(j=1; j<=k; j++){
	    	E[i][j] = 0;
	    	for(l=0; l<m; l++){
	    		E[i][j] += A[i][l] * B[l][j-1];
	    	}
			printf("\t%d\t",E[i][j]);
	    }  
}

int main(){
	
	int i;
	pthread_t thread1, thread2;
	remplir_matrice();
	
	//la création du premier thread qui calcul le produit de chaque élément de la matrice 
	pthread_create(&thread1, NULL, fonc1, NULL);
    
	//la création du dexième thread qui calcul le produit de chaque ligne de la matrice 
	for (i=0; i<n; i++) {
		pthread_create(&thread2, NULL, fonc2, (void*)i);
	}
	
      
      
    pthread_join(thread1,NULL);
    for (i=0; i<n; i++) {
		pthread_join(thread2,NULL);
	}
     
       
   
   return 0;
}
