#include <iostream>

typedef long long Int;

int main() {
    Int n, a;
    std::cin >> n >> a;
    while (n > 1) {
        if (a % 2 == 1) {
            n = (n+1)/2;
            a = (a+1)/2;
            printf("0 ");
        } else {
            n /= 2;
            a /= 2;
            printf("1 ");
        }
    }
    return 0;
}