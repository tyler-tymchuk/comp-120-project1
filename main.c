// tic tac toe coding project due NOV 11
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARD_SIZE 9

void init_board(char board[]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = ' ';
    }
}

void display_board(char board[]) {
    char c[BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++) {
        c[i] = board[i];

        if (c[i] == ' ') {
            c[i] = '0' + i;
        }
    }

    printf("\n");
    printf(" %c | %c | %c\n", c[0], c[1], c[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", c[3], c[4], c[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", c[6], c[7], c[8]);
    printf("\n");
}

bool is_winner(char board[], char player) {
    if (board[0] == player && board[1] == player && board[2] == player)
        return true;

    if (board[3] == player && board[4] == player && board[5] == player)
        return true;

    if (board[6] == player && board[7] == player && board[8] == player)
        return true;

    if (board[0] == player && board[3] == player && board[6] == player)
        return true;

    if (board[1] == player && board[4] == player && board[7] == player)
        return true;

    if (board[2] == player && board[5] == player && board[8] == player)
        return true;

    if (board[0] == player && board[4] == player && board[8] == player)
        return true;

    if (board[2] == player && board[4] == player && board[6] == player)
        return true;

    return false;
}

char other_player(char player) {
    if (player == 'O') {
        return 'X';
    }

    return 'O';
}

int get_human_move(char board[]) {
    int move;
    bool valid = false;

    while (!valid) {
        printf("Your turn (O). Enter a square number (0-8): ");

        if (scanf("%d", &move) != 1) {
            printf("Invalid input. Please enter a number from 0 to 8.\n");

            while (getchar() != '\n') {
            }
        }
        else if (move < 0 || move > 8) {
            printf("Invalid square. Please enter a number from 0 to 8.\n");
        }
        else if (board[move] != ' ') {
            printf("That square is already taken.\n");
        }
        else {
            valid = true;
        }
    }

    return move;
}

int get_computer_move(char board[]) {
    int move;

    do {
        move = rand() % BOARD_SIZE;
    } while (board[move] != ' ');

    return move;
}

void take_turn(char board[], char player) {
    int move;

    if (player == 'O') {
        move = get_human_move(board);
    }
    else {
        printf("Computer (X) is thinking...\n");
        move = get_computer_move(board);
        printf("Computer (X) chose square %d. Your move next!\n", move);
    }

    board[move] = player;
}

bool board_full(char board[]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == ' ') {
            return false;
        }
    }

    return true;
}

void play_game(void) {
    char board[BOARD_SIZE];
    char player = 'O';
    bool game_over = false;

    init_board(board);
    display_board(board);

    for (int turn = 0; turn < BOARD_SIZE && !game_over; turn++) {

        take_turn(board, player);
        display_board(board);

        if (is_winner(board, player)) {
            if (player == 'O') {
                printf("You win!\n");
            }
            else {
                printf("The computer wins!\n");
            }

            game_over = true;
        }
        else if (board_full(board)) {
            printf("It's a draw!\n");
            game_over = true;
        }
        else {
            player = other_player(player);
        }
    }
}

bool play_again(void) {
    char answer;

    do {
        printf("Play again? Enter y to play again or q to quit: ");
        scanf(" %c", &answer);

        if (answer != 'y' && answer != 'q') {
            printf("Invalid choice. Please enter y or q.\n");
        }

    } while (answer != 'y' && answer != 'q');

    return answer == 'y';
}

int main(void) {
    srand(time(NULL));

    
    printf("You are O and you go first. The computer is X.\n");
    printf("On your turn, type the number of an empty square:\n");

    do {
        play_game();
    } while (play_again());

    printf("Thanks for playing\n");

    return 0;
}



