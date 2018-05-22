#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <set>

int main() {
    int dimension, nQueries; scanf("%d %d", &dimension, &nQueries);
    
    std::set<int> set;
    for (int q = 0; q < nQueries; ++q) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (a == 0) {
            for (int a = 1; a <= dimension; ++a) {
                set.insert(c + 1024 * (b + a * 1024));
            }
        } else if (b == 0) {
            for (int b = 1; b <= dimension; ++b) {
                set.insert(c + 1024 * (b + a * 1024));
            }
        } else if (c == 0) {
            for (int c = 1; c <= dimension; ++c) {
                set.insert(c + 1024 * (b + a * 1024));
            }
        } else {
            throw 1;
        }
    }
    printf("%d\n", dimension*dimension*dimension - (int)set.size());
    return 0;
}