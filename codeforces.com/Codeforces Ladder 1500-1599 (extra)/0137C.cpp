/*
    Problem: 137C. History
    
    Solution: sorting, events, std::set, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <cassert>
#include <vector>
#include <algorithm>
#include <set>

const int OPEN = 0, CLOSE = 1;

struct Event {
    int time, type, id;
};

bool operator<(const Event& a, const Event& b) {
    assert(a.time != b.time);
    return a.time < b.time;
}

int main() {
    int n; scanf("%d", &n);
    std::vector<Event> events;
    std::vector<int> timeOpen(n);
    for (int i = 0; i < n; ++i) {
        int l, r; scanf("%d %d", &l, &r);
        events.push_back(Event{l, OPEN, i});
        events.push_back(Event{r,CLOSE, i});
        timeOpen[i] = l;
    }
    std::sort(events.begin(), events.end());
    std::set<int> opened;
    int answ = 0;
    for (auto& e : events) {
        if (e.type == CLOSE) {
            opened.erase(timeOpen[e.id]);
            answ += !opened.empty() && *opened.begin() < timeOpen[e.id];
        } else {
            opened.insert(timeOpen[e.id]);
        }
    }
    printf("%d\n", answ);
    return 0;
}