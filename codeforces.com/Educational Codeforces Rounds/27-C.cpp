/*
    Problem: 845C. Two TVs
    
    Solution: sorting, events, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const int OPEN  = 0;
const int CLOSE = 1;

struct Event {
    int pos, type;
};

bool operator<(const Event& a, const Event& b) {
    return a.pos < b.pos || (a.pos == b.pos && a.type < b.type);
}

int main() {
    int n; scanf("%d", &n);
    std::vector<Event> events;
    for (int i = 0; i < n; ++i) {
        int l, r; scanf("%d %d", &l, &r);
        events.push_back(Event{l, OPEN});
        events.push_back(Event{r, CLOSE});
    }
    std::sort(events.begin(), events.end());
    int balance = 0;
    for (auto e : events) {
        if (e.type == OPEN) {
            balance++;
        } else {
            balance--;
        }
        if (balance > 2) {
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}