#include <stdio.h>
#include "sudokusam.h"
#include <allegro.h>

//MACROS

#define W 1080
#define H 720
#define CD 16 //Colour depth
#define SPR_W 24
#define SPR_H 24
#define MENU_L 698 //Posicion X (en pixeles) donde empieza el menu
#define MENU_R 1016 //Posicion Y (en pixeles) donde termina el menu


enum stt{initial, newGameGeneration, playing, recursion};
enum menuOptions{nothing, newGame, recursiveSolving};

//BITMAPS

BITMAP *buffer;
BITMAP *sudokuBoard;
BITMAP *sprNumbers;
BITMAP *number;
BITMAP *arrow;

//MIDI

MIDI *music;

//FUNCIONES

void initGame();
void scr();
void loadSprites();
void loadMusic();
//void drawBoard(int S1[ROWS][COLS], int S2[ROWS][COLS]);
void drawBoard();
void drawNumbers(int S1[ROWS][COLS], int S2[ROWS][COLS]);
void drawNumbersSlow(int S1[ROWS][COLS], int S2[ROWS][COLS]);
int menuSelection();
bool finalRecursiveSolutionAllegro(int S[ROWS][COLS]);

//Mezcla de funciones de biblioteca Allegro con sudokusam

bool recursionSudokuA_allegro(int S[ROWS][COLS], int *cont);
bool recursionSudokuB_allegro(int S[ROWS][COLS], int *cont);
bool recursionSudokuC_allegro(int S[ROWS][COLS], int *cont);
bool recursionSudokuD_allegro(int S[ROWS][COLS], int *cont);
bool recursionSudokuE_allegro(int S[ROWS][COLS], int *cont);

//

int main() {

    int S1[ROWS][COLS]={0}, S2[ROWS][COLS]={0};
    int state = initial;
    int menu = 0;
    bool success;

    //mouse_x y mouse_y son variables de allegro para la posicion en X y en Y
    //(en pixeles) del raton.

    initGame();

    /*chooseRandomSudoku(S1, S2);
    sudokuPrint(S1);*/

    //Para esta primera version, se pasara inmediatamente del estado
    //inicial al estado en juego

    state = playing;

    //play_looped_midi(music, 0, -1);
    play_midi(music, 1);

    while (!key[KEY_ESC]){

        drawBoard();
        drawNumbers(S1, S2);
        show_mouse(screen);


        switch (state){
            case initial:
                break;
            case newGameGeneration:
                chooseRandomSudoku(S1, S2);
                sudokuPrint(S1);
                drawNumbersSlow(S1, S2);
                state = playing;
                break;
            case playing:
                menu=menuSelection();
                if(menu!=0){
                    rest(200);
                    switch (menu){
                        case newGame:
                            state = newGameGeneration;
                            clearSudokuMat(S1);
                            clearSudokuMat(S2);
                            break;
                        case recursiveSolving:
                            copySudoku(S1, S2);
                            state = recursion;
                            break;
                    }
                }
                break;
            case recursion:

                success = finalRecursiveSolutionAllegro(S2);

                state = playing;
                break;
        }




        scr();
        rest(100);
        clear(buffer);
    }


    return 0;
}END_OF_MAIN();




void initGame(){
    initSudoku();
    allegro_init();
    install_keyboard();
    install_mouse();
    enable_hardware_cursor();
    select_mouse_cursor(MOUSE_CURSOR_ARROW);
    set_color_depth(CD);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, W, H, 0, 0);
    buffer = create_bitmap(W, H);
    loadSprites();
    loadMusic();

    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

}

void scr(){
    blit(buffer, screen, 0, 0, 0, 0, W, H);
}

void loadSprites(){
    sudokuBoard = load_bitmap("sprites/sudokuBoard.bmp", NULL);
    sprNumbers = load_bitmap("sprites/sprNumbers.bmp", NULL);
    number = create_bitmap(SPR_W, SPR_H);
    arrow = load_bitmap("sprites/arrow.bmp", NULL);
}

void loadMusic(){
    music = load_midi("midi/midiTimeTraxIntro.mid");
}

void drawBoard(){
    draw_sprite(buffer, sudokuBoard, 0, 0);
}

