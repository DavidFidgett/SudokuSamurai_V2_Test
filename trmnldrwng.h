/*
	Biblioteca para dibujar Sudokus version Samurai
	en la terminal de la consola a traves del uso de 
	caracteres ASCII extendidos.
	Se requiere uso de una matriz de 21x21 para su funcionamiento.
	
	Ejemplo:
	
	void sudokuPrint(int S[ROWS][COLS]);
	
         ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
         │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 10│ 11│ 12│ 13│ 14│ 15│ 16│ 17│ 18│ 19│ 20│ 21│
         └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘

┌───┐    ╔═══════════╦═══════════╦═══════════╗           ╔═══════════╦═══════════╦═══════════╗
│ 1 │    ║   │ 2 │ 9 ║   │   │   ║ 5 │ 1 │   ║           ║   │ 9 │ 1 ║   │   │   ║ 7 │ 6 │   ║
├───┤    ║───┼───┼───║───┼───┼───║───┼───┼───║           ║───┼───┼───║───┼───┼───║───┼───┼───║
│ 2 │    ║ 1 │   │   ║ 7 │   │ 5 ║   │   │ 9 ║           ║ 4 │   │   ║ 6 │   │ 9 ║   │   │ 5 ║
├───┤    ║───┼───┼───║───┼───┼───║───┼───┼───║           ║───┼───┼───║───┼───┼───║───┼───┼───║
│ 3 │    ║ 6 │   │   ║ 2 │   │ 9 ║   │   │ 3 ║           ║ 5 │   │   ║ 4 │   │ 2 ║   │   │ 1 ║
├───┤    ╠═══════════╬═══════════╬═══════════╣           ╠═══════════╬═══════════╬═══════════╣
│ 4 │    ║   │ 3 │ 7 ║   │   │   ║ 2 │ 4 │   ║           ║   │ 6 │ 9 ║   │   │   ║ 8 │ 7 │   ║
├───┤    ║───┼───┼───║───┼───┼───║───┼───┼───║           ║───┼───┼───║───┼───┼───║───┼───┼───║
│ 5 │    ║   │   │   ║   │   │   ║   │   │   ║           ║   │   │   ║   │   │   ║   │   │   ║
├───┤    ║───┼───┼───║───┼───┼───║───┼───┼───║           ║───┼───┼───║───┼───┼───║───┼───┼───║
│ 6 │    ║   │ 6 │ 4 ║   │   │   ║ 9 │ 5 │   ║           ║   │ 5 │ 7 ║   │   │   ║ 1 │ 4 │   ║
├───┤    ╠═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╣
│ 7 │    ║ 4 │   │   ║ 9 │   │ 6 ║   │   │ 2 ║   │   │   ║ 7 │   │   ║ 8 │   │ 4 ║   │   │ 3 ║
├───┤    ║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║
│ 8 │    ║ 3 │   │   ║ 8 │   │ 1 ║   │   │ 5 ║   │   │   ║ 9 │   │   ║ 2 │   │ 3 ║   │   │ 7 ║
├───┤    ║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║
│ 9 │    ║   │ 8 │ 6 ║   │   │   ║ 1 │ 9 │   ║   │ 8 │   ║   │ 2 │ 3 ║   │   │   ║ 4 │ 9 │   ║
├───┤    ╚═══════════╩═══════════╬═══════════╬═══════════╬═══════════╬═══════════╩═══════════╝
│ 10│                            ║   │   │   ║ 2 │   │ 7 ║   │   │   ║
├───┤                            ║───┼───┼───║───┼───┼───║───┼───┼───║
│ 11│                            ║   │   │ 9 ║   │   │   ║ 3 │   │   ║
├───┤                            ║───┼───┼───║───┼───┼───║───┼───┼───║
│ 12│                            ║   │   │   ║ 6 │   │ 1 ║   │   │   ║
├───┤    ╔═══════════╦═══════════╬═══════════╬═══════════╬═══════════╬═══════════╦═══════════╗
│ 13│    ║   │ 6 │ 4 ║   │   │   ║ 9 │ 2 │   ║   │ 7 │   ║   │ 3 │ 1 ║   │   │   ║ 9 │ 5 │   ║
├───┤    ║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║
│ 14│    ║ 3 │   │   ║ 8 │   │ 6 ║   │   │ 7 ║   │   │   ║ 2 │   │   ║ 5 │   │ 4 ║   │   │ 8 ║
├───┤    ║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║───┼───┼───║
│ 15│    ║ 5 │   │   ║ 4 │   │ 9 ║   │   │ 1 ║   │   │   ║ 5 │   │   ║ 9 │   │ 3 ║   │   │ 2 ║
├───┤    ╠═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╣
│ 16│    ║   │ 3 │ 7 ║   │   │   ║ 8 │ 1 │   ║           ║   │ 2 │ 7 ║   │   │   ║ 6 │ 1 │   ║
├───┤    ║───┼───┼───║───┼───┼───║───┼───┼───║           ║───┼───┼───║───┼───┼───║───┼───┼───║
│ 17│    ║   │   │   ║   │   │   ║   │   │   ║           ║   │   │   ║   │   │   ║   │   │   ║
├───┤    ║───┼───┼───║───┼───┼───║───┼───┼───║           ║───┼───┼───║───┼───┼───║───┼───┼───║
│ 18│    ║   │ 2 │ 5 ║   │   │   ║ 4 │ 7 │   ║           ║   │ 6 │ 9 ║   │   │   ║ 5 │ 2 │   ║
├───┤    ╠═══════════╬═══════════╬═══════════╣           ╠═══════════╬═══════════╬═══════════╣
│ 19│    ║ 2 │   │   ║ 1 │   │ 8 ║   │   │ 9 ║           ║ 7 │   │   ║ 4 │   │ 6 ║   │   │ 1 ║
├───┤    ║───┼───┼───║───┼───┼───║───┼───┼───║           ║───┼───┼───║───┼───┼───║───┼───┼───║
│ 20│    ║ 4 │   │   ║ 9 │   │ 3 ║   │   │ 2 ║           ║ 9 │   │   ║ 8 │   │ 5 ║   │   │ 3 ║
├───┤    ║───┼───┼───║───┼───┼───║───┼───┼───║           ║───┼───┼───║───┼───┼───║───┼───┼───║
│ 21│    ║   │ 9 │ 1 ║   │   │   ║ 3 │ 5 │   ║           ║   │ 8 │ 4 ║   │   │   ║ 7 │ 9 │   ║
└───┘    ╚═══════════╩═══════════╩═══════════╝           ╚═══════════╩═══════════╩═══════════╝
*/

