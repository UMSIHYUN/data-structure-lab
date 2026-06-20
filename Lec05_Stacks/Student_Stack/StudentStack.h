#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAX_STRING = 20;
const int MAX_STACK_SIZE = 20;

// 오류 처리 함수
inline void error(const char* message) {
    printf("%s\n", message);
    exit(1);
}

class Student {
    int id;
    char name[MAX_STRING];
    char dept[MAX_STRING];
public:
	Student(int i = 0, const char* n = "", const char* d = "") { set(i, n, d); } //학생 생성자
    void set(int i, const char* n, const char* d) {
        id = i;
        strcpy_s(name, n);
        strcpy_s(dept, d);
    }
    void display() {
		printf("  학번:%-15d 성명:%-10s 학과:%-20s\n", id, name, dept); //학생 정보 출력, 빈칸확보 위해 %-15d, %-10s, %-20s 사용
    }
};

class StudentStack {
    int top;
    Student data[MAX_STACK_SIZE];
public:
    StudentStack() { top = -1; }
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX_STACK_SIZE - 1; }

    void push(Student e) {
        if (isFull()) error("스택 포화 에러");
        data[++top] = e;
    }

    Student pop() {
        if (isEmpty()) error("스택 공백 에러");
        return data[top--];
    }

    Student peek() {
        if (isEmpty()) error("스택 공백 에러");
        return data[top];
    }

    void display() {
        printf("[전체 학생의 수 = %2d] ==>\n", top + 1);
        for (int i = 0; i <= top; i++) {
            data[i].display();
        }
        printf("\n");
    }
};
