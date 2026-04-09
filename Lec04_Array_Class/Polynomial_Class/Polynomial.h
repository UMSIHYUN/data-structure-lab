#pragma once
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

class Polynomial {
    vector<float> coef;
public:
    int degree() { return coef.empty() ? 0 : (int)coef.size() - 1; }

    // 0인지 확인하는 함수 (UML에 포함됨)
    bool isZero() {
        return coef.empty() || (degree() == 0 && coef[0] == 0);
    }

    // 부호를 반전시키는 함수 (UML에 포함됨)
    void negate() {
        for (int i = 0; i < coef.size(); i++) {
            coef[i] = -coef[i];
        }
    }

    void read() {
        int deg; float value;
        printf("Input max degree: ");
        scanf_s("%d", &deg);
        printf("Input coefficients (%d total): ", deg + 1);
        for (int i = 0; i <= deg; i++) {
            scanf_s("%f", &value);
            coef.push_back(value);
        }
    }

    void display(const char* str = "Poly = ") {
        printf("\t%s", str);
        if (isZero()) {
            printf(" 0\n");
            return;
        }
        int deg = degree();
        for (int i = 0; i < deg; i++) {
            printf("%5.1f x^%d + ", coef[i], deg - i);
        }
        // 마지막 상수항 (x가 붙지 않음)
        printf("%4.1f\n", coef[deg]);
    }

    void add(Polynomial a, Polynomial b) {
        // (기존 add 로직과 동일)
        if (a.degree() > b.degree()) {
            *this = a;
            int diff = a.degree() - b.degree();
            for (int i = 0; i <= b.degree(); i++) coef[i + diff] += b.coef[i];
        }
        else {
            *this = b;
            int diff = b.degree() - a.degree();
            for (int i = 0; i <= a.degree(); i++) coef[i + diff] += a.coef[i];
        }
    }
};
 //한글이 깨져서 영어로 변경