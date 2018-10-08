/*
    Problem: 149C. Division into Teams
    
    Solution: constructive, sorting, greedy, O(n log(n))
    
    Auhtor: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

struct Pair {
    int value, id;
};
bool operator<(const Pair& a, const Pair& b) {
    return a.value < b.value || (a.value == b.value && a.id < b.id);
}
int main() {
    int n; scanf("%d", &n);
    std::vector<Pair> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i].value);
        arr[i].id = i+1;
    }
    std::sort(arr.begin(), arr.end());
    std::vector<int> fi, se;
    for (int i = 0; i < n; ++i) {
        if (i & 1) {
            se.push_back(arr[i].id);
        } else {
            fi.push_back(arr[i].id);
        }
    }
    printf("%d\n", (int)fi.size());
    for (auto& it : fi) printf("%d ", it);
    printf("\n");
    printf("%d\n", (int)se.size());
    for (auto& it : se) printf("%d ", it);
    printf("\n");
    return 0;
}