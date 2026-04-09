#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <cstring>

class Car {
protected:
    int speed;
    char name[40];
public:
    int gear;
    Car() : speed(0), gear(1) { strcpy(name, "Car"); }
    ~Car() {}

    Car(int s, char* n, int g) : speed(s), gear(g) {
        strcpy(name, n);
    }

    void changeGear(int g = 4) {
        gear = g;
    }

    void speedUp() {
        speed += 5;
    }

    // 한글 대신 영어로 수정
    void display() {
        printf("[%s] : Gear=%d, Speed=%dkmph\n", name, gear, speed);
    }

    void whereAmI() {
        printf("Address = %p\n", this);
    }
};