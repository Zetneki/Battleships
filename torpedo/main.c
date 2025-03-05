#include <stdio.h>
#include "stdlib.h"
#include "conio.h"
#include "string.h"

void board_score_fillup(char** board, int size, char score[size][size], const char copy[100]);
void print(char** board, int size, char score[size][size]);
void input(char** board, int size, char score[size][size], int* steps);
void end(char** board, int size, char score[size][size], int* final, int* num);
int restart();

int main() {
    //----------------declaring values----------------------
    char copy[100];
    int size;
    int length = -1;
    char character;
    int number1 = 1;
    int value = 0;
    char enter;
    //-------------------file write-----------------------
    printf(" .-') _                _  .-')     _ (`-.    ('-.  _ .-') _\n");
    printf("(  OO) )              ( \\( -O )   ( (OO  ) _(  OO)( (  OO) )\n");
    printf("/     '._  .-'),-----. ,------.  _.`     \\(,------.\\     .'_  .-'),-----.\n");
    printf("|'--...__)( OO'  .-.  '|   /`. '(__...--'' |  .---',`'--..._)( OO'  .-.  '\n");
    printf("'--.  .--'/   |  | |  ||  /  | | |  /  | | |  |    |  |  \\  '/   |  | |  |\n");
    printf("   |  |   \\_) |  |\\|  ||  |_.' | |  |_.' |(|  '--. |  |   ' |\\_) |  |\\|  |\n");
    printf("   |  |     \\ |  | |  ||  .  '.' |  .___.' |  .--' |  |   / :  \\ |  | |  |\n");
    printf("   |  |      `'  '-'  '|  |\\  \\  |  |      |  `---.|  '--'  /   `'  '-'  '\n");
    printf("   `--'        `-----' `--' '--' `--'      `------'`-------'      `-----' \n");

    printf("\n\n                    Welcome to TORPEDO-BOAT-DESTROYER-2000!\n");

    jump:

    printf("\nPlayer 1 please type in the N size (N x N) of the board (maximum value can be 5): ");
    scanf("%d", &size);
    while (size > 5 || size < 2) {
        printf("Wrong size given. Try again.\n");
        scanf("%d", &size);
    }
    int number2 = size;

    FILE* in = fopen("tabla.txt", "w");

    fprintf(in, "%d", size);

    printf("Please type in the characters of the board. They must be 'x' or 'o'!\n");

    for (int i = 0; i < size * size; ++i) {
        printf("\n%d. character out of the %d. row (%d/%d):\n", i + 1, number1, value + 1, number2);
        scanf(" %c", &character);
        while (character != 'x' && character != 'o') {
            printf("\nWrong character given. Try again.\n");
            printf("%d. character out of the %d. row (%d/%d):\n", i + 1, number1, value + 1, number2);
            scanf(" %c", &character);
        }
        fprintf(in, "%c", character);

        value++;
        value == size ? number1++ : number1;
        value == size ? value = 0 : value;
    }
    printf("\n");
    system("cls");

    printf(" .-') _                _  .-')     _ (`-.    ('-.  _ .-') _\n");
    printf("(  OO) )              ( \\( -O )   ( (OO  ) _(  OO)( (  OO) )\n");
    printf("/     '._  .-'),-----. ,------.  _.`     \\(,------.\\     .'_  .-'),-----.\n");
    printf("|'--...__)( OO'  .-.  '|   /`. '(__...--'' |  .---',`'--..._)( OO'  .-.  '\n");
    printf("'--.  .--'/   |  | |  ||  /  | | |  /  | | |  |    |  |  \\  '/   |  | |  |\n");
    printf("   |  |   \\_) |  |\\|  ||  |_.' | |  |_.' |(|  '--. |  |   ' |\\_) |  |\\|  |\n");
    printf("   |  |     \\ |  | |  ||  .  '.' |  .___.' |  .--' |  |   / :  \\ |  | |  |\n");
    printf("   |  |      `'  '-'  '|  |\\  \\  |  |      |  `---.|  '--'  /   `'  '-'  '\n");
    printf("   `--'        `-----' `--' '--' `--'      `------'`-------'      `-----' \n");

    printf("\nNow player 2 can begin guessing the place of the 'x'-s.\n\n");
    printf("Press enter to start.\n");
    getch();

    fclose(in);

    //-------------------file read------------------------
    FILE* out = fopen("tabla.txt", "r");

    fscanf(in, "%d", &size);

    for (int i = 0; !feof(in); ++i) {
        fscanf(in, "%c", &copy[i]);
        length++;
    }
    copy[length] = '\0';

    fclose(out);
    //----------------------declaring arrays and pointers----------------------
    char **board = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; ++i) {
        board[i] = (char*)malloc(sizeof(char));
    }

    char score[size][size];

    int *final = (int*)malloc(sizeof(int));

    int *num = (int*)malloc(sizeof(int));

    int *steps = (int*)malloc(sizeof(int));
    *steps = 0;
    //----------------main-------------------------------

    board_score_fillup(board, size, score, copy);
    system("cls");

    do {

        input(board, size, score, steps);
        end(board, size, score, final, num);

    } while (*final != *num);

    printf("The game has ended.\n\n");
    if (*steps == size*size) {
        printf("Player 1 has won the game!\n\n");
    } else if (*steps < size*size) {
        printf("Player 2 has won the game!\n\n");
    }
    printf("Number of steps: %d\n", *steps);
    printf("The original board's values:\n\n");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%c    ", board[i][j]);
        }
        printf("\n\n");
    }

    if (restart() == 1) {
        system("cls");
        goto jump;
    }

    //-------------------main--------------------------
    //-------------------------freeing pointers----------------------
    for (int i = 0; i < size; ++i) {
        free(board[i]);
    }
    free(board);
    free(final);
    free(num);
    free(steps);
    getch();
    return 0;
}

void board_score_fillup(char** board, int size, char score[size][size], const char copy[100]) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] = copy[i * size + j];
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            score[i][j] = '?';
        }
    }
}

void print(char** board, int size, char score[size][size]) {

    printf("\n");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%c    ", score[i][j]);
        }
        printf("\n\n");
    }
    printf("\n");
}

void input(char** board, int size, char score[size][size], int* steps) {

    int row, col;
    printf("\nRow: ");
    scanf("%d", &row);

    printf("Column: ");
    scanf("%d", &col);

    row-=1;
    col-=1;

    if (row >= 0 && row < size && col >= 0 && col < size) {
        system("cls");
        score[row][col] == 'x' || score[row][col] == 'o' ? (*steps)-- : *steps;
        score[row][col] = board[row][col] == 'x' ? 'x' : 'o';
        print(board, size, score);
        (*steps)++;
    } else {
        printf("\nWrong coordinates given. Try again.\n");
    }

}

void end(char** board, int size, char score[size][size], int* final, int* num) {

    *final = 0;
    *num = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] == 'x' ? (*final)++ : *final;
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            score[i][j] == 'x' ? (*num)++ : *num;
        }
    }
}

int restart() {

    printf("\nWould you like to play again? (yes/no)\n");
    char decide[4];
    scanf("%s", decide);

    if (strcmp(decide, "yes") == 0) {
        return 1;
    }

    return 0;
}