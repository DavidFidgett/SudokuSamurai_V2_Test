//
// Created by david on 19-May-20.
//

#ifndef SUDOKUSAMURAI_V1_0_SUDOKUSAM_H
#define SUDOKUSAMURAI_V1_0_SUDOKUSAM_H

//
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "trmnldrwng.h"
//

//MACROS y enum

enum intersection{nonIntersected, interA, interB, interC, interD};
enum subSudokus{sudA, sudB, sudC, sudD, sudE, inter };
#define NUMSUD 3

//Declaraciones de funciones

/**
 * @param S1 SudokuSource
 * @param S2 SudokuDestination
*/
void copySudoku(int S1[ROWS][COLS], int S2[ROWS][COLS]);

void clearSudokuMat(int S[ROWS][COLS]);
bool loadSudoku(int S[NUMSUD][ROWS][COLS]);
void initSudoku();
void chooseRandomSudoku(int S1[ROWS][COLS], int S2[ROWS][COLS]);

void pressEnter();
bool coordCheck(int S1[ROWS][COLS], int row, int col);
bool fillSudoku(int S1[ROWS][COLS], int S2[ROWS][COLS],int row, int col, int num);
bool boxCheck(int S2[ROWS][COLS], int row, int col, int num);
bool rowCheck(int S2[ROWS][COLS], int row, int col, int num);
bool colCheck(int S2[ROWS][COLS], int row, int col, int num);
bool fullCheck(int S2[ROWS][COLS], int row, int col, int num);

bool recursiveSolution(int S[ROWS][COLS], int *cont);
bool recursiveSolution2(int S[ROWS][COLS], int *cont);
bool recursiveSolution3(int S[ROWS][COLS], int *cont);

bool finalRecursiveSolution(int S[ROWS][COLS]);
bool recursionSudokuA(int S[ROWS][COLS], int *cont);
bool recursionSudokuB(int S[ROWS][COLS], int *cont);
bool recursionSudokuC(int S[ROWS][COLS], int *cont);
bool recursionSudokuD(int S[ROWS][COLS], int *cont);
bool recursionSudokuE(int S[ROWS][COLS], int *cont);

int getQuad(int row,int col);
int getSubSudoku(int row, int col);

//Variable global

int sudokuDataBase[NUMSUD][ROWS][COLS];

//Definicion de funciones


void copySudoku(int S1[ROWS][COLS], int S2[ROWS][COLS]){
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            S2[i][j]=S1[i][j];
        }
    }
}

void pressEnter(){
    printf("\n Presione ENTER para continuar.");
    getch();
    system("cls");
}

bool coordCheck(int S1[ROWS][COLS], int row, int col){
    if(row<0 || row>=21 || col<0 || col>=21){
        return false;
    }
    if(S1[row][col]==0){
        return true;//Coordenada valida para insercion de numero.
    }else{
        if(S1[row][col]==-1){
          //  printf("\n Coordenada [%d,%d] no valida.", row+1, col+1);
            return false;
        }else{
          //  printf("\n Coordenada con pista.");
            return false;
        }
    }
}

bool fillSudoku(int S1[ROWS][COLS], int S2[ROWS][COLS],int row, int col, int num){
    if(num<0 || num>9){
      //  printf("\n Numero introducido no valido.");
        return false;
    }

    int _row=row-1;
    int _col=col-1;

    if(coordCheck(S1, _row, _col)){

        if(fullCheck(S2, _row, _col, num)){
            S2[_row][_col]=num;
            return true;
        }else{
            if(num==0){
                S2[_row][_col]=num;
                return true;
            }
            return false;
        }

    }else{
        return false;
    }

}


bool boxCheck(int S2[ROWS][COLS], int row, int col, int num){
    int _row = row - row%3;
    int _col = col - col%3;

    for (int i = _row; i < _row+3; ++i) {
        for (int j = _col; j < _col+3; ++j) {
            if(S2[i][j]==num){
       //         printf("\n Numero ya existente en el cuadrante.");
                return false; //El numero ya existe en el cuadrante
            }
        }
    }
    return true;
}


