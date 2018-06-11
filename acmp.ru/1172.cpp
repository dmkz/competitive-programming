#include <stdio.h>

int pow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res *= a;
        }
        a *= a;
        n /= 2;
    }
    return res;
}

int euler(const int n) {
    int answer = 1, m = n;
    for (int i = 2; i * i <= n; ++i) {
        int count = 0;
        while (m % i == 0) {
            m /= i;
            ++count;
        }
        if (count > 0) {
            answer *= pow(i, count) - pow(i, count-1);
        }
    }
    if (m > 1) {
        answer *= (m-1);
    }
    return answer;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", euler(n));
    return 0;
}