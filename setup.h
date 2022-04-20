#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int ASSIGN_1 = 0;
const int ASSIGN_2 = 1;
const int ADD_PLAYER = 2;
const int DELETE_PLAYER = 3;
const int CONFIRM_PLAYERS = 4;
const int INVALID = 5;

extern const int max_players;


void clear_board(int board[6][7]) {
    // makes board all zeros
    int i, j;
    for (i = 0; i < 6; i=i+1) {
        for (j = 0; j < 7; j++) {
            board[i][j] = 0;
        }
    }
}

int next_available(char all_players[max_players][11]) {
    // returns next available index
    int i;
    char player[11];
    for (i = 0; i < max_players; i++) {
        memset(player, 0, sizeof player);
        strcpy(player, all_players[i]);
        if (player[0] == '\0') {
            return i;
        }
    }
    return max_players; 
}

void show_players(char all_players[max_players][11], int next) {
    if (next == 0) { // next available index
        printf("%s", "No players yet. \n\n");
    } else {
        printf("%s", "Here are the current players. \n");
        char player[11];
        int i;
        for (i = 0; i < max_players; i ++) {
            memset(player, 0, sizeof player);
            strcpy(player, all_players[i]); // get player at index

            if (player[0] == '\0') {        // if empty
                break;
            }
            printf("%d. %s\n", i + 1, player);
        }
        printf("\n");
    }
}

int player_screen(char all_players[max_players][11], int player_arr[2], int next) {
    // display player screen
    // allow user to choose next step

    show_players(all_players, next);
    
    printf("%s", "Current Assignments:\n");
    char player1[11];
    char player2[11];
    if (player_arr[0] < max_players) {
        strcpy(player1, all_players[player_arr[0]]);
    } else {
        strcpy(player1, "");
    }
    if (player_arr[1] < max_players) {
        strcpy(player2, all_players[player_arr[1]]);
    } else {
        strcpy(player2, "");
    }
    printf("Player 1: %s\n", player1);
    printf("Player 2: %s\n\n", player2);

    
    printf("%s", "Press\n1 \t Assign player 1\n2 \t Assign player 2\n");
    printf("%s", "a \t Add a new player\n");
    printf("%s", "b \t Delete an existing player\n");
    printf("%s", "c \t Begin gameplay!\n");
    
    printf("\n");

    char buffer[3];
    fgets(buffer, 3, stdin);
    printf("\n");
    char input = buffer[0];

    if (input == '1') return ASSIGN_1;
    else if (input == '2') return ASSIGN_2;
    else if (input == 'a') return ADD_PLAYER;
    else if (input == 'b') return DELETE_PLAYER;
    else if (input == 'c') return CONFIRM_PLAYERS;
    else return INVALID;
}

int select_player(char all_players[max_players][11], int next) {
    // selects existing player

    char buffer[3];
    fgets(buffer, 3, stdin);
    int num = buffer[0] - '0';

    if (num > 0 && num <= next) {
        return num;
    } else {
        return 0;
    }
}

void get_new_player(char new_player[11]) {
    // gets a player name, puts in new_player
    printf("%s", "Enter new player's name: ");
    char buffer[11];

    fgets(buffer, 10, stdin);
    printf("\n");
    buffer[strcspn(buffer, "\n")] = 0;  // remove newline
    buffer[10] = '\0';

    strcpy(new_player, buffer);
}

int confirm_delete(char player[11]) {
    // asks user again if they want to delete
    // returns 1 to confirm delete and 0 otherwise

    printf("Are you sure you want to delete %s? (y/n) ", player);

    char buffer[3];
    fgets(buffer, 3, stdin);
    printf("\n");
    buffer[strcspn(buffer, "\n")] = 0;  // remove newline

    if (strcmp(buffer, "y") == 0) return 1;
    else return 0;
}

void do_delete(char all_players[10][11], int player_index) {
    // delete player and shift all back
    for (int i = player_index + 1; i < 10; i ++) {
        strcpy(all_players[i - 1], all_players[i]); // move everything one back
    }
    all_players[9][0] = '\0';
}

