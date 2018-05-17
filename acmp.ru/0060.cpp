#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <bits/stdc++.h>

int main() {
    const int MAX_N = 1000000;
    std::vector<bool> is_simple(1+MAX_N, true);
    is_simple[0] = is_simple[1] = false;
    for (int i = 2; i * i <= MAX_N; ++i) {
        if (!is_simple[i]) continue;
        for (int j = i * i; j <= MAX_N; j += i) {
            is_simple[j] = false;
        }
    }
    int need; std::cin >> need;
    int pos = 0, cur = -1;
    int number = 0;
    for (int i = 2; i <= MAX_N; ++i) {
        if (is_simple[i]) {
            number++;
            if (is_simple[number]) {
                cur = i;
                pos++;
                if (pos == need) {
                    break;
                }
            }
        }
    }
    assert(cur != -1);
    std::cout << cur << std::endl;
    return 0;
}