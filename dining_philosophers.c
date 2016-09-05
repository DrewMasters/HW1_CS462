#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t *forks;
pthread_t *philosophers;

void *eat(int i);

int main(int argc, char **argv){
	if(argc !=2) {
		printf("Usage: ./dining_philosophers number_of_philosophers\n");
		exit(1);
	}

	int i, np;
	
	np = atoi(argv[1]);

	/*forks being used*/
	forks = malloc(sizeof(pthread_mutex_t)*np);

	/*philosophers*/
	philosophers = malloc(sizeof(pthread_t)*np);
	
	/*initialize random number generator*/
	srand(time(NULL));
	/*for loop creating forks and starting philosophers*/
	for (i=0; i < np ; i++){
		pthread_mutex_init(&forks[i],NULL);
		printf("fork %i created\n", i);
		pthread_create(&philosophers[i], NULL, (void *)eat, (void *)i);
		printf("philosopher %i created\n", i);
	}

	for (i=0; i < np ; i++){
		pthread_join(philosophers[i],NULL);
	}

	for (i=0; i < np ; i++){
		pthread_mutex_destroy(&forks[i]);
	}
}


void *eat(int i)
{
	printf("Philospher %i is thinking\n",i);
	
	while(1){
		/*try to get the "left" fork*/
		pthread_mutex_trylock(&forks[i]);
		/*try to get the "right" fork*/
		if (pthread_mutex_trylock(&forks[(i+1)%5])==0){
			/*if you can get the second fork eat than give up the fork*/
			pthread_mutex_unlock(&forks[i]);
			pthread_mutex_unlock(&forks[(i+1)%5]);
			printf("philospher %i is done eating\n", i);
			/*after eating sleep for a random amount of time between 0 and 3 seconds*/
			sleep(rand()%3);
		}
		else{
			/*if you couldn't get the second fork give up the first fork*/
			pthread_mutex_unlock(&forks[i]);
		}
	}

	return(NULL);
}
