#include <stdio.h>
#include <stdlib.h>

// Function declarations
void displayBoard();
int checkWin();
int isDraw();
void resetBoard();
void switchPlayer();
void playGame();

// Global Variables
char board[3][3];
char currentPlayer = 'X';

int main() {
    char playAgain;

    do {
        resetBoard();
        playGame();

        printf("\nDo you want to play again? (Y/N): ");
        scanf(" %c", &playAgain);
        playAgain = (playAgain >= 'a' && playAgain <= 'z') ? playAgain - 32 : playAgain; // Uppercase

    } while (playAgain == 'Y');

    printf("Thanks for playing!\n");
    return 0;
}

// Reset the board
void resetBoard() {
    int count = 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
    currentPlayer = 'X';
}

// Display the game board
void displayBoard() {
    printf("\n");
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n\n", board[2][0], board[2][1], board[2][2]);
}

// Check for win conditions
int checkWin() {
    for (int i = 0; i < 3; i++) {
        // Check rows and columns
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer))
            return 1;
    }
    // Diagonals
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer))
        return 1;

    return 0;
}

// Check for draw
int isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

// Switch players
void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Play one game
void playGame() {
    int row, col;
    int gameOver = 0;

    printf("TIC-TAC-TOE GAME\nPlayer 1: X  |  Player 2: O\n");

    while (!gameOver) {
        displayBoard();

        // Input
        printf("Player %c, enter your move (row and column: 1-3 1-3): ", currentPlayer);
        scanf("%d %d", &row, &col);

        row--; col--; // Adjusting index (0-based)
        
        if (row >= 0 && row < 3 && col >= 0 && col < 3) {
            if (board[row][col] == ' ') {
                board[row][col] = currentPlayer;

                if (checkWin()) {
                    displayBoard();
                    printf("Player %c wins! 🎉\n", currentPlayer);
                    gameOver = 1;
                } else if (isDraw()) {
                    displayBoard();
                    printf("It's a draw!\n");
                    gameOver = 1;
                } else {
                    switchPlayer();
                }

            } else {
                printf("Cell already occupied! Try again.\n");
            }
        } else {
            printf("Invalid input. Please enter values between 1 and 3.\n");
        }
    }
}
