/*
    Problem: 702C. Cellular Network
    
    Solution: merge, binary search, O(n * log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long long ll;

const int OPEN = 0, CHECK = 1, CLOSE = 2;

struct Event {
    ll pos; int type;
};

inline bool operator<(const Event& a, const Event& b) {
    return a.pos < b.pos || (a.pos == b.pos && a.type < b.type);
}

bool solve(const std::vector<ll>& a, const std::vector<ll>& b, ll r) {
    std::vector<Event> events, check, open, close;
    for (auto& it : a) {
        check.push_back(Event{it, CHECK});
    }
    for (auto& it : b) {
        open.push_back(Event{it-r, OPEN});
        close.push_back(Event{it+r, CLOSE});
    }
    {
        std::vector<Event> temp;
        std::merge(check.begin(), check.end(), open.begin(), open.end(), std::back_inserter(temp));
        std::merge(temp.begin(), temp.end(), close.begin(), close.end(), std::back_inserter(events));
    }
    
    int balance = 0;
    for (auto& e : events) {
        if (e.type == OPEN) {
            balance++;
        } else if (e.type == CHECK) {
            if (balance == 0) {
                return false;
            }
        } else {
            assert(e.type == CLOSE);
            balance--;
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, m; std::cin >> n >> m;
    std::vector<ll> a(n), b(m);
    for (auto& it : a) std::cin >> it;
    for (auto& it : b) std::cin >> it;
    
    ll low = -1, high = 2e9+1;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (solve(a, b, mid)) {
            high = mid;
        } else {
            low = mid;
        }
    }
    std::cout << high;
    
    return 0;
}