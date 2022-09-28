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
    int ppid;
    printf("The Zombie process ppid is: ");
    fscanf(stderr,"%d",&ppid);   
    system ("ps -l| grep -w Z| tr -s ' '| cut -d ' ' -f 5");
    fscanf(buffer,"%d",&ppid);
    fgets(ppid,50,stderr);
    printf("PPID: %d\n", ppid);
}