#include <stdio.h>
#include <vector>
#include <algorithm>

int main() {
    int n; scanf("%d", &n);
    std::vector<int> coin(n);
    for (auto& it : coin) {
        scanf("%d", &it);
    }
    std::vector<char> possible(1+1000, false);
    possible[0] = true;
    for (int i = 1; i <= 1000; ++i) {
        for (auto c : coin) {
            if (i-c >= 0 && possible[i-c]) {
                possible[i] = true;
            }
        }
    }
    int nQ;
    scanf("%d", &nQ);
    while (nQ--) {
        int sum; scanf("%d", &sum);
        printf("%d ", (int)possible[sum]);
    }
    return 0;
}