int getQuad(int _row,int _col){
    if(_row==6 && _col==6){
        return interA;
    }
    if(_row==6 && _col==12){
        return interB;
    }
    if(_row==12 && _col==6){
        return interC;
    }
    if(_row==12 && _col==12){
        return interD;
    }
    return nonIntersected;
}

int getSubSudoku(int row, int col){
    if(row>=0 && row<= 8){
        if(col >=0 && col <= 5){
            return sudA;
        }
        if(row<=5 && col >= 6 && col<=8){
            return sudA;
        }
        if(row<=5 && col >= 12 && col<=14){
            return sudB;
        }
        if(col>=15 && col<=20){
            return sudB;
        }
        if(row>=6 && col>=6 && col<=8){
            //return interCA;
            return inter;
        }
        if(row>=6 && col>=9 && col<=11){
            return sudC;
        }
        if(row>=6 && col>=12 && col<=14){
            //return interCB;
            return inter;
        }
    }

    if(row>=9 && row<=11 && col>=6 && col<=14){
        return sudC;
    }

    if(row>=12 && row<= 20){
        if(col >=0 && col <= 5){
            return sudD;
        }
        if(row>=15 && col >= 6 && col<=8){
            return sudD;
        }
        if(row>=15 && col >= 12 && col<=14){
            return sudE;
        }
        if(col>=15 && col<=20){
            return sudE;
        }
        if(row<=14 && col>=6 && col<=8){
            //return interCD;//Q22
            return inter;
        }
        if(row<=14 && col>=9 && col<=11){
            return sudC;
        }
        if(row<=14 && col>=12 && col<=14){
            //return interCE;
            return inter;
        }
    }
    return -1;
}

bool rowCheck(int S2[ROWS][COLS], int row, int col, int num){


    int _row = row - row%3;
    int _col = col - col%3;
    int q = getQuad(_row, _col);
    int s = getSubSudoku(row, col);


    switch (s){
        case sudA:
            for (int j = 0; j < 9; ++j) {
                if(S2[row][j]==num){
            //        printf("\n Numero ya existente en renglon.");
                    return false;
                }
            }
            break;
        case sudB:
            for (int j = 12; j < 21; ++j) {
                if(S2[row][j]==num){
            //        printf("\n Numero ya existente en renglon.");
                    return false;
                }
            }
            break;
        case sudC:
            for (int j = 6; j < 15; ++j) {
                if(S2[row][j]==num){
            //        printf("\n Numero ya existente en renglon.");
                    return false;
                }
            }
            break;
        case sudD:
            for (int j = 0; j < 9; ++j) {
                if(S2[row][j]==num){
            //        printf("\n Numero ya existente en renglon.");
                    return false;
                }
            }
            break;
        case sudE:
            for (int j = 12; j < 21; ++j) {
                if(S2[row][j]==num){
            //        printf("\n Numero ya existente en renglon.");
                    return false;
                }
            }
            break;
        case inter:
            for (int j = 6; j < 15; ++j) {
                if(S2[row][j]==num){
            //        printf("\n Numero ya existente en renglon.");
                    return false;
                }
            }
            switch (q){
                case interA:
                    for (int j = 0; j < 9; ++j) {
                        if(S2[row][j]==num){
            //                printf("\n Numero ya existente en renglon.");
                            return false;
                        }
                    }
                    break;
                case interB:
                    for (int j = 12; j < 21; ++j) {
                        if(S2[row][j]==num){
            //                printf("\n Numero ya existente en renglon.");
                            return false;
                        }
                    }
                    break;
                case interC:
                    for (int j = 0; j < 9; ++j) {
                        if(S2[row][j]==num){
            //                printf("\n Numero ya existente en renglon.");
                            return false;
                        }
                    }
                    break;
                case interD:
                    for (int j = 12; j < 21; ++j) {
                        if(S2[row][j]==num){
            //                printf("\n Numero ya existente en renglon.");
                            return false;
                        }
                    }
                    break;
                default:
            //        printf("\nFATAL ERROR");
                    break;
            }
            break;
        default:
            printf("\nFATAL ERROR");
            break;
    }

    return true;

}

