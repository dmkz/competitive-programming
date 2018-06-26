#include <stdio.h>

int solve(int len) {
    static int prepared = false;
    static int count[2][1+30]; // count[last][len]
    if (!prepared) {
        prepared = true;
        count[0][1] = count[1][1] = 1;
        count[0][2] = count[1][2] = 2;
        count[0][3] = count[1][3] = 3;
        for (int len = 4; len <= 30; ++len) {
            for (int last = 0; last < 2; ++last) {
                count[last][len] = count[0][len-1]+count[1][len-1]-count[1-last][len-3];
            }
        }
    }
    return count[0][len] + count[1][len];
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", solve(n));
    return 0;
}