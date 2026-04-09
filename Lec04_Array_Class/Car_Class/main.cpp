#include "SportsCar.h"

int main() {
    SportsCar s1;

    // Test 1: Turbo OFF
    s1.setTurbo(false);
    s1.speedUp();
    s1.display();

    // Test 2: Turbo ON
    s1.setTurbo(true);
    s1.speedUp();
    s1.display();

    return 0;
}