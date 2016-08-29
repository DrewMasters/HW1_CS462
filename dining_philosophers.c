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
	printf("Philospher %i is thinking\n",i);
	
	while(1){
		pthread_mutex_lock(&forks[i]);
		if (pthread_mutex_trylock(&forks[i])==0){
			printf("Philospher %i is eating\n",i);
			printf("forks %i and %i are taken by philoshpher %i\n", i, (i+4)%5 ,i);
			sleep(1);
			pthread_mutex_unlock(&forks[i]);
			pthread_mutex_unlock(&forks[(i+4)%5]);
			printf("philospher %i is done eating\n", i);
		}
		else{
			sleep(1);
			if (pthread_mutex_trylock(&forks[i])==0){
				printf("Philospher %i is eating\n",i);
				printf("forks %i and %i are taken by philoshpher %i\n", i, (i+4)%5 ,i);
				sleep(1);
				pthread_mutex_unlock(&forks[i]);
				pthread_mutex_unlock(&forks[(i+4)%5]);
				printf("philospher %i is done eating\n", i);
			}
			else
			{
				pthread_mutex_unlock(&forks[i]);
				pthread_mutex_unlock(&forks[(i+4)%5]);
			}
		}
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