/*
	Valores ASCII utilizados (en orden numerico):
	
	179: │

    180: ┤
	
	185: ╣	
	
	186: ║
	
	187: ╗
	
	188: ╝

    191: ┐

    192: └

    193: ┴

    194: ┬

    195: ├
	
	196: ─
	
	197: ┼
	
	200: ╚
	
	201: ╔
	
	202: ╩
	
	203: ╦
	
	204: ╠
	
	205: ═
	
	206: ╬

    217: ┘

    218: ┌

*/

#define repeat(n) for (int i=0 ; i<n ; i++)
	
#define ROWS 21
#define COLS 21
#define SPC 4
#define SPACING 5+SPC

//Declaracion de funciones:



void sudokuPrint(int S[ROWS][COLS]);
/* void sudokuPrint(int S[ROWS][COLS]) es la funcion mas importante (y la unica que
   deberia ser llamada por el usuario). Esta funcion hace uso de las demas funciones
   para dibujar correctamente el Sudoku. Recibe un matriz de tipo entero de 21 renglones
   por 21 columnas. Los "0" se dibujan como espacios, mientras que los "-1" denotan
   que es una casilla no valida para el juego.
*/

void simplePrint(int S[ROWS][COLS]);
/* simplePrint(int S[ROWS][COLS]) es una alternativa a sudokuPrint() que solo 
   imprimira los valores del sudoku, sin tanto formato como el usado en la funcion
   sudokuPrint().
*/

