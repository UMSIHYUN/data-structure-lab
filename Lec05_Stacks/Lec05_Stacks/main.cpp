#include "ArrayStack.h"

int main() {
    ArrayStack stack;

    // 데이터 순차 삽입 및 출력
    for (int i = 1; i < 10; i++) {
        stack.push(i);
    }
    stack.display();
    stack.pop();
    stack.pop();
    stack.pop();
    stack.display();

    return 0;
}