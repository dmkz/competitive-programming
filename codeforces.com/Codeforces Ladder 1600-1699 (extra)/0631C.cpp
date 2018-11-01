/*
    Problem: 631C. Report
    
    Solution: deque, sorting, priority queue, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>
#include <queue>

const int ASC = 1, DEC = 2;

struct Query {
    int id, type, count;
};

bool operator<(const Query& a, const Query& b) {
    if (a.count < b.count) return true;
    if (a.count > b.count) return false;
    if (a.id < b.id) return true;
    if (a.id > b.id) return false;
    return a.type < b.type;
}

bool operator>(const Query& a, const Query& b) {
    return b < a;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, m;
    while (std::cin >> n >> m) {
        std::deque<int> deque;
        std::vector<int> answ;
        for (int i = 0, v; i < n; ++i) {
            std::cin >> v;
            deque.push_back(v);
        }
        std::priority_queue<Query> queue;
        int lastQuery = 0;
        for (int i = 0, t, cnt; i < m; ++i) {
            std::cin >> t >> cnt;
            queue.push(Query{i, t, cnt});
        }
        queue.push(Query{m, ASC, 0});
        bool reversed = false, sorted = false;
        while (!queue.empty()) {
            auto curr = queue.top(); queue.pop();
            if (curr.id < lastQuery) continue;
            lastQuery = curr.id;
            while ((int)deque.size() > curr.count) {
                if (reversed) {
                    answ.push_back(deque.front());
                    deque.pop_front();
                } else {
                    answ.push_back(deque.back());
                    deque.pop_back();
                }
            }
            if (!sorted) {
                sorted = true;
                std::sort(deque.begin(), deque.end());
            }
            reversed = (curr.type == DEC);
        }
        std::reverse(answ.begin(), answ.end());
        for (auto& it : answ) { std::cout << it << ' '; }
        std::cout << std::endl;
    }
    return 0;
}