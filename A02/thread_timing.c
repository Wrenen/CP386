#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>

void logStart(char* tID);//function to log that a new thread is started
void logFinish(char* tID);//function to log that a thread has finished its time

void startClock();//function to start program clock
long getCurrentTime();//function to check current time since clock was started
time_t programClock;//the global timer/clock for the program

typedef struct thread //represents a single thread
{
	char tid[4];//id of the thread as read from file
//add more members here as per requirement
	int start;
	int life;
	bool flag;

} Thread;

pthread_t new_pthread(void *func, void *param);

void* threadRun(void* t);//the thread function, the code executed by each thread
int readFile(char* fileName, Thread** threads);//function to read the file content and build array of threads

int main(int argc, char *argv[])
{
	if(argc<2)
	{
		printf("Input file name missing...exiting with error code -1\n");
		return -1;
	}

    //you can add some suitable code here as per problem specification
	Thread *threads;

	int num_threads = readFile(argv[1], &threads);
	pthread_t tids[num_threads];

	startClock();

	bool started = false;
	int e;
	long now;

	while(!started)//put a suitable condition here to run your program
	{
	    //write suitable code here to run the threads
		started = true;
		now = getCurrentTime();

		for (e = 0; e < num_threads; e++) {
			if (threads[e].flag && now == threads[e].start) {
				threads[e].flag = true;
				tids[e] = new_pthread(threadRun, &threads[e]);
			}
			started = started && threads[e].flag;
		}
	}

	for (e = 0; e < num_threads; e++) {
		pthread_join(tids[e], NULL);

	}

	return 0;
}

int readFile(char* fileName, Thread** threads)//use this method in a suitable way to read file
{
	FILE *in = fopen(fileName, "r");
	if(!in)
	{
		printf("Child A: Error in opening input file...exiting with error code -1\n");
		return -1;
	}

	struct stat st;
	fstat(fileno(in), &st);
	char* fileContent = (char*)malloc(((int)st.st_size+1)* sizeof(char));
	fileContent[0]='\0';
	while(!feof(in))
	{
		char line[100];
		if(fgets(line,100,in)!=NULL)
		{
			strncat(fileContent,line,strlen(line));
		}
	}
	fclose(in);

	char* command = NULL;
	int threadCount = 0;
	char* fileCopy = (char*)malloc((strlen(fileContent)+1)*sizeof(char));
	strcpy(fileCopy,fileContent);
	command = strtok(fileCopy,"\r\n");
	while(command!=NULL)
	{
		threadCount++;
		command = strtok(NULL,"\r\n");
	}
	*threads = (Thread*) malloc(sizeof(Thread)*threadCount);

	char* lines[threadCount];
	command = NULL;
	int i=0;
	command = strtok(fileContent,"\r\n");
	while(command!=NULL)
	{
		lines[i] = malloc(sizeof(command)*sizeof(char));
		strcpy(lines[i],command);
		i++;
		command = strtok(NULL,"\r\n");
	}

	Thread *arr = *threads;
	for(int k=0; k<threadCount; k++)
	{
		Thread sent;
		char* token = NULL;
		//int j = 0;
		token = strtok(lines[k], ";");
		strcpy(sent.tid, token);
		token = strtok(NULL, ";");
		sent.start = atoi(token);
		token = strtok(NULL, ";");
		sent.life = atoi(token);
		sent.start = false;
		arr[k] = sent;

	}
	return threadCount;
}

//Aux function
pthread_t new_pthread(void *f, void *p) {

	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	if (pthread_create(&tid, &attr, f, p)!=0)
		{
			perror("Error");
			exit(1);
		}

	return tid;
}

void logStart(char* tID)//invoke this method when you start a thread
{
	printf("[%ld] New Thread with ID %s is started.\n", getCurrentTime(), tID);
}

void logFinish(char* tID)//invoke this method when a thread is over
{
	printf("[%ld] Thread with ID %s is finished.\n", getCurrentTime(), tID);
}

void* threadRun(void* t)//implement this function in a suitable way
{
	Thread *thread = t;
	logStart(thread ->tid);
	sleep(thread->life);
	logFinish(thread->tid);
	return 0;
}

void startClock()//invoke this method when you start servicing threads
{
	programClock = time(NULL);
}

long getCurrentTime()//invoke this method whenever you want to check how much time units passed
//since you invoked startClock()
{
	time_t now;
	now = time(NULL);
	return now-programClock;
}
