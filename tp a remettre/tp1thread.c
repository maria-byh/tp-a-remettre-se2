#include <pthread.h>
#include <stdio.h>

void* fonc (void* arg) {
	
	printf("p%d\n", (void*)arg);
}

int main(void) {
	pthread_t tid;
	int i;
	//création du thread
	for (i=0; i<=7; i++){
		pthread_create(&tid, NULL, fonc, (void*)i);
	}
	for (i=1; i<=7; i++){
		pthread_join(tid, NULL);
	}
	
}
