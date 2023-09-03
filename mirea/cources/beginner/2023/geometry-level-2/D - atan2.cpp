#include <bits/stdc++.h>
template<typename T> int sign(T t) { return t < 0 ? -1 : t > 0 ? +1 : 0; }
using ld = long double;
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        printf("%d\n", sign(std::atan2(ld(y1), ld(x1)) - std::atan2(ld(y2), ld(x2))));
    }
    return 0;
}