bool colCheck(int S2[ROWS][COLS], int row, int col, int num){


    int _row = row - row%3;
    int _col = col - col%3;
    int q = getQuad(_row, _col);
    int s = getSubSudoku(row, col);


    switch (s){
        case sudA:
            for (int i = 0; i < 9; ++i) {
                if(S2[i][col]==num){
            //        printf("\n Numero ya existente en columna.");
                    return false;
                }
            }
            break;
        case sudB:
            for (int i = 0; i < 9; ++i) {
                if(S2[i][col]==num){
            //        printf("\n Numero ya existente en columna.");
                    return false;
                }
            }
            break;
        case sudC:
            for (int i = 6; i < 15; ++i) {
                if(S2[i][col]==num){
            //        printf("\n Numero ya existente en columna.");
                    return false;
                }
            }
            break;
        case sudD:
            for (int i = 12; i < 21; ++i) {
                if(S2[i][col]==num){
            //        printf("\n Numero ya existente en columna.");
                    return false;
                }
            }
            break;
        case sudE:
            for (int i = 12; i < 21; ++i) {
                if(S2[i][col]==num){
            //        printf("\n Numero ya existente en columna.");
                    return false;
                }
            }
            break;
        case inter:
            for (int i = 6; i < 15; ++i) {
                if(S2[i][col]==num){
            //        printf("\n Numero ya existente en columna.");
                    return false;
                }
            }
            switch (q){
                case interA:
                    for (int i = 0; i < 9; ++i) {
                        if(S2[i][col]==num){
            //                printf("\n Numero ya existente en columna.");
                            return false;
                        }
                    }
                    break;
                case interB:
                    for (int i = 0; i < 9; ++i) {
                        if(S2[i][col]==num){
             //               printf("\n Numero ya existente en columna.");
                            return false;
                        }
                    }
                    break;
                case interC:
                    for (int i = 12; i < 21; ++i) {
                        if(S2[i][col]==num){
            //                printf("\n Numero ya existente en columna.");
                            return false;
                        }
                    }
                    break;
                case interD:
                    for (int i = 12; i < 21; ++i) {
                        if(S2[i][col]==num){
            //                printf("\n Numero ya existente en columna.");
                            return false;
                        }
                    }
                    break;
                default:
                    printf("\nFATAL ERROR");
                    break;
            }
            break;
        default:
            printf("\nFATAL ERROR");
            break;
    }

    return true;
    
}

bool fullCheck(int S2[ROWS][COLS], int row, int col, int num){
    return (boxCheck(S2, row, col, num) && colCheck(S2, row, col, num) && rowCheck(S2, row, col, num));
}

bool recursiveSolution(int S[ROWS][COLS], int *cont){

    *cont = *cont + 1;
    //system("cls");

   /* printf("\n\t Ciclo recursivo #%d", *cont);
    sudokuPrint(S);*/

    //printf("\n\t Debug");

    if(*cont % 1000 == 0){
        printf("\n\t Ciclo recursivo #%d", *cont);
        sudokuPrint(S);
    }

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursiveSolution(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }

    return true;
}

