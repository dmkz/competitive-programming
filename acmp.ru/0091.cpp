#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

int main() {
    int n; scanf("%d", &n); --n;
    std::vector<int> a{2, 3, 4, 7, 13, 15}, b{1, 5, 6, 8, 9, 10};
    a.reserve(n+1); b.reserve(n+1);
    int top = 4;
    for (int i = (int)a.size()-1; i <= n; ++i) {
        a.push_back(b[i] + b[i-2]);
        b.push_back(b[i]+1);
        while (b.back() == a[top]) {
            b.back()++;
            top++;
        }
    }
    printf("%d\n%d\n", a[n], b[n]);
    return 0;
}