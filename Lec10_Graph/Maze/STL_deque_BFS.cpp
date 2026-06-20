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
    locDeque.push_back(entry); // BFS: 뒤쪽으로 삽입 (Queue 방식)

    while (locDeque.empty() == false) {
        Location2D here = locDeque.front(); // 먼저 들어온 데이터를 앞(front)에서 복사
        locDeque.pop_front();               // 앞(front)에서 꺼내기

        int r = here.row, c = here.col;
        printf("(%d,%d) ", r, c);

        if (map[r][c] == 'x') {
            printf("미로 탐색 성공\n");
            return 0;
        }
        else {
            map[r][c] = '.';
            // BFS 탐색을 위해 back에 밀어넣기 (FIFO 구조 형성)
            if (isValidLoc(r - 1, c)) locDeque.push_back(Location2D(r - 1, c));
            if (isValidLoc(r + 1, c)) locDeque.push_back(Location2D(r + 1, c));
            if (isValidLoc(r, c - 1)) locDeque.push_back(Location2D(r, c - 1));
            if (isValidLoc(r, c + 1)) locDeque.push_back(Location2D(r, c + 1));
        }
    }
    printf("미로 탐색 실패\n");
    return 0;
}