bool recursiveSolution2(int S[ROWS][COLS], int *cont){

    *cont = *cont + 1;
    //system("cls");

   // printf("\n\t DEBUG");


    if(*cont % 2000 == 0){
        printf("\n\t Ciclo recursivo #%d", *cont);
        sudokuPrint(S);
    }



    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursiveSolution2(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }

    for (int i = 6; i < 14; ++i) {
        for (int j = 6; j < 14; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursiveSolution2(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 12; j < 21; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursiveSolution2(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }



    for (int i = 12; i < 21; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursiveSolution2(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }

    for (int i = 12; i < 21; ++i) {
        for (int j = 12; j < 21; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursiveSolution2(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }

    return true;
}

bool recursiveSolution3(int S[ROWS][COLS], int *cont){

    *cont = *cont + 1;
    //system("cls");

    // printf("\n\t DEBUG");


    if(*cont % 1000 == 0){
        printf("\n\t Ciclo recursivo #%d", *cont);
        sudokuPrint(S);
    }



    for (int i = 6; i <= 14; ++i) {
        for (int j = 6; j <= 14; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursiveSolution3(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursiveSolution3(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 12; j < 21; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursiveSolution3(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }



    for (int i = 12; i < 21; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursiveSolution3(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }

    for (int i = 12; i < 21; ++i) {
        for (int j = 12; j < 21; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursiveSolution3(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }

    return true;
}

bool finalRecursiveSolution(int S[ROWS][COLS]){
    int cont=0;
    printf("\n\t DEBUG");
    if(recursionSudokuC(S, &cont)){
        printf("\n\t Ciclo recursivo #%d", cont);
        printf("\n\t Fin Sudoku C");
        sudokuPrint(S);
        pressEnter();
    }
    if(recursionSudokuA(S, &cont)){
        printf("\n\t Ciclo recursivo #%d", cont);
        printf("\n\t Fin Sudoku A");
        sudokuPrint(S);
        printf("\n\t Fin Sudoku A");
        pressEnter();
    }
    if(recursionSudokuB(S, &cont)){
        printf("\n\t Ciclo recursivo #%d", cont);
        printf("\n\t Fin Sudoku B");
        sudokuPrint(S);
        pressEnter();
        printf("\n\t Fin Sudoku B");
    }
    if(recursionSudokuD(S, &cont)){
        printf("\n\t Ciclo recursivo #%d", cont);
        printf("\n\t Fin Sudoku D");
        sudokuPrint(S);
        pressEnter();
        printf("\n\t Fin Sudoku D");
    }
    if(recursionSudokuE(S, &cont)){
        printf("\n\t Ciclo recursivo #%d", cont);
        printf("\n\t Fin Sudoku E");
        sudokuPrint(S);
        pressEnter();
        printf("\n\t Fin Sudoku E");
    }
    return true;
}

bool recursionSudokuA(int S[ROWS][COLS], int *cont){

    *cont=*cont+1;

    if(*cont%1000==0){
        printf("\n\t Ciclo recursivo #%d", *cont);
        sudokuPrint(S);
    }


    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursionSudokuA(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool recursionSudokuB(int S[ROWS][COLS], int *cont){

    *cont=*cont+1;


    if(*cont%1000==0){
        printf("\n\t Ciclo recursivo #%d", *cont);
        sudokuPrint(S);
    }


    for (int i = 0; i < 9; ++i) {
        for (int j = 12; j < 21; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursionSudokuB(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool recursionSudokuC(int S[ROWS][COLS], int *cont){

    *cont=*cont+1;

    if(*cont%1000==0){
        printf("\n\t Ciclo recursivo #%d", *cont);
        sudokuPrint(S);
    }


    for (int i = 6; i < 15; ++i) {
        for (int j = 6; j < 15; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursionSudokuC(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool recursionSudokuD(int S[ROWS][COLS], int *cont){

    *cont=*cont+1;

    if(*cont%1000==0){
        printf("\n\t Ciclo recursivo #%d", *cont);
        sudokuPrint(S);
    }


    for (int i = 12; i < 21; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursionSudokuD(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool recursionSudokuE(int S[ROWS][COLS], int *cont){

    *cont=*cont+1;

    if(*cont%1000==0){
        printf("\n\t Ciclo recursivo #%d", *cont);
        sudokuPrint(S);
    }


    for (int i = 12; i < 21; ++i) {
        for (int j = 12; j < 21; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursionSudokuE(S, cont)){
                            return true;
                        }else{
                            S[i][j]=0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void clearSudokuMat(int S[ROWS][COLS]){
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            S[i][j]=0;
        }
    }
}

bool loadSudoku(int S[NUMSUD][ROWS][COLS]){
    FILE *fp = fopen("sudokusData/unsolvedSudokus.txt", "r");

    int num;

    if(fp==NULL){
        printf("\n\t Error al abrir archivo de Sudoku");
        return false;
    }

    for (int k=0; k<NUMSUD; ++k) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                fscanf(fp, "%d", &num);
                //printf("\n\t %d", num);
                S[k][i][j]=num;
            }
        }
    }

    fclose(fp);

    return true;

}

void initSudoku(){
    srand(time(NULL));
    loadSudoku(sudokuDataBase);
}

void chooseRandomSudoku(int S1[ROWS][COLS], int S2[ROWS][COLS]){
    int r = rand()%NUMSUD;
    copySudoku(sudokuDataBase[r], S1);
    copySudoku(S1, S2);
}

#endif //SUDOKUSAMURAI_V1_0_SUDOKUSAM_H
