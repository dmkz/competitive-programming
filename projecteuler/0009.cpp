#include <iostream>
#include <string>
#include <algorithm>

int main() {
    for (int a = 1; a <= 1000; ++a) {
        for (int b = a; b <= 1000-a; ++b) {
            int c = 1000-a-b;
            if (c <= 0) continue;
            if (a * a + b * b == c * c) {
                std::cout << a*b*c;
                return 0;
            }
        }
    }
    throw 1;
}