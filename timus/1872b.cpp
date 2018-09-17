/*
    Problem: 1872. Spacious Office
    
    Solution: greedy, sorting, Sparse Table, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <queue>

#define all(x) (x).begin(), (x).end()
#define unique(x) (x).erase(std::unique(all(x)), (x).end())

const int OPEN = 0, CHECK = 1, CLOSE = 2;

const int INF = (int)1e9+1;

struct Event {
    int pos, type, id;
};

bool operator<(const Event& a, const Event& b) {
    if (a.pos < b.pos) return true;
    if (a.pos > b.pos) return false;
    return a.type < b.type || (a.type == b.type && a.id < b.id);
}

struct Pair {
    int value, id;
};

bool operator<(const Pair& a, const Pair& b) {
    return a.value < b.value || (a.value == b.value && a.id < b.id);
}

bool operator>(const Pair& a, const Pair& b) {
    return b < a;
}

int main() {
    int n; scanf("%d", &n);
    std::vector<int> val(n), min(n), max(n), x, to(n);
    for (int i = 0; i < n; ++i) { scanf("%d", &val[i]); }
    for (int i = 0; i < n; ++i) { scanf("%d %d", &min[i], &max[i]); }    
    for (int i = 0; i < n; ++i) {
        x.insert(x.end(), {val[i]-1, val[i], val[i]+1, min[i]-1, min[i], min[i]+1, max[i]-1, max[i], max[i]+1});
    }
    std::sort(all(x)); unique(x);
    const int MAX = (int)x.size()-1;
    
    // Function for output answer:
    std::function<void(int)> output = [&](int ret) {
        if (ret == 0) {
            printf("Let's search for another office.");
        } else if (ret == 2) {
            printf("Ask Shiftman for help.");
        } else {
            assert(ret == 1);
            std::vector<int> temp(n);
            for (int i = 0; i < n; ++i) {
                temp[to[i]] = i+1;
            }
            printf("Perfect!\n");
            for (auto& it : temp) printf("%d ", it);
        }
        std::exit(0);
    };
    // Prepare events array:
    std::vector<Event> events;
    for (int i = 0; i < n; ++i) {
        val[i] = int(std::lower_bound(all(x), val[i])-x.begin());
        min[i] = int(std::lower_bound(all(x), min[i])-x.begin());
        max[i] = int(std::lower_bound(all(x), max[i])-x.begin());
        events.push_back(Event{min[i], OPEN, i});
        events.push_back(Event{max[i],CLOSE, i});
        events.push_back(Event{val[i],CHECK, i});
    }    
    std::sort(all(events));
    // Events handling:
    std::set<Pair> set;
    for (auto& e : events) {
        if (e.type == CHECK) {
            if (set.empty()) output(0);
            to[e.id] = set.begin()->id;
            set.erase(set.begin());
        } else if (e.type == OPEN) {
            set.insert(Pair{max[e.id], e.id});
        } else {
            assert(e.type == CLOSE);
            auto it = set.find(Pair{max[e.id], e.id});
            if (it != set.end()) {
                set.erase(it);
            }
        }
    }
    // Construct Sparse Table:
    const int PMAX = 20;
    std::vector<std::vector<int>> table(PMAX, std::vector<int>(1+MAX, INF));
    for (int i = 0; i < n; ++i) {
        assert(min[to[i]] <= val[i] && val[i] <= max[to[i]]);
        table[0][val[i]] = min[to[i]];
    }
    for (int p = 1; p < PMAX; ++p) {
        for (int i = 0; i + (1 << p) - 1 <= MAX; ++i) {
            table[p][i] = std::min(table[p-1][i], table[p-1][i+(1<<(p-1))]);
        }
    }
    std::vector<int> log2(1+MAX);
    for (int i = 2; i <= MAX; ++i) {
        log2[i] = log2[i/2]+1;
    }
    std::function<int(int,int)> query = [&](int l, int r) {
        if (r < l) return INF;
        int len = r - l + 1;
        int log = log2[len];
        return std::min(table[log][l], table[log][r+1-(1 << log)]);
    };
    // Check on not unique values array:
    int answ = 1;
    {
        std::vector<int> temp;
        for (int i = 0; i < n; ++i) temp.push_back(val[i]);
        std::sort(all(temp)); unique(temp);
        answ += ((int)temp.size() != n);
    }
    // Search correct transposition:
    for (int i = 0; i < n; ++i) {
        int ret = query(val[i]+1, max[to[i]]);
        if (ret <= val[i]) {
            answ = 2;
            break;
        }
    }
    output(answ);
    return 0;
}