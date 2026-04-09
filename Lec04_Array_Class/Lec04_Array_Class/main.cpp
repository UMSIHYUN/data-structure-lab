#include <iostream>

using namespace std;

#define HEIGHT 8
#define WIDTH 8

// 1) 2차원 이미지에서 최대 화소 밝기를 구해서 반환하는 함수
int get_max_brightness(int img[HEIGHT][WIDTH]) {
    int max_val = img[0][0]; // 첫 번째 요소를 초기값으로 설정

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (img[i][j] > max_val) {
                max_val = img[i][j]; // 더 큰 값을 찾으면 업데이트
            }
        }
    }
    return max_val;
}

int main() {
    // 과제에서 주어진 예제 이미지 배열
    int image[HEIGHT][WIDTH] = {
        { 10,  30,  55,  80, 120, 160, 200, 230},
        { 20,  45,  70, 100, 140, 180, 220, 210},
        { 35,  60,  90, 130, 170, 210, 240, 190},
        { 50,  80, 115, 150, 190, 230, 255, 170},
        { 40,  65, 100, 140, 175, 215, 235, 150},
        { 25,  50,  80, 115, 155, 195, 210, 130},
        { 15,  35,  60,  90, 130, 165, 185, 110},
        {  5,  20,  40,  70, 105, 140, 160,  90}
    };

    // 함수 호출
    int max_brightness = get_max_brightness(image);

    // 결과 출력
    cout << "Max brightness: " << max_brightness << endl;

    return 0;
}
