/*
    Problem: 540B. School Marks
    
    Solution: greedy, math, constructive, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

typedef std::vector<int> vi;

vi solve(const int n, vi arr, const int max, const int med, const int sum) {
    std::sort(arr.begin(), arr.end());
    int need = n - (int)arr.size();
    while ((int)arr.size() < n) {
        arr.insert(arr.begin(), 1);
    }
    int n1 = need, n2 = 0;
    while (need > 0 && arr[n / 2] < med) {
        arr[0] = med;
        n1--;
        n2++;
        for (int i = 0; i + 1 < n; ++i) {
            if (arr[i] > arr[i+1]) {
                std::swap(arr[i], arr[i+1]);
            } else {
                break;
            }
        }
        --need;
    }
    vi answ(n1, 1);
    while (n2--) {
        answ.push_back(med);
    }
    if (arr[n / 2] < med || std::accumulate(arr.begin(), arr.end(), 0) > sum) {
        answ.assign(1, -1);
    }
    return answ;
}

int main() {
    int n, nGiven, max, sum, med;
    while (std::cin >> n >> nGiven >> max >> sum >> med) {
        vi given(nGiven);
        for (auto& it : given) {
            std::cin >> it;
        }
        auto answ = solve(n, given, max, med, sum);
        for (auto it : answ) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}