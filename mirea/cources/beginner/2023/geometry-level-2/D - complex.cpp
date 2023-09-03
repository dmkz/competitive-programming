#include <bits/stdc++.h>
template<typename T> int sign(T t) { return t < 0 ? -1 : t > 0 ? +1 : 0; }
using complex = std::complex<long double>;
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        // результат сравнения это разница между аргументами (полярными углами)
        // двух комплексных чисел:
        printf("%d\n", sign(std::arg(complex(x1,y1)) - std::arg(complex(x2,y2))));
    }
    return 0;
}