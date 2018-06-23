#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>

struct Record {
    int time, count, id;
};

typedef long long ll;

int main() {
    int n;
    scanf("%d", &n);
    
    std::vector<Record> arr;
    for (int i = 0; i < n; ++i) {
        int t, w;
        scanf("%d %d", &t, &w);
        arr.push_back(Record{t,w,i});
    }
    
    std::sort(arr.begin(), arr.end(), [](const Record& a, const Record& b) {
        return a.count < b.count;
    });
    
    std::vector<ll> answ(n);
    ll t = 0;
    for (auto& r : arr) {
        t = answ[r.id] = std::max(ll(r.time) * r.count, t);
    }
    
    for (auto& it : answ) {
        printf("%s\n", std::to_string(it).c_str());
    }
    
    return 0;
}