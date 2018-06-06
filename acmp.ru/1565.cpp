#include <stdio.h>
#include <vector>
#include <algorithm>

typedef unsigned int Int;

int main() {
    Int n, need;
    scanf("%u %u", &n, &need);
    std::vector<Int> s(1+n), c(1+n), k(1+n, 1);
    for (Int i = 1; i <= n; ++i) {
        scanf("%u %u %u", &s[i], &c[i], &k[i]);
    }
    const Int INF = 2u*1000u*1000u*1000u;
    static Int min[1+100][1+100*100], from[1+100][1+100*100];
    for (Int i = 0; i <= 100u; ++i) for (Int j = 0; j <= 100u*100u; ++j) {
        min[i][j] = INF;
        from[i][j] = -1;
    }
    min[0][0] = 0;
    for (Int t = 1; t <= n; ++t) {
        for (Int curr = 0; curr <= t * 100; ++curr) {
            for (Int score = 0; curr >= score && score <= 100; ++score) {
                if (score % k[t] != 0) {
                    continue;
                }
                Int sum = score == 0 ? min[t-1][curr] : min[t-1][curr-score] + s[t] + score * c[t];
                if (min[t][curr] > sum) {
                    min[t][curr] = sum;
                    from[t][curr] = curr-score;
                }
            }
        }
    }
    int answ = need;
    for (int curr = need; curr <= 100*100; ++curr) {
        if (min[n][answ] > min[n][curr]) {
            answ = curr;
        }
    }
    printf("%u\n", min[n][answ]);
    Int seq[101];
    for (Int i = n; i >= 1; --i) {
        seq[i] = answ - from[i][answ];
        answ = from[i][answ];
    }
    for (Int i = 1; i <= n; ++i) {
        printf("%u ", seq[i]);
    }
    
    return 0;
}