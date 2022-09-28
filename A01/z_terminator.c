/*
-------------------------------------
File:    z_terminator.c
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
    // run z_creator
    system("./z_creator &");

    // lists processes
    system("ps -l");

    printf("\nThe Zombie process ppid is: \n");
    system ("ps -l| grep -w Z| tr -s ' '| cut -d ' ' -f 5");

    system("kill -9 $(ps -l|grep -w Z|tr -s ' '|cut -d ' ' -f 5)");

    printf("\nSucessfully killed zombie process\n\n");
    system("ps -l");
}
