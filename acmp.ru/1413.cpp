#include <stdio.h>
#include <vector>

int main() {
    int n; scanf("%d", &n);
    std::vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &a[i], &b[i], &c[i]);
    }
    std::vector<std::pair<int, int>> answ;
    for (int i = 0; i < n; ++i) {
        int min = i;
        for (int j = i+1; j < n; ++j) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        if (min != i) {
            for (int c = 0; c < 3; ++c) {
                answ.push_back({i+1, min+1});
            }
            std::swap(a[min], a[i]);
            std::swap(b[min], b[i]);
            std::swap(c[min], c[i]);
        }
    }
    printf("%d\n", (int)answ.size());
    for (auto& p : answ) {
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}