#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cassert>

void rec(int pos, const std::vector<int>& v, int sum, int& answ) {
    if (pos == (int)v.size()) {
        answ = std::min(answ, std::abs(sum));
        return;
    }
    assert(pos < (int)v.size());
    rec(pos+1, v, sum+v[pos], answ);
    rec(pos+1, v, sum-v[pos], answ);
}

int main() {
    int n; scanf("%d", &n);
    std::vector<int> arr(n);
    for (auto& it : arr) {
        scanf("%d", &it);
    }
    int answ = 1e9;
    printf("%d", (rec(1, arr, arr[0], answ), answ));
    return 0;
}