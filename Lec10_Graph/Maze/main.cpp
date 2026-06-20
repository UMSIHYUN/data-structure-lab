
// STL STACK DFS

#include "Location2D.h"
#include <cstdio>
#include <stack>

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
    stack<Location2D> locStack;
    Location2D entry(1, 0); // 입구 객체
    locStack.push(entry);   // 스택에 입구 위치 삽입

    while (locStack.empty() == false) {
        Location2D here = locStack.top(); // 스택 상단 요소 복사
        locStack.pop();                   // 스택 상단 요소 제거

        int r = here.row, c = here.col;
        printf("(%d,%d) ", r, c);

        if (map[r][c] == 'x') {
            printf("미로 탐색 성공\n");
            return 0;
        }
        else {
            map[r][c] = '.'; // 현재 위치를 "지나옴" 처리
            // 상, 하, 좌, 우 위치를 유효성 검사 후 스택에 삽입
            if (isValidLoc(r - 1, c)) locStack.push(Location2D(r - 1, c));
            if (isValidLoc(r + 1, c)) locStack.push(Location2D(r + 1, c));
            if (isValidLoc(r, c - 1)) locStack.push(Location2D(r, c - 1));
            if (isValidLoc(r, c + 1)) locStack.push(Location2D(r, c + 1));
        }
    }
    printf("미로 탐색 실패\n");
    return 0;
}