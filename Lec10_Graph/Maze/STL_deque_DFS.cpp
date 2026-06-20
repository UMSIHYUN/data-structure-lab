#include "Location2D.h"
#include <cstdio>
#include <deque>

using namespace std;
const int MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'},
};

bool isValidLoc(int r, int c) {
    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) return false;
    else return map[r][c] == '0' || map[r][c] == 'x';
}

int main() {
    deque<Location2D> locDeque;
    Location2D entry(1, 0);
    locDeque.push_front(entry); // À§Ä¡ µ¦ »ý¼º, ÀÔ±¸ »ðÀÔ

    while (locDeque.empty() == false) {
        Location2D here = locDeque.front(); // µ¦ÀÇ front »ó´Ü °´Ã¼ º¹»ç
        locDeque.pop_front();               // µ¦ »ó´Ü °´Ã¼ »èÁ¦

        int r = here.row, c = here.col;
        printf("(%d,%d) ", r, c);

        if (map[r][c] == 'x') {
            printf("¹Ì·Î Å½»ö ¼º°ø\n");
            return 0;
        }
        else {
            map[r][c] = '.'; // ÇöÀç À§Ä¡¸¦ Áö³ª¿È
            if (isValidLoc(r - 1, c)) locDeque.push_front(Location2D(r - 1, c));
            if (isValidLoc(r + 1, c)) locDeque.push_front(Location2D(r + 1, c));
            if (isValidLoc(r, c - 1)) locDeque.push_front(Location2D(r, c - 1));
            if (isValidLoc(r, c + 1)) locDeque.push_front(Location2D(r, c + 1));
        }
    }
    printf("¹Ì·Î Å½»ö ½ÇÆÐ\n");
    return 0;
}