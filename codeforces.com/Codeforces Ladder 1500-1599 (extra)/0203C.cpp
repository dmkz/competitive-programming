/*
    Problem: 203C. Photographer
    
    Solution: sorting, greedy, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

struct Pair {
    ll value; int id;
};

bool operator<(const Pair& a, const Pair& b) {
    return a.value < b.value || (a.value == b.value && a.id < b.id);
}

int main() {
    int n, limit, s1, s2;
    scanf("%d %d %d %d", &n, &limit, &s1, &s2);
    std::vector<Pair> arr;
    for (int i = 0; i < n; ++i) {
        int c1, c2; scanf("%d %d", &c1, &c2);
        arr.push_back(Pair{ll(c1) * s1 + ll(c2) * s2, i+1});
    }
    std::sort(arr.begin(), arr.end());
    int p = 0; ll sum = 0;
    while (p < n && sum + arr[p].value <= limit) {
        sum += arr[p].value;
        p++;
    }
    printf("%d\n", p);
    for (int i = 0; i < p; ++i) {
        printf("%d ", arr[i].id);
    }
    return 0;
}