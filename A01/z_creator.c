/*
-------------------------------------
File:    z_creator.c
Project: Assignment 1
-------------------------------------
Author:  Wrenen D'Cunha
ID:      200590590
Email:   dcun0590@mylaurier.ca
Version  21-05-2022
-------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>   

int main(){
    pid_t child_pid = fork();
    //Parent process
    if (child_pid > 0){
        printf("In Parent Process!\n");
        sleep(10); //Puts the Parent to sleep so that we can identify any zombie processes
        //system("ps -l");
        }
        //Child process
    else {
        printf("In Child Process!\n");
        exit(0);
    }
    return 0;
}