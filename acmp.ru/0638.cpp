#include <stdio.h>
#include <vector>

int main() {
    int n, duration, daysPerWeek, nBlockedPerWeek, first;
    scanf("%d %d %d %d %d", &n, &duration, &daysPerWeek, &nBlockedPerWeek, &first);
    std::vector<bool> blockedPerWeek(1+daysPerWeek);
    while (nBlockedPerWeek--) {
        int it;
        scanf("%d", &it);
        blockedPerWeek[it] = true;
    }
    std::vector<bool> blocked(1+n);
    for (int i = 1, cur = first; i <= n; ++i) {
        if (blockedPerWeek[cur]) {
            blocked[i] = true;
        }
        ++cur;
        if (cur > daysPerWeek) cur = 1;
    }
    
    int nBlockedPerMonth;
    scanf("%d", &nBlockedPerMonth);
    while (nBlockedPerMonth--) {
        int it;
        scanf("%d", &it);
        blocked[it] = true;
    }
    
    int nBlocked = 0;
    for (int i = 1; i <= duration; ++i) {
        nBlocked += blocked[i];
    }
    int answ = (nBlocked == 0);
    int l = 2, r = duration+1;
    while (r <= n) {
        nBlocked += blocked[r] - blocked[l-1];
        answ += (nBlocked == 0);
        ++r, ++l;
    }
    printf("%d", answ);
    
    return 0;
}