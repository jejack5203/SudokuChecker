#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


#define MATRIX_SIZE 81 // size of sudoku
#define HEIGHT 9
#define WIDTH 9

typedef struct{
        int ROW;
        int COL;
        int (*matrix)[WIDTH];
} validate;

void *checkRows(void *value);

void *checkCols(void *value);

void *checkSudoku(void *value);


//check if file with sudoku is able to open
int main(int argc, char *argv[]){

        FILE *fp;
        char *mode = "r";
        int matrix[HEIGHT][WIDTH];

        fp = fopen("wss.txt", mode);

        if(fp == NULL){
                fprintf(stderr, "UNABLE TO OPEN THE FILE \n");
                exit(1);
        }
        else{
                for(int col=0; col < HEIGHT; col++){
                  for(int row=0; row < WIDTH; row++){
                                fscanf(fp, "%d", &matrix[col][row]);
                        }
                }
        }
        fclose(fp);

/*      //display sudoku matrix
        printf("CURRENTLY SOLVING --\n");
        //print the sudoku matix
        for (int i=0; i<HEIGHT; i++){
                for(int j=0; j<WIDTH; j++){
                        printf("%d ", matrix[i][j]);
                }
                printf("\n");
        }
        printf("\n");
*/
        validate *check0 = (validate *) malloc(sizeof(validate));
        check0->ROW = 0;
        check0->COL = 0;
        check0->matrix = matrix;

        //check 1st sub matrix
        validate *check1 = (validate *) malloc(sizeof(validate));
        check1->ROW = 0;
        check1->COL = 0;
        check1->matrix = matrix;

        //check 2st sub matrix
        validate *check2 = (validate *) malloc(sizeof(validate));
        check2->ROW = 0;
        check2->COL = 3;
        check2->matrix = matrix;

       //check 3rd sub matrix
        validate *check3 = (validate *) malloc(sizeof(validate));
        check3->ROW = 0;
        check3->COL = 6;
        check3->matrix = matrix;
        
         //check 4rth sub matrix
        validate *check4 = (validate *) malloc(sizeof(validate));
        check4->ROW = 3;
        check4->COL = 0;
        check4->matrix = matrix;

        //check 5th sub matrix
        validate *check5 = (validate *) malloc(sizeof(validate));
        check5->ROW = 3;
        check5->COL = 3;
        check5->matrix = matrix;

        //check 6th sub matrix
        validate *check6 = (validate *) malloc(sizeof(validate));
        check6->ROW = 3;
        check6->COL = 6;
        check6->matrix = matrix;

        //check 7th sub matrix
        validate *check7 = (validate *) malloc(sizeof(validate));
        check7->ROW = 6;
        check7->COL = 0;
        check7->matrix = matrix;

        //check 8th sub matrix
        validate *check8 = (validate *) malloc(sizeof(validate));
        check8->ROW = 6;
        check8->COL = 3;
        check8->matrix = matrix;

        //check 9th sub matrix
        validate *check9 = (validate *) malloc(sizeof(validate));
        check9->ROW = 6;
        check9->COL = 6;
        check9->matrix = matrix;
                                                     
         pthread_t t_row, t_col,
                          t_check1, t_check2, t_check3,
                          t_check4, t_check5, t_check6,
                          t_check7, t_check8, t_check9;

         //Result pointers
        void *res_rows, *res_cols,
                          *res_s1, *res_s2, *res_s3, *res_s4,
                          *res_s5, *res_s6, *res_s7, *res_s8,
                          *res_s9;

        //Start the threads
        pthread_create(&t_row, NULL, checkRows, (void *)check0);
        pthread_create(&t_col, NULL, checkCols, (void *)check0);
        pthread_create(&t_check1, NULL, checkSudoku, (void *)check1);
        pthread_create(&t_check2, NULL, checkSudoku, (void *)check2);
        pthread_create(&t_check3, NULL, checkSudoku, (void *)check3);
        pthread_create(&t_check4, NULL, checkSudoku, (void *)check4);
        pthread_create(&t_check5, NULL, checkSudoku, (void *)check5);
        pthread_create(&t_check6, NULL, checkSudoku, (void *)check6);
        pthread_create(&t_check7, NULL, checkSudoku, (void *)check7);
        pthread_create(&t_check8, NULL, checkSudoku, (void *)check8);
        pthread_create(&t_check9, NULL, checkSudoku, (void *)check9);

         //Wait for the threads
        pthread_join(t_row, &res_rows);
        pthread_join(t_col, &res_cols);
        pthread_join(t_check1, &res_s1);
        pthread_join(t_check2, &res_s2);
        pthread_join(t_check3, &res_s3);
        pthread_join(t_check4, &res_s4);
        pthread_join(t_check5, &res_s5);
        pthread_join(t_check6, &res_s6);
        pthread_join(t_check7, &res_s7);
        pthread_join(t_check8, &res_s8);
        pthread_join(t_check9, &res_s9);

        //Check all the threads passed
        if((unsigned long)res_rows == 1 && (unsigned long)res_cols == 1 &&
                (unsigned long)res_s1 == 1 && (unsigned long)res_s2 == 1 && (unsigned long)res_s3 == 1 &&
                (unsigned long)res_s4 == 1 && (unsigned long)res_s5 == 1 && (unsigned long)res_s6 == 1 &&
                (unsigned long)res_s7 == 1 && (unsigned long)res_s8 == 1 && (unsigned long)res_s9 == 1){
                printf("Sudoku puzzle is valid.\n");
        }
        else {
                printf("Sudoku puzzle is invalid.\n");
        }
}

//check rows for 1-9
void *checkRows(void *value){
        validate *mtrix = (validate *)value;
        int s_row = mtrix->ROW;
        int s_col = mtrix->COL;
        for (int i=s_row; i < HEIGHT; i++){
                int row[10] = {0};

                for(int j = s_col; j < WIDTH; j++){
                        int cell = mtrix->matrix[i][j];
                        if(row[cell] != 0){
                                return (void *)0;
                        }
                        else{
                                row[cell] = 1;
                        }
                }
        }
        return (void *)1;
}  

    //check columns for 1-9
void *checkCols(void *value){
        validate *mtrix = (validate *)value;
        int s_row = mtrix->ROW;
        int s_col = mtrix->COL;
        for (int i=s_col; i < WIDTH; i++){
                int col[10] = {0};

                for(int j = s_row; j < HEIGHT; j++){
                        int cell = mtrix->matrix[i][j];
                        if(col[cell] != 0){
                                return (void *)0;
                        }
                        else{
                                col[cell] = 1;
                        }
                }
        }
        return (void *)1;
}

//check each sub matrix in the sudoku
void *checkSudoku(void *value){
        validate *mtrix = (validate *)value;
        int s_row = mtrix->ROW;
        int s_col = mtrix->COL;
        for (int i=s_row; i < s_row+3; i++){
                int subs[10] = {0};

                for(int j = s_col; j < s_col+3; j++){
                        int cell = mtrix->matrix[i][j];
                        if(subs[cell] != 0){
                                return (void *)0;
                        }
                        else{
                                subs[cell] = 1;
                        }
                }
                /*r(int i = 0; i < 9; i++)
                if(subs[i] != 1)
                {
                    printf("Invalid at %d\n", i + 1);
                }*/
                
        }
         return (void *)1;
}
                          
                           
