/*
    Problem: 1028. Stars
    
    Solution: Fenwick, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

struct Fenwick {
    
    std::vector<int> data;

    Fenwick(int s) : data(s, 0) { }
    
    void inc(int p, int value) {
        for (int i = p; i < (int)data.size(); i |= i+1) {
            data[i] += value;
        }
    }
    
    int get(int r) const {
        int answ = 0;
        for (int i = r; i >= 0; i = (i & (i+1))-1) {
            answ += data[i];
        }
        return answ;
    }
};

int main() {
    const int max = 32000;
    Fenwick fw(1+max);
    int n; scanf("%d", &n);
    std::vector<int> count(n,0);
    while (n--) {
        int x, y;
        scanf("%d %d", &x, &y);
        count[fw.get(x)]++;
        fw.inc(x, 1);
    }
    for (auto& it : count) printf("%d\n", it);
    return 0;
}