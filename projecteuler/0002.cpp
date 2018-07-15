#include <iostream>
typedef long long ll;
int main() {
    ll sum = 0, prev = 1, curr = 1;
    while (curr <= 4*1000*1000) {
        if (curr % 2 == 0) sum += curr;
        auto next = curr + prev;
        prev = curr;
        curr = next;
    }
    std::cout << sum;
    return 0;
}