/*
    Problem: 34C. Page Numbers
    
    Solution: strings, implementation, O(n+MAX)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <string>
int main() {
    std::vector<bool> used(1+1000, false);
    for (int v; scanf("%d,",&v) == 1; used[v] = true);
    char buf[20]; std::string answ;
    for (int l = 1; l <= 1000; ++l) {
        if (!used[l]) continue;
        int r = l;
        while (r+1 <= 1000 && used[r+1]) ++r;
        if (r == l) {
            sprintf(buf, "%d,", l);
        } else {
            sprintf(buf, "%d-%d,", l, r);
        }
        answ += buf;
        l = r;
    }
    answ.pop_back();
    printf("%s", answ.c_str());
    return 0;
}