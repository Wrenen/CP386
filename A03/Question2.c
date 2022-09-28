#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex;

// Global Data variables.
int a = 5, b = 7;
// Function that access the global data.
void* inc_dec(void *arg) {
	//wait for other threads to finish
	sem_wait(&mutex);

	printf("Read value of 'a' global variable is: %d\n", a);
	printf("Read value of 'b' global variable is: %d\n", b);
	sleep(1);
	a = a + 1;
	b = b - 1;
	printf("Updated value of 'a' variable is: %d\n", a);
	printf("Updated value of 'b' variable is: %d\n", b);

	//signal the completion of current thread
	sem_post(&mutex);
	return 0;
}
int main() {
	// Intializing the semaphore variable
	sem_init(&mutex, 0, 1);

	// Creating the thread instances.
	pthread_t t1, t2, t3;
	pthread_create(&t1, NULL, inc_dec, NULL);
	pthread_create(&t2, NULL, inc_dec, NULL);
	pthread_create(&t3, NULL, inc_dec, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	//Destroying seamphore variable when complete
	sem_destroy(&mutex);

	return 0;
}
