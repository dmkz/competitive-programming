#include <stdio.h>
#include <tuple>

int main() {
    int n; scanf("%d", &n);
    double p = 1, q = 0;
    while (n--) {
        double cur; 
        scanf("%lf", &cur);
        std::tie(p, q) = std::make_tuple(
            p * cur + q * (1-cur),
            p * (1-cur) + q * cur
        );
    }
    printf("%0.6f", p);
    return 0;
}