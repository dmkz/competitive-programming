#include <iostream>
#include <vector>

int main() {
    int number, need;
    std::cin >> number >> need;
    std::vector<int> answer;
    int a = need % 10, b = need / 10;
    // number = a + b * base + base^2*(...)
    for (int base = 2; a + b * base + base * base <= number; ++base) {
        if ((number - a - b * base) % (base*base) == 0 && a < base && b < base) {
            answer.push_back(base);
        }
    }
    int base = (number - a) / b;
    if (number == a + b * base && a < base && b < base) {
        answer.push_back(base);
    }
    if (answer.empty()) {
        answer.push_back(-1);
    }
    for (auto& it : answer) {
        printf("%d ", it);
    }
    return 0;
}