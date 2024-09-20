// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI

#include <stdio.h>

#define border_x 80
#define border_y 25
#define r_length 3
#define r_x 5  // отступ ракетки

int GoalCheck(int ball_x) {
    int GoalCheck = 0;
    if (ball_x == 1) {
        GoalCheck = 2;
    }
    if (ball_x == 79) {
        GoalCheck = 1;
    }
    return GoalCheck;
}
int rickochetCheckX(int ball_x, int ball_y, int r1_y, int r2_y, int ball_vector_x) {
    int rickochetCheckX = ball_vector_x;

    if ((ball_x == r_x + 1 && ball_vector_x == -1 && ball_y >= r1_y && ball_y <= r1_y + r_length) ||
        (ball_x == border_x - r_x - 1 && ball_vector_x == 1 && ball_y >= r2_y && ball_y <= r2_y + r_length)) {
        rickochetCheckX *= -1;
    }

    return rickochetCheckX;
}
int rickochetCheckY(int ball_y, int ball_vector_y) {
    int rickochetCheckY = ball_vector_y;

    if ((ball_y == 2 && ball_vector_y == -1) || (ball_y == 24 && ball_vector_y == 1)) {
        rickochetCheckY *= -1;
    }

    return rickochetCheckY;
}
void getScore(int p1_score, int p2_score) {
    printf("%02d / %02d \n", p1_score, p2_score);

    if (p1_score == 21) {
        printf("Player 1 won! \n");
    }
    if (p2_score == 21) {
        printf("Player 2 won! \n");
    }
}
void getDisplay(int ball_x, int ball_y, int r1_y, int r2_y) {
    int length_counter1 = 1;
    int length_counter2 = 1;

    for (int y = 1; y <= border_y; y++) {
        for (int x = 1; x <= border_x; x++) {
            if (y == 1) {
                printf("▄");
                continue;
            }
            if (y == border_y) {
                printf("▀");
                continue;
            }
            if (y > 1 && (x == 1 || x == border_x)) {
                printf("║");
                continue;
            }
            if (x == ball_x && y == ball_y) {
                printf("o");
                continue;
            }
            if (x == r_x && (y >= r1_y && length_counter1 <= r_length)) {
                printf("▓");
                length_counter1++;
                continue;
            }
            if ((x == border_x - r_x) && (y >= r2_y && length_counter2 <= r_length)) {
                printf("▓");
                length_counter2++;
                continue;
            }
            printf(" ");
        }
        printf("\n");
    }
}

int main() {
    int ball_x = border_x / 2;  // initial ball position as first x value
    int ball_y = border_y / 2;  // initial ball position as first y value // changed x to y
    int ball_vector_x = 1;
    int ball_vector_y = 1;
    int r1_y = border_y / 2;
    int r2_y = border_y / 2;
    int p1_score = 0;
    int p2_score = 0;

    while (p1_score <= 21 && p2_score <= 21) {
        printf(
            "Press Space Bar to play |\nA/Z - Up/Down for player 1 | K/M - Up/Down for player 2 | 21 points "
            "to win! LET'S GO!\n");
        char key;  // variable for ke from input for playing
        key = getc(stdin);

        if (key == 'a' || key == 'A' || key == 'z' || key == 'Z' || key == 'k' || key == 'K' || key == 'm' ||
            key == 'M' || key == ' ') {
            if (GoalCheck(ball_x) == 1) {
                ball_x = border_x / 2;
                ball_y = border_y / 2;
                p1_score++;
                ball_vector_y *= -1;
            }
            if (GoalCheck(ball_x) == 2) {
                ball_x = border_x / 2;
                ball_y = border_y / 2;
                p2_score++;
                ball_vector_y *= 1;
            }
            if ((key == 'a' || key == 'A') && r1_y >= 1) {
                r1_y--;
            }
            if ((key == 'z' || key == 'Z') && r1_y <= border_y - r_length - 1) {
                r1_y++;
            }
            if ((key == 'k' || key == 'K') && r2_y >= 1) {
                r2_y--;
            }
            if ((key == 'm' || key == 'M') && r2_y <= border_y - r_length - 1) {
                r2_y++;
            }
            ball_vector_x = rickochetCheckX(ball_x, ball_y, r1_y, r2_y, ball_vector_x);
            ball_x += ball_vector_x;
            ball_vector_y = rickochetCheckY(ball_y, ball_vector_y);
            ball_y += ball_vector_y;

            printf("\033[2J");
            getScore(p1_score, p2_score);
            getDisplay(ball_x, ball_y, r1_y, r2_y);
        }
        printf("\033[2J");
        getScore(p1_score, p2_score);
        getDisplay(ball_x, ball_y, r1_y, r2_y);
    }
}
