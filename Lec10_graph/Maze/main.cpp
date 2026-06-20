#include "Location2D.h"
#include <stack>
#include <deque>
using namespace std;

const int MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'},
};

bool isValidLoc(int r, int c)
{
	if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) return false;
	else return map[r][c] == '0' || map[r][c] == 'x';
}

void resetMap() {
	map[0][0] = '1'; map[0][1] = '1'; map[0][2] = '1'; map[0][3] = '1'; map[0][4] = '1'; map[0][5] = '1';
	map[1][0] = 'e'; map[1][1] = '0'; map[1][2] = '1'; map[1][3] = '0'; map[1][4] = '0'; map[1][5] = '1';
	map[2][0] = '1'; map[2][1] = '0'; map[2][2] = '0'; map[2][3] = '0'; map[2][4] = '1'; map[2][5] = '1';
	map[3][0] = '1'; map[3][1] = '0'; map[3][2] = '1'; map[3][3] = '0'; map[3][4] = '1'; map[3][5] = '1';
	map[4][0] = '1'; map[4][1] = '0'; map[4][2] = '1'; map[4][3] = '0'; map[4][4] = '0'; map[4][5] = 'x';
	map[5][0] = '1'; map[5][1] = '1'; map[5][2] = '1'; map[5][3] = '1'; map[5][4] = '1'; map[5][5] = '1';
}

void main() {
	int ds_num;
	printf("DFS 데이터구조 라이브러리 선택 1)stack, 2)deque \n");
	scanf_s("%d", &ds_num);

	switch (ds_num) {
	case 1:
	{
		stack<Location2D> locStack;
		Location2D entry(1, 0);
		locStack.push(entry);

		while (locStack.empty() == false) {
			Location2D here = locStack.top();
			locStack.pop();

			int r = here.row, c = here.col;
			printf(" (%d,%d)", r, c);
			if (map[r][c] == 'x') {
				printf("\n미로 탐색 성공\n");
				break;
			}
			else {
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) locStack.push(Location2D(r - 1, c));
				if (isValidLoc(r + 1, c)) locStack.push(Location2D(r + 1, c));
				if (isValidLoc(r, c - 1)) locStack.push(Location2D(r, c - 1));
				if (isValidLoc(r, c + 1)) locStack.push(Location2D(r, c + 1));
			}
		}
		resetMap();
		break;
	}

	case 2:
	{
		deque<Location2D> locDeque;
		Location2D entry(1, 0);
		locDeque.push_front(entry);

		while (locDeque.empty() == false) {
			Location2D here = locDeque.front();
			locDeque.pop_front();

			int r = here.row, c = here.col;
			printf(" (%d,%d)", r, c);
			if (map[r][c] == 'x') {
				printf("\n미로 탐색 성공\n");
				break;
			}
			else {
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) locDeque.push_front(Location2D(r - 1, c));
				if (isValidLoc(r + 1, c)) locDeque.push_front(Location2D(r + 1, c));
				if (isValidLoc(r, c - 1)) locDeque.push_front(Location2D(r, c - 1));
				if (isValidLoc(r, c + 1)) locDeque.push_front(Location2D(r, c + 1));
			}
		}
		resetMap();
		break;
	}
	}

	printf("\nBFS 미로 탐색\n");
	deque<Location2D> locDeque;
	locDeque.push_back(Location2D(1, 0));

	while (locDeque.empty() == false) {
		Location2D here = locDeque.front();
		locDeque.pop_front();

		int r = here.row, c = here.col;
		printf(" (%d,%d)", r, c);
		if (map[r][c] == 'x') {
			printf("\n미로 탐색 성공\n");
			return;
		}
		else {
			map[r][c] = '.';
			if (isValidLoc(r - 1, c)) locDeque.push_back(Location2D(r - 1, c));
			if (isValidLoc(r + 1, c)) locDeque.push_back(Location2D(r + 1, c));
			if (isValidLoc(r, c - 1)) locDeque.push_back(Location2D(r, c - 1));
			if (isValidLoc(r, c + 1)) locDeque.push_back(Location2D(r, c + 1));
		}
	}
	printf("\n미로 탐색 실패\n");
}