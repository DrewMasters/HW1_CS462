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
	/*printf("Philospher %i is thinking\n",i);*/
	
	while(1){
		pthread_mutex_trylock(&forks[i]);
		/*printf("Philosopher %i has taken fork %i\n",i,i);
		printf("Philosopher %i is about to try to take fork %i\n",i, (i+1)%5);*/
		if (pthread_mutex_trylock(&forks[(i+1)%5])==0){
			/*printf("got forks on first try\n");
			printf("Philospher %i is eating\n",i);
			printf("forks %i and %i are taken by philoshpher %i\n", i, (i+1)%5 ,i);*/
			pthread_mutex_unlock(&forks[i]);
			/*printf("fork %i is free\n",i);*/
			pthread_mutex_unlock(&forks[(i+1)%5]);
			/*printf("fork %i is free\n",(i+1)%5);*/
			printf("philospher %i is done eating\n", i);
			sleep(rand()%3);
		}
		else{
			/*printf("fork %i already taken philosopher %i giving up fork %i\n", (i+1)%5,i,i);*/
			pthread_mutex_unlock(&forks[i]);
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