void rowNumbers();
void rowTypeA();
void rowTypeB(int S[ROWS][COLS], int i);
void rowTypeC();
void rowTypeD();
void rowTypeE();
void rowTypeF(int S[ROWS][COLS], int i);
void rowTypeG();
void rowTypeH();
void rowTypeI(int S[ROWS][COLS], int i);
void rowTypeJ();
void rowTypeK();
void rowTypeL();



//Funciones:

void sudokuPrint(int S[ROWS][COLS]){

    printf("\n ");
    rowNumbers();

    printf("\n "); //Salto de linea
    rowTypeA();


    //Renglones 0 a 2
    for (int i = 0; i < 3; ++i) {
        printf("\n ");
        rowTypeB(S, i);
        if(i!=2){
            printf("\n ");
            rowTypeC();
        }else{
            printf("\n ");
            rowTypeD();
        }
    }

    //Renglones 3 a 5
    for (int i = 3; i < 6; ++i) {
        printf("\n ");
        rowTypeB(S, i);
        if(i!=5){
            printf("\n ");
            rowTypeC();
        }else{
            printf("\n ");
            rowTypeE();
        }
    }

    //Renglones 6 a 8
    for (int i = 6; i < 9; ++i) {
        printf("\n ");
        rowTypeF(S, i);
        if(i!=8){
            printf("\n ");
            rowTypeG();
        }else{
            printf("\n ");
            rowTypeH();
        }
    }

    //Renglones 9 a 11
    for (int i = 9; i < 12; ++i) {
        printf("\n ");
        rowTypeI(S, i);
        if(i!=11){
            printf("\n ");
            rowTypeJ();
        }else{
            printf("\n ");
            rowTypeK();
        }
    }

    //Renglones 12 a 14
    for (int i = 12; i < 15; ++i) {
        printf("\n ");
        rowTypeF(S, i);
        if(i!=14){
            printf("\n ");
            rowTypeG();
        }else{
            printf("\n ");
            rowTypeE();
        }
    }

    //Renglones 15 a 17
    for (int i = 15; i < 18; ++i) {
        printf("\n ");
        rowTypeB(S, i);
        if(i!=17){
            printf("\n ");
            rowTypeC();
        }else{
            printf("\n ");
            rowTypeD();
        }
    }

    //Renglones 18 a 20
    for (int i = 18; i < 21; ++i) {
        printf("\n ");
        rowTypeB(S, i);
        if(i!=20){
            printf("\n ");
            rowTypeC();
        }else{
            printf("\n ");
            rowTypeL();
        }
    }


    printf("\n"); //Salto de linea
}

void rowNumbers(){

    repeat(SPACING){
        printf(" ");
    }

    printf("%c", 218);//218: ┌
    repeat(20){
        repeat(3){
            printf("%c", 196);//196: ─
        }
        printf("%c", 194);//194: ┬
    }
    repeat(3){
        printf("%c", 196);//196: ─
    }
    printf("%c", 191);//191; ┐


    printf("\n ");
    repeat(SPACING){
        printf(" ");
    }
    printf("%c", 179);//179: │
    for (int i = 1; i < 9 ; ++i) {
        printf(" %d %c",i, 179);//179: │
    }
    printf(" 9 %c", 179);//179: │
    for (int i = 10; i <= 21 ; ++i) {
        printf(" %d%c",i, 179);//179: │
    }

    printf("\n ");
    repeat(SPACING){
        printf(" ");
    }
    printf("%c", 192);//192: └
    repeat(20){
        repeat(3){
            printf("%c", 196);//196: ─
        }
        printf("%c", 193);//193: ┴
    }
    repeat(3){
        printf("%c", 196);//196: ─
    }
    printf("%c", 217);//217: ┘

    printf("\n");

}

