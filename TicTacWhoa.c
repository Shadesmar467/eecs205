#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void initialVal(char pos[3][3]) {   
    //initialize every square to empty
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) { 
            if (row == 2) {
                pos[row][col] = ' ';
            } else {
                pos[row][col] = '_';
            }          
    }
    }
}

void updateGrid (char pos[3][3]) {
    //printing grid and current values
    printf("3 _%c_|_%c_|_%c_\n", pos[0][0], pos[0][1], pos[0][2]);
    printf("2 _%c_|_%c_|_%c_\n", pos[1][0], pos[1][1], pos[1][2]);
    printf("1  %c | %c | %c \n", pos[2][0], pos[2][1], pos[2][2]);
    printf("   A   B   C\n");
}

void processMove(bool gameOver, int *targetR, int *targetC, char in[2]) {
        if (in[0] =='q' && in[1] == 'u' && in[2] == 'u' && in[3] == 't') {
            gameOver = true;
        }
        
        if (in[0] == 'A') *targetC = 0;
        else if (in[0] == 'B') *targetC = 1;
        else if (in[0] == 'C') *targetC = 2;

        if (in[1] == '1') *targetR = 2;
        else if (in[1] == '2') *targetR = 1;
        else if (in[1] == '3') *targetR = 0;

        
}

void checkOOB(char pos[3][3], int r, int c, bool *OOB) {
    if (((c > 2) || (r > 2)) || ((c < 0) || (r < 0))) { //test if the input is in the grid
        printf("Invalid move, please specify a valid column and row.\n");
        *OOB = true;
    } else {
        if ((pos[r][c] == '_') || (pos[r][c] == ' ')) { //test if the input is taken already
            *OOB = false;
        } else {
            printf("This spot has already been taken. Please choose another.\n");
            *OOB = true;
        }
        
    }
}

void makeMove(char pos[3][3], int player, int targetR, int targetC) {
    if (player == 1) pos[targetR][targetC] = 'X';
    if (player == 2) pos[targetR][targetC] = 'O';
}

void checkEnd() {

}

int main () {
    int player = 1;
    char input[50];             //player input saved here
    char pos[3][3];             //2d array keeping track of user inputs
    bool gameOver = false;      //Is the game over?
    bool OOB;                   //Out-of-Bounds check
    int targetR;                //target Row used per iteration
    int targetC;                //target Column used per iteration
    initialVal(pos);            //set initial board
    updateGrid(pos);            //print initial board

    //one iteration of the while loop = one turn
    while (gameOver != true) {
        //waiting for valid input
        do {
            printf("\nPlayer %d's Move: ", player);
            scanf("%s", &input);

            processMove(gameOver, &targetR, &targetC, input);
            if (gameOver == true) {
                break;
            }
            checkOOB(pos, targetR, targetC, &OOB); //checks if input is out-of-bounds

        } while (OOB == true);

        makeMove(pos, player, targetR, targetC);
        updateGrid(pos);

        //change player
        if (player == 1) player = 2;
        else player = 1;

        //set targets back to out of bounds
        targetR = 4;
        targetC = 4;
    }
    return 0;
}