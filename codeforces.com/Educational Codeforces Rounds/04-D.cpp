/*
    Problem: 612D. The Union of k-Segments
    
    Solution: sorting, events, O(n log(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

const int CLOSED = 1;
const int OPENED = 0;

struct Event {
    int pos, type;
};

const int UNDEFINED = -(int)1e9-1;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, k; std::cin >> n >> k;
    std::vector<Event> events;
    for (int i = 0; i < n; ++i) {
        int a, b; std::cin >> a >> b;
        events.push_back(Event{a, OPENED});
        events.push_back(Event{b, CLOSED});
    }
    std::stable_sort(events.begin(), events.end(), [](const Event& a, const Event& b){
        return a.pos < b.pos || (a.pos == b.pos && a.type < b.type);
    });
    
    std::vector<std::pair<int, int>> answer;
    int balance = 0, left = UNDEFINED, right = UNDEFINED;
    for (auto e : events) {
        int next = balance + (e.type == OPENED ? 1 : -1);
        if (balance == k-1 && next == k) {
            left = e.pos;
        } else if (balance == k && next == k-1) {
            right = e.pos;
            assert(left != UNDEFINED);
            answer.push_back({left, right});
            left = right = UNDEFINED;
        }
        balance = next;
    }
    std::cout << answer.size() << std::endl;
    for (auto it : answer) {
        std::cout << it.first << " " << it.second << "\n";
    }
    
    return 0;
}