void rowTypeA(){



    //┌───┐
    printf("%c", 218);//218: ┌
    repeat(3){
        printf("%c", 196);//196: ─
    }
    printf("%c", 191);//191: ┐
    repeat(SPC){
        printf(" ");
    }

    // ╔═══════════╦═══════════╦═══════════╗
    printf("%c", 201);//201: ╔
    repeat(2){
        repeat(11){
            printf("%c", 205);//205: ═
        }
        printf("%c", 203);//203: ╦
    }

    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 187);//187: ╗

    repeat(11){
        printf(" ");// Espacio
    }

    //Segunda parte despues del espacio

    printf("%c", 201);//201: ╔
    repeat(2){
        repeat(11){
            printf("%c", 205);//205: ═
        }
        printf("%c", 203);//203: ╦
    }

    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 187);//187: ╗

}

void rowTypeB(int S[ROWS][COLS], int i){

    //│ i │
    printf("%c", 179);//179: │
    if(i<9){
        printf(" %d ", i+1);
    }else{
        printf(" %d", i+1);
    }
    printf("%c", 179);//179: │
    repeat(SPC){
        printf(" ");
    }



    printf("%c", 186);//186: ║
    for (int j = 0; j < 9; ++j) {

        if(S[i][j]!=0 && S[i][j]!=-1){
            printf(" %d ", S[i][j]);
        }else{
            printf("   ");
        }

        if(j!=2 && j!=5 && j!=8){
            printf("%c", 179);//179: │
        }else{
            printf("%c", 186);//186: ║
        }

    }

    repeat(11){
        printf(" ");// Espacio
    }

    //Segunda parte despues del espacio

    printf("%c", 186);//186: ║
    for (int j = 12; j < 21; ++j) {

        if(S[i][j]!=0 && S[i][j]!=-1){
            printf(" %d ", S[i][j]);
        }else{
            printf("   ");
        }

        if(j!=14 && j!=17 && j!=20){
            printf("%c", 179);//179: │
        }else{
            printf("%c", 186);//186: ║
        }

    }

}

void rowTypeC(){

    //├───┤
    printf("%c", 195);//195: ├
    repeat(3){
        printf("%c", 196);//196: ─
    }
    printf("%c", 180);//180: ┤
    repeat(SPC){
        printf(" ");
    }


    //
    printf("%c", 186);//186: ║
    repeat(3){
        repeat(2){
            repeat(3){
                printf("%c", 196);//196: ─
            }
            printf("%c", 197);//197: ┼
        }
        repeat(3){
            printf("%c", 196);//196: ─
        }
        printf("%c", 186);//186: ║
    }

    repeat(11){
        printf(" ");// Espacio
    }

    printf("%c", 186);//186: ║
    repeat(3){
        repeat(2){
            repeat(3){
                printf("%c", 196);//196: ─
            }
            printf("%c", 197);//197: ┼
        }
        repeat(3){
            printf("%c", 196);//196: ─
        }
        printf("%c", 186);//186: ║
    }

}

void rowTypeD(){

    //├───┤
    printf("%c", 195);//195: ├
    repeat(3){
        printf("%c", 196);//196: ─
    }
    printf("%c", 180);//180: ┤
    repeat(SPC){
        printf(" ");
    }

    //
    printf("%c", 204);//204: ╠
    repeat(2){
        repeat(11){
            printf("%c", 205);//205: ═
        }
        printf("%c", 206);//206: ╬
    }
    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 185);//185:╣

    repeat(11){
        printf(" ");// Espacio
    }

    printf("%c", 204);//204: ╠
    repeat(2){
        repeat(11){
            printf("%c", 205);//205: ═
        }
        printf("%c", 206);//206: ╬
    }
    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 185);//185:╣

}

