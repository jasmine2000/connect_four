#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void sort_names_scores(char all_players[10][11], int all_scores[10], int player_arr[2]) {
    // sorts all players and scores from 
    // highest to lowest
    int i, j, k;
    int sorted;
    char lastplayer[11];
    char player[11];

    for (i = 0; i < 9; i++) {
        sorted = 1;
        memset(lastplayer, 0, sizeof lastplayer);
        strcpy(lastplayer, all_players[0]); // first player

        for (j = 1; j < 10; j++) {
            memset(player, 0, sizeof player);
            strcpy(player, all_players[j]); // get player at index
            if (player[0] == '\0') {        // if empty
                break;
            }
            if (all_scores[j] > all_scores[j - 1]) {
                strcpy(all_players[j], lastplayer); // swap players
                strcpy(all_players[j - 1], player);

                int temp = all_scores[j];           // swap scores
                all_scores[j] = all_scores[j - 1];
                all_scores[j - 1] = temp;

                sorted = 0;
                // lastplayer is same

                for (k = 0; k < 2; k ++) {
                    if (player_arr[k] == j) {
                        player_arr[k] = j - 1;
                    }
                }

            } else {
                memset(lastplayer, 0, sizeof lastplayer);
                strcpy(lastplayer, player);
            }
        }
        if (sorted == 1) break;
    }
}

void show_stats(char all_players[10][11], int all_scores[10]) {
    // prints out leaderboard
    printf("LEADERBOARD\n");
    for (int i = 0; i < 10; i=i+1) {
        char player[11] = {0};
        strcpy(player, all_players[i]); // get player at index

        if (player[0] != '\0') {        // if empty
            printf("%s\t| %d\n", player, all_scores[i]);
        }
    }
}