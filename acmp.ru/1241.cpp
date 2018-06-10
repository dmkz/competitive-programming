#include <stdio.h>
#include <cmath>
#include <cassert>

bool solve(int x) {
    int root = std::sqrt(x);
    return root * root == x;
}

int main() {
    int x; scanf("%d", &x);
    printf(solve(x) ? "YES" : "NO");
    return 0;
}