void rowTypeE(){

    //├───┤
    printf("%c", 195);//195: ├
    repeat(3){
        printf("%c", 196);//196: ─
    }
    printf("%c", 180);//180: ┤
    repeat(SPC){
        printf(" ");
    }

    //

    printf("%c", 204);//204: ╠
    repeat(6){
        repeat(11){
            printf("%c", 205);//205: ═
        }
        printf("%c", 206);//206: ╬
    }
    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 185);//185:╣
}

void rowTypeF(int S[ROWS][COLS], int i){


    //│ i │
    printf("%c", 179);//179: │
    if(i<9){
        printf(" %d ", i+1);
    }else{
        printf(" %d", i+1);
    }
    printf("%c", 179);//179: │
    repeat(SPC){
        printf(" ");
    }
    //


    printf("%c", 186);//186: ║
    for (int j = 0; j < 21; ++j) {
        if(S[i][j]!=0 && S[i][j]!=-1){
            printf(" %d ", S[i][j]);
        }else{
            printf("   ");
        }

        if(j!=2 && j!=5 && j!=8 && j!=11 && j!=14 && j!=17 && j!=20){
            printf("%c", 179);//179: │
        }else{
            printf("%c", 186);//186: ║
        }

    }
}

void rowTypeG(){

    //├───┤
    printf("%c", 195);//195: ├
    repeat(3){
        printf("%c", 196);//196: ─
    }
    printf("%c", 180);//180: ┤
    repeat(SPC){
        printf(" ");
    }
    //

    printf("%c", 186);//186: ║
    repeat(7){
        repeat(2){
            repeat(3){
                printf("%c", 196);//196: ─
            }
            printf("%c", 197);//197: ┼
        }
        repeat(3){
            printf("%c", 196);//196: ─
        }
        printf("%c", 186);//186: ║
    }
}

void rowTypeH(){

    //├───┤
    printf("%c", 195);//195: ├
    repeat(3){
        printf("%c", 196);//196: ─
    }
    printf("%c", 180);//180: ┤
    repeat(SPC){
        printf(" ");
    }
    //

    printf("%c", 200);//200:╚
    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 202);//202: ╩
    repeat(4){
        repeat(11){
            printf("%c", 205);//205: ═
        }
        printf("%c", 206);//206: ╬
    }
    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 202);//202: ╩
    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 188);//188: ╝

}

void rowTypeI(int S[ROWS][COLS], int i){


    //│ i │
    printf("%c", 179);//179: │
    if(i<9){
        printf(" %d ", i+1);
    }else{
        printf(" %d", i+1);
    }
    printf("%c", 179);//179: │
    repeat(SPC){
        printf(" ");
    }
    //


    repeat(24){
        printf(" ");
    }
    printf("%c", 186);//186: ║

    for (int j = 6; j < 15; ++j) {
        if(S[i][j]!=0 && S[i][j]!=-1){
            printf(" %d ", S[i][j]);
        }else{
            printf("   ");
        }

        if(j!=8 && j!=11 && j!=14){
            printf("%c", 179);//179: │
        }else{
            printf("%c", 186);//186: ║
        }

    }


}

void rowTypeJ(){

    //├───┤
    printf("%c", 195);//195: ├
    repeat(3){
        printf("%c", 196);//196: ─
    }
    printf("%c", 180);//180: ┤
    repeat(SPC){
        printf(" ");
    }
    //


    repeat(24){
        printf(" ");
    }
    printf("%c", 186);//186: ║
    repeat(3){
        repeat(2){
            repeat(3){
                printf("%c", 196);//196: ─
            }
            printf("%c", 197);//197: ┼
        }
        repeat(3){
            printf("%c", 196);//196: ─
        }
        printf("%c", 186);//186: ║
    }
}

void rowTypeK(){

    //├───┤
    printf("%c", 195);//195: ├
    repeat(3){
        printf("%c", 196);//196: ─
    }
    printf("%c", 180);//180: ┤
    repeat(SPC){
        printf(" ");
    }
    //


    printf("%c", 201);//201:╔
    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 203);//203: ╦
    repeat(4){
        repeat(11){
            printf("%c", 205);//205: ═
        }
        printf("%c", 206);//206: ╬
    }
    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 203);//203: ╦
    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 187);//187: ╗
}

