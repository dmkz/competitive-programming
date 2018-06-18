#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cassert>

int solve(int n) {
    // Генерируем числа Фибоначчи:
    std::vector<int> fib{1,1,2};
    for (int i = 3; fib.back() < n; ++i) {
        fib.push_back(fib[i-1]+fib[i-2]);
    }
    // Находим номер нужного:
    return int(std::lower_bound(fib.begin(), fib.end(), n) - fib.begin());
}

int main() {
    int n;
    scanf("%d", &n);
    
    if (n == 0 || n == 1) {
        printf("0");
        return 0;
    }
    
    printf("%d\n", solve(n));
    
    return 0;
}