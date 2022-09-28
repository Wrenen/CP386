/*
-------------------------------------
File:    threads.c
Project: Assignment 2
-------------------------------------
Author:  Wrenen D'Cunha
ID:      200590590
Email:   dcun0590@mylaurier.ca
Version  21-06-2022
-------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <pthread.h>


void *thread_fucn(){
    for (int i = 0;i < 5;i++){
        printf("I am a Custom Thread Function Created By user.\n");
        sleep(1);
    }
    pthread_exit(0);
}

int main(){
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    printf("This program would create threads\n");

    if (pthread_create(&tid, &attr, thread_fucn, NULL) != 0){
        return 1;
    } else{
        printf("Custom thread created Successfully\n");
    }

    for(int i = 0; i < 5; i++){
        printf("I am the process thread created by the compiler by default.\n");
        sleep(1);
    }
    if(pthread_join(tid, NULL) != 0){
        return 2;
    }

    /* Since the threads are running in parallel the complition time of each thread is unknow and the order of the print
       statements are not the same everytime the program runs. */
    return 0;
}
