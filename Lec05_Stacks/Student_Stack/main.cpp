#include "StudentStack.h"

int main() {
    StudentStack stack;

    stack.push(Student(202514124, "최우진", "컴퓨터인공지능학부"));
    stack.push(Student(202513851, "이규빈", "전자공학부"));
    stack.push(Student(202524090, "김윤기", "전자공학부"));

    stack.display();
    stack.peek();
    stack.pop();
    stack.pop();
    stack.display();

    return 0;
}