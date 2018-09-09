/*
    Problem: 762B. USB vs. PS/2
    
    Solution: sorting, greedy, O(m * log(m))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

typedef long long ll;

struct Record {
    int cost, type;
};

inline bool operator<(const Record& a, const Record& b) {
    return a.cost < b.cost || (a.cost == b.cost && a.type < b.type);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n0, n1, n01;
    std::cin >> n0 >> n1 >> n01;
    
    std::vector<Record> arr;
    
    int nR; std::cin >> nR;
    while (nR--) {
        int cost; std::string s;
        std::cin >> cost >> s;
        arr.push_back(Record{cost, int(s == "PS/2")});
    }
    
    std::sort(arr.begin(), arr.end());
    
    ll sum = 0, count = 0;
    
    for (auto& r : arr) {
        if (r.type == 0) {
            if (n0 > 0) {
                n0--;
                sum += r.cost;
                count++;
            } else if (n01 > 0) {
                n01--;
                sum += r.cost;
                count++;
            }
        } else {
            if (n1 > 0) {
                n1--;
                sum += r.cost;
                count++;
            } else if (n01 > 0) {
                n01--;
                sum += r.cost;
                count++;
            }
        }
    }
    std::cout << count << ' ' << sum;
    return 0;
}