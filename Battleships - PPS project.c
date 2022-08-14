//5x5 Battleship game
//PPS Project

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void print_board(char board[5][5]);//function declaration

char board[5][5] = {{'~','~','~','~','~'},{'~','~','~','~','~'},{'~','~','~','~','~'},{'~','~','~','~','~'},{'~','~','~','~','~'}};
int guessed[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
int i,j,n=5;//used to print the board
int a, pos1, pos2, l;//used to select tile
int test = 1;//used to place ship
char attack[4];
int row, col;
int tries = 0;//used to keep track of score
int shp = 0;//number of tiles occupied
char end;

//code to generate random number between 0 and 4 is (5 not included)
// rand_num = (rand() % (5) + 0);


int main() {
    srand(time(0));//to use the random function

    print_board(board);

//placing ships from largest to smallest
n = 5;
    for (l = n-1; l>1; l-- ){//the ship length(l) should be smaller than the board
        shp = shp + l;
        pos1 = (rand() % (n) + 0);
        pos2 = (rand() % (n) + 0);
        a = (rand() % (2) + 0);//vertical or horizontal

        if (a == 0){//horizontal
            j = 0;
            for (j=0; j<l; j++){
        //to check if all points occupied by the ship are empty, and space is there
                if (board[pos1][pos2+j] != '~' || pos2>n-l){
                    pos1 = (rand() % (n) + 0);
                    pos2 = (rand() % (n-l) + 0);
                    j = -1;//generate new points and check again
                }
            }

            for(j=0; j<l; j++){
                board[pos1][pos2+j] = 'x';//marking the points
            }

        }
        else if (a == 1){//vertical, same working
            for (j=0; j<l; j++){
                if (board[pos1+j][pos2] != '~' || pos1>n-l){
                    pos1 = (rand() % (n-l) + 0);
                    pos2 = (rand() % (n) + 0);
                    j = -1;
                }
            }
            for(j=0; j<l; j++){
                board[pos1+j][pos2] = 'x';
            }
        }
    }


    printf("\n\nWelcome to Battleship!\nThe ocean contains one each of 4x1, 3x1 and 2x1 ships  (placed horizontally or vertically)\nAttack tiles and destroy the ships to win. \nEnter q to quit\n");

//attacking and checking
    while (1){//infinite loop
        //making guesses
        printf("\nEnter cell to attack (eg, A4): ");
        fgets(attack,4,stdin);//extra space for newline

        if (attack[0]>='a' && attack[0]<='e'){//converting guess to indices
            col = attack[0] - 'a';
        }
        else if (attack[0]>='A' && attack[0]<='E'){
            col = attack[0] - 'A';
        }
        else if (attack[0]=='q' || attack[0]=='Q' ){
        //To print out the board as it is
            printf("\n\n    A\t   B\t   C\t   D\t   E");
            for (i = 0; i<5; i++){
                printf("\n\n");//new line for each row
                printf("%d",i+1);//row number
                for (j=0; j<5; j++){
                    printf("  %c%c    ",board[i][j],board[i][j]);
                }
                printf("\n");
                for (j=0; j<5; j++){
                    printf("   %c%c   ",board[i][j],board[i][j]);
                }
            }
            printf("\n\nYou quit. Game over");
            break;
        }
        else {
            printf("\nInvalid input. Try again.");
            continue;
        }
        row = attack[1] - '0' - 1;
        if (row<0 || row>4){
            printf("\nInvalid input. Try again.");
            continue;
        }

        //attacking
        if (guessed[row][col]== 1){
            printf("\nYou've already attacked that cell");
            continue;
        }
        else{
            if (board[row][col] == '~'){
                printf("\n\nMiss!");
                board[row][col] = '0';//miss
            }
            else if (board[row][col] == 'x'){
                printf("\n\nHit!");
                board[row][col] = '1';//hit
                shp = shp - 1;
            }

            guessed[row][col] = 1;//mark as guessed
        }
        tries = tries + 1;

        print_board(board);

        //checking if any ship's tiles are left
        if (shp == 0){
            printf("\n\nYou win!");
            break;
        }

    }

printf("\n\nYou took %d tries", tries);
printf("\nThanks for playing\n\n");
printf("Press the enter key to exit");
scanf("%c",&end);
}

//function to print the board
void print_board(char board[5][5]){//function definition
    char sym;
    //To print out the board
    printf("\n\n    A\t   B\t   C\t   D\t   E");
    for (i = 0; i<5; i++){
        printf("\n\n");//new line for each row
        printf("%d",i+1);//row number
        for (j=0; j<5; j++){
            if (board[i][j] == 'x'){//to hide the ships
                sym = '~';
            }
            else {
                sym = board[i][j];
            }
            printf("  %c%c    ",sym,sym);
        }
        printf("\n");
        for (j=0; j<5; j++){
            if (board[i][j] == 'x'){
                sym = '~';
            }
            else {
                sym = board[i][j];
            }
            printf("   %c%c   ",sym,sym);
        }
    }
}
/*code to print the board as is for testing

    printf("\n\n");
    for (i = 0; i<5; i++){
        printf("\n\n");//new line for each row
        printf("%d",i+1);//row number
        for (j=0; j<5; j++){
            printf("  %c%c ",board[i][j],board[i][j]);
        }
        printf("\n");
        for (j=0; j<5; j++){
            printf("   %c%c",board[i][j],board[i][j]);
        }
    }*/
