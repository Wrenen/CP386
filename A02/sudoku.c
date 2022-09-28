/*
-------------------------------------
File:    sudoku.c
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

//Data structure to pass multiple variables into thread
typedef struct args
{
    int col;
    int row;
} ARGS;

//Functions
void* row_valid(void* arg);
void* col_valid(void* arg);
void* sub_grid_vaild(void* arg);
pthread_t new_thread(void *func, void *paramters);
void printMatrix(int matrix[9][9]);
int is_valid(int check_array[9]);

int sudoku[9][9];
//Matrices to check if each group of checks is valid
int rows_check[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
int cols_check[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
int sub_grids_check[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};

int main(){
    int temp, i = 0, j =0, sol_valid = 1;
    //FILE* fp = fopen("sample1_in.txt","r");
    FILE* fp = fopen("sample1_in.txt","r");
    
    //Scaning Matrix from file
    while(fscanf(fp, "%d", &temp) != EOF){
        if (temp >= 0){
            sudoku[i][j] = temp;
            j++;
            if(j == 9){
                j = 0;
                i++;
            }
        }
    }

    fclose(fp);

    printf("Sodoku Solution:\n");
    printMatrix(sudoku);
    printf("\n");

    //Creating 9 threads to scan each row
    for(int row = 0; row < 9; row++){
        int *arg = malloc(sizeof(int));
        *arg = row;
        new_thread(row_valid,arg);
    }
    //Creating 9 threads to scan each col
    for(int col = 0; col < 9; col++){
        int *arg = malloc(sizeof(int));
        *arg = col;
        new_thread(col_valid,arg);
    } 

    //Creating 9 threads to scan each sub matrix
    for(int row = 0; row < 9; row+= 3){
        for(int col = 0;col < 9; col+= 3){
            ARGS *anchor = (ARGS *)malloc(sizeof(ARGS));
            anchor->row = row;
            anchor->col = col;
            new_thread(sub_grid_vaild,anchor);
        }
    }

    sleep(3);

    //checking columns matrix
    if(is_valid(cols_check) == 1){
        printf("Columns are valid!\n");
    } else if(is_valid(cols_check) == 0){
        printf("Columns are not valid!\n");
        sol_valid = 0;
    } else{
        printf("Error in Columns!\n");
        goto Error;
    }

    //checking row matrix
    if(is_valid(rows_check) == 1){
        printf("Rows are valid!\n");
    } else if(is_valid(rows_check) == 0){
        printf("Rows are not valid!\n");
        sol_valid = 0;
    } else{
        printf("Error in Rows!\n");
        goto Error;
    }

    //check 3x3 sub grids
    if(is_valid(sub_grids_check) == 1){
        printf("Sub Grids are valid!\n");
    } else if(is_valid(sub_grids_check) == 0){
        printf("Sub Grids are not valid!\n");
        sol_valid = 0;
    } else{
        printf("Error with Sub Grids!\n");
        goto Error;
    }

    //Valid Soulution 

    if (sol_valid == 1){
        printf("\nSolution is Valid!\n");
        goto End;
    } else if (sol_valid == 0){
        printf("\nSolution is Invaild!\n");
        goto End;
    }

    //Error in solution
    Error:
    printf("Error in Solution!\n");

    End:
    return 0;
}

/*  Create new thread fuction   */
pthread_t new_thread(void *func, void *paramters){
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    if (pthread_create(&tid, &attr, func, paramters) != 0){
        fprintf( stderr, "Thread unsuccessful!\n");
        pthread_exit(0);
    }

    return tid;
}

/*  Function to check if a row in a solution contains every number 1 - 9 once (adds to 45)

    Parameter: 
        void*: location of row
*/
void *row_valid(void* arg){
    int row = *(int*)arg;
    int sum = 0;
    for(int i = 0; i < 9; i++){
        sum += sudoku[row][i];
    }

    if (sum == 45){
        rows_check[row] = 1;
    } else{
        rows_check[row] = 0;
    }
    free(arg);
    pthread_exit(0);
}

/*  Function to check if a columns in a solution contains every number 1 - 9 once (adds to 45)

    Parameter: 
        void*: location of col
*/
void *col_valid(void* arg){
    int col = *(int*)arg;
    int sum = 0;
    for(int i = 0; i < 9; i++){
        sum += sudoku[i][col];
    }

    if (sum == 45){
        cols_check[col] = 1;
    } else{
        cols_check[col] = 0;
    }
    free(arg);
    pthread_exit(0);
}

/*  Function to check if a 3x3 sub grid in a solution contains every number 1 - 9 once (adds to 45)

    Parameter: 
        void*: Data structure of 2 ints 
            Row: row location of the sub grid
            Col: col location of the sub grid 
*/
void *sub_grid_vaild(void* arg){
    int *anchor = (int*)arg;
    int col,row,sum = 0;
    row = anchor[0];
    col = anchor[1];
    int index = ((3*row) + col)/3;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            sum += sudoku[row][col];
            col++;
        }
        row++;
        col = anchor[1];
    }

    if (sum == 45){
        sub_grids_check[index] = 1;
    } else{
        sub_grids_check[index] = 0;
    }
    free(arg);
    pthread_exit(0);
}

/*  Prints a 9x9 matrix */
void printMatrix(int matrix[9][9]){

    for(int i = 0; i < 9; i++){
        for(int j =0; j < 9;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

/*  Checks if a valid matrix contains:
        1: Valid, returns 1
        0: Invalid, returns 0
        other: Error case, returns -1
*/
int is_valid(int check_array[9]){
    int valid = 0;
    int i;
    for(i = 0; i < 9; i++){
        if(check_array[i] == 1){
            valid = 1;
        } else if (check_array[i] == 0){
            valid = 0;
            break;
        } else{
            valid = -1;
            break;
        }
    }

    return valid;
}