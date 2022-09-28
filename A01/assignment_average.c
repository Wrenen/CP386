#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>

int main(){
    FILE* fp = fopen("sample_in_grades.txt","r");
    int grades[10][6];
    double average;

    for(int i =0; i < 10; i++){
        for(int j =0; j < 6; j++){
            fscanf(fp, "%d", &grades[i][j]);
        }
    }
    /*
    //For testing purposes to print grades martix
    for(int i = 0; i < 10; i++){
        for (int j = 0; j < 6; j++){
            printf("%d ", grades[i][j]);
        }
        printf("\n");
    }
    printf("\n");*/

    pid_t teacher = fork();     //teacher creates one GradTA
    pid_t gta = fork();         //both teacher and GradTA create another child/gta

    if (teacher > 0){
        wait(NULL);             //tells only the teacher to wait for gradTAs to finish
    }
    if (teacher == 0 || gta == 0){

        //for(int col = 0;col < 6; col++){
        pid_t ta = fork();      //each gradTA creates a single child, TA

        if(ta > 0){             //each gradTA waits for TAs to finish
            wait(NULL); 
        }
        
        if (ta == 0){
            wait(0);
            
            for(int col = 0; col < 6; col++){
                int sum = 0;
                for(int row = 0; row < 10; row++){
                    sum += grades[row][col];
                }
                average = (double)sum/10;
                printf("\n");
                printf("Assignment %d - Average = %.6f", col + 1, average);
            }
        }
        //}
    }
    return 0;
}