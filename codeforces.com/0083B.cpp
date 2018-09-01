/*
    Problem: 83B. Doctor
    
    Solution: sorting, set, implementation, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>
#include <deque>

typedef long long ll;

struct Pair {
    int pos, value;
};

bool operator<(const Pair& a, const Pair& b) {
    return a.pos < b.pos;
}

int main() {
    int n; ll k;
    scanf("%d %lld", &n, &k);
    
    std::set<Pair> set;
    std::vector<Pair> arr;
    for (int i = 1; i <= n; ++i) {
        int v; scanf("%d", &v);
        arr.push_back(Pair{i, v});
        set.insert(Pair{i,v});
    }
    std::sort(arr.begin(), arr.end(), [](const Pair& a, const Pair& b) {
        return a.value < b.value || (a.value == b.value && a.pos < b.pos);
    });
    ll curr_sum = 0, curr_it = 0;
    std::deque<int> answ;
    for (int i = 0; i < n; ++i) {
        if (arr[i].value == curr_it) {
            set.erase(arr[i]);
            continue;
        }
        if (curr_sum == k) continue;
        assert(arr[i].value > curr_it);
        ll min = std::min(arr[i].value - curr_it, (k - curr_sum) / (n - i));
        if (min == 0) {
            while (curr_sum < k) {
                if (set.begin()->value > curr_it+1) {
                    answ.push_back(set.begin()->pos);
                }
                set.erase(set.begin());
                ++curr_sum;
            }
            while (!set.empty()) {
                assert(set.rbegin()->value > curr_it);
                answ.push_front(set.rbegin()->pos);
                set.erase(*set.rbegin());
            }
        } else {
            curr_it += min;
            curr_sum += 1LL * min * (n-i);
        }
        --i;
    }
    if (curr_sum < k) {
        printf("-1"); return 0;
    }
    for (auto& it : set) {
        answ.push_back(it.pos);
    }
    for (auto& it : answ) {
        printf("%d ", it);
    }
    return 0;
}