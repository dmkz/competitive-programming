#include <iostream>
int main() {
    int k, a, b;
    std::cin >> k >> a >> b;
    std::cout << ((a+b) == 0 ? 1 : k+1);
    return 0;
}