int menuSelection(){

    int A_Yi = 168; //Opcion A del menu, Y inicial
    int A_Yf = 220; //Opcion A del menu, Y final
    int B_Yi = 236;
    int B_Yf = 312;

    int arrow_x = 989;
    int arrow_y_A = 184;
    int arrow_y_B = 263;

    //printf("\n\t X: %d Y: %d", mouse_x, mouse_y);

    if(mouse_x >= MENU_L && mouse_x <= MENU_R){


        if(mouse_y >= A_Yi && mouse_y <= A_Yf){
            draw_sprite(buffer, arrow, arrow_x, arrow_y_A);
            if(mouse_b){
                return newGame;
            }
        }

        if(mouse_y >= B_Yi && mouse_y <= B_Yf){
            draw_sprite(buffer, arrow, arrow_x, arrow_y_B);
            if(mouse_b){
                return recursiveSolving;
            }
        }

        scr();

    }

    return 0;
}


void drawNumbers(int S1[ROWS][COLS], int S2[ROWS][COLS]){

    int offset = 67;//MAYBE MACRO!?
    int spacing = 27;

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if(S2[i][j]!=0 && S2[i][j]!=-1){
                blit(sprNumbers, number, SPR_W*(S2[i][j]), 0, 0, 0, SPR_W, SPR_H);
                draw_sprite(buffer, number, offset+(j*spacing), offset+(i*spacing));
            }
        }
    }


}

void drawNumbersSlow(int S1[ROWS][COLS], int S2[ROWS][COLS]){

    int offset = 67;//MAYBE MACRO!?
    int spacing = 27;

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if(S2[i][j]!=0 && S2[i][j]!=-1){
                blit(sprNumbers, number, SPR_W*(S2[i][j]), 0, 0, 0, SPR_W, SPR_H);
                draw_sprite(buffer, number, offset+(j*spacing), offset+(i*spacing));
                scr();
                rest(20);
            }
        }
    }


}

bool finalRecursiveSolutionAllegro(int S[ROWS][COLS]){
    int cont=0;
    printf("\n\t DEBUG");
    /*if(recursionSudokuC_allegro(S, &cont)){
        printf("\n\t Ciclo recursivo allegro #%d", cont);
        printf("\n\t Fin Sudoku C");
    }
    if(recursionSudokuA_allegro(S, &cont)){
        printf("\n\t Ciclo recursivo #%d", cont);

    }
    if(recursionSudokuB_allegro(S, &cont)){
        printf("\n\t Ciclo recursivo #%d", cont);

    }
    if(recursionSudokuD_allegro(S, &cont)){
        printf("\n\t Ciclo recursivo #%d", cont);

    }
    if(recursionSudokuE_allegro(S, &cont)){
        printf("\n\t Ciclo recursivo #%d", cont);

    }*/

    recursionSudokuC_allegro(S, &cont);
    recursionSudokuA_allegro(S, &cont);
    recursionSudokuB_allegro(S, &cont);
    recursionSudokuD_allegro(S, &cont);
    recursionSudokuE_allegro(S, &cont);

    return true;
}

bool recursionSudokuA_allegro(int S[ROWS][COLS], int *cont){

    *cont=*cont+1;

    //Drawing
    clear(buffer);
    drawBoard();
    drawNumbers(S, S);
    show_mouse(screen);
    scr();
    //


    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursionSudokuA_allegro(S, cont)){
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

bool recursionSudokuB_allegro(int S[ROWS][COLS], int *cont){

    *cont=*cont+1;

    //Drawing
    clear(buffer);
    drawBoard();
    drawNumbers(S, S);
    show_mouse(screen);
    scr();
    //

    for (int i = 0; i < 9; ++i) {
        for (int j = 12; j < 21; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursionSudokuB_allegro(S, cont)){
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

bool recursionSudokuC_allegro(int S[ROWS][COLS], int *cont){

    *cont=*cont+1;



    //Drawing
    clear(buffer);
    drawBoard();
    drawNumbers(S, S);
    show_mouse(screen);
    scr();

    //

    for (int i = 6; i < 15; ++i) {
        for (int j = 6; j < 15; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursionSudokuC_allegro(S, cont)){
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

bool recursionSudokuD_allegro(int S[ROWS][COLS], int *cont){

    *cont=*cont+1;


    //Drawing
    clear(buffer);
    drawBoard();
    drawNumbers(S, S);
    show_mouse(screen);
    scr();
    //


    for (int i = 12; i < 21; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursionSudokuD_allegro(S, cont)){
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

bool recursionSudokuE_allegro(int S[ROWS][COLS], int *cont){

    *cont=*cont+1;


    //Drawing
    clear(buffer);
    drawBoard();
    drawNumbers(S, S);
    show_mouse(screen);
    scr();
    //

    for (int i = 12; i < 21; ++i) {
        for (int j = 12; j < 21; ++j) {
            if(S[i][j]==0){
                for (int num = 1; num <= 9; ++num) {
                    if(fullCheck(S, i, j, num)){
                        S[i][j]=num;
                        if(recursionSudokuE_allegro(S, cont)){
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

