#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*number of philosphers*/
#define np 5

/*forks being used*/
pthread_mutex_t forks[np];

/*philosphers*/
pthread_t philosphers[np];

void *eat(int i)
{
	int ne=rand()%5+1;
	printf("Philospher %i will eat %d times\n", i, ne);
	sleep(3);
	printf("Philospher %i is thinking\n",i);
	
	/*	for (int j=0; j > ne; j++){*/
	/*while(1){*/
		pthread_mutex_lock(&forks[i]);
		pthread_mutex_lock(&forks[(i+4)%5]);
		printf("Philospher %i is eating\n", i);
		pthread_mutex_unlock(&forks[i]);
		pthread_mutex_unlock(&forks[(i+4)%5]);
		printf("philospher %i is done eating\n", i);
	}

	return(NULL);
}

int main(){
	int i;
	srand(time(NULL));
	for (i=0; i < np ; i++){
		pthread_mutex_init(&forks[i],NULL);
		pthread_create(&philosphers[i], NULL, (void *)eat, (void *)i);
	}

	for (i=0; i < np ; i++){
		pthread_join(philosphers[i],NULL);
	}

	for (i=0; i < np ; i++){
		pthread_mutex_destroy(&forks[i]);
	}
}
