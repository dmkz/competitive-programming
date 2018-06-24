#include <stdio.h>

int main() {
    int n, n_ab, n_bc, n_ac;
    scanf("%d %d %d %d", &n, &n_ab, &n_bc, &n_ac);
    
    for (int k_a = 0; k_a <= n; ++k_a) {
        for (int k_b = 0; k_b <= n-k_a; ++k_b) {
            int k_ab = n_ab - k_a - k_b;
            int k_c = k_ab + n_ac + n_bc - n;
            int k_ac = n_ac - k_a - k_c;
            int k_bc = n_bc - k_b - k_c;
            if (k_a >= 0 && k_ab >= 0 && k_b >= 0 && k_bc >= 0 && k_c >= 0 && k_ac >= 0) {
                printf("YES\n");
                printf("%d %d %d %d %d %d", k_a, k_ab, k_b, k_bc, k_c, k_ac);
                return 0;
            }
        }
    }
    printf("NO");
    return 0;
}