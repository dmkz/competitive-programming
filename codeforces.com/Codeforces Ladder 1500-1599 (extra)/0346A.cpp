/*
    Problem: 346A. Alice and Bob
    
    Solution: number theory, math, gcd, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int n; scanf("%d", &n);
    std::vector<int> arr(n);
    for (auto& it : arr) {
        scanf("%d", &it);
    }
    int d = arr[0];
    for (int i = 1; i < n; ++i) {
        d = gcd(d, arr[i]);
    }
    for (auto& it : arr) it /= d;
    int max = *std::max_element(arr.begin(), arr.end());
    printf((max - n) % 2 == 1 ? "Alice" : "Bob");
    return 0;
}