void rowTypeL(){

    //└───┘
    printf("%c", 192);//192: └
    repeat(3){
        printf("%c", 196);//196: ─
    }
    printf("%c", 217);//217: ┘
    repeat(SPC){
        printf(" ");
    }
    //

    printf("%c", 200);//200: ╚
    repeat(2){
        repeat(11){
            printf("%c", 205);//205: ═
        }
        printf("%c", 202);//202: ╩
    }

    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 188);//188: ╝

    repeat(11){
        printf(" ");// Espacio
    }

    //Segunda parte despues del espacio

    printf("%c", 200);//200: ╚
    repeat(2){
        repeat(11){
            printf("%c", 205);//205: ═
        }
        printf("%c", 202);//202: ╩
    }

    repeat(11){
        printf("%c", 205);//205: ═
    }
    printf("%c", 188);//188: ╝

}

void simplePrint(int S[ROWS][COLS]){

    printf("\n");

    for (int i = 0; i < ROWS; ++i) {
        printf("\n ");
        for (int j = 0; j < COLS; ++j) {
            if(S[i][j]!= 0 && S[i][j]!= -1){
                printf("[%d]", S[i][j]);
            }else{
                if(S[i][j]==0){
                    printf("[ ]");
                }else if(S[i][j]==-1){
                    printf("   ");
                }
            }
        }
    }

}

//Sudoku para probar la biblioteca//

int SUDOKU_TEST[ROWS][COLS]={
        0,2,9,0,0,0,5,1,0,-1,-1,-1,0,9,1,0,0,0,7,6,0,
        1,0,0,7,0,5,0,0,9,-1,-1,-1,4,0,0,6,0,9,0,0,5,
        6,0,0,2,0,9,0,0,3,-1,-1,-1,5,0,0,4,0,2,0,0,1,
        0,3,7,0,0,0,2,4,0,-1,-1,-1,0,6,9,0,0,0,8,7,0,
        0,0,0,0,0,0,0,0,0,-1,-1,-1,0,0,0,0,0,0,0,0,0,
        0,6,4,0,0,0,9,5,0,-1,-1,-1,0,5,7,0,0,0,1,4,0,
        4,0,0,9,0,6,0,0,2,0,0,0,7,0,0,8,0,4,0,0,3,
        3,0,0,8,0,1,0,0,5,0,0,0,9,0,0,2,0,3,0,0,7,
        0,8,6,0,0,0,1,9,0,0,8,0,0,2,3,0,0,0,4,9,0,
        -1,-1,-1,-1,-1,-1,0,0,0,2,0,7,0,0,0,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,0,0,9,0,0,0,3,0,0,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,0,0,0,6,0,1,0,0,0,-1,-1,-1,-1,-1,-1,
        0,6,4,0,0,0,9,2,0,0,7,0,0,3,1,0,0,0,9,5,0,
        3,0,0,8,0,6,0,0,7,0,0,0,2,0,0,5,0,4,0,0,8,
        5,0,0,4,0,9,0,0,1,0,0,0,5,0,0,9,0,3,0,0,2,
        0,3,7,0,0,0,8,1,0,-1,-1,-1,0,2,7,0,0,0,6,1,0,
        0,0,0,0,0,0,0,0,0,-1,-1,-1,0,0,0,0,0,0,0,0,0,
        0,2,5,0,0,0,4,7,0,-1,-1,-1,0,6,9,0,0,0,5,2,0,
        2,0,0,1,0,8,0,0,9,-1,-1,-1,7,0,0,4,0,6,0,0,1,
        4,0,0,9,0,3,0,0,2,-1,-1,-1,9,0,0,8,0,5,0,0,3,
        0,9,1,0,0,0,3,5,0,-1,-1,-1,0,8,4,0,0,0,7,9,0,
};

