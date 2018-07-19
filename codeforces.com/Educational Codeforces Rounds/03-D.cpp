/*
    Problem: 609D. Gadgets for dollars and pounds
    
    Solution: sorting, binary search, two pointers, O(n log(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

struct Gadget {
    int id, cost;
};

int main () {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    // Input:
    int nDays, nGadgets, nNeed, totalSum;
    std::cin >> nDays >> nGadgets >> nNeed >> totalSum;
    
    std::vector<int> cost1(1+nDays); for (int day = 1; day <= nDays; ++day) std::cin >> cost1[day];
    std::vector<int> cost2(1+nDays); for (int day = 1; day <= nDays; ++day) std::cin >> cost2[day];
    
    std::vector<Gadget> gadgets1, gadgets2;
    for (int i = 1; i <= nGadgets; ++i) {
        int type, cost; std::cin >> type >> cost;
        if (type == 1) {
            gadgets1.push_back(Gadget{i, cost});
        } else {
            assert(type == 2);
            gadgets2.push_back(Gadget{i, cost});
        }
    }
    // Sorting gadgets by cost:
    std::sort(gadgets1.begin(), gadgets1.end(), [](const Gadget& a, const Gadget& b){
        return a.cost < b.cost || (a.cost == b.cost && a.id < b.id);
    });
    
    std::sort(gadgets2.begin(), gadgets2.end(), [](const Gadget& a, const Gadget& b){
        return a.cost < b.cost || (a.cost == b.cost && a.id < b.id);
    });
    
    std::vector<std::pair<int, int>> answer;
    
    // Solve problem for fixed day:
    std::function<bool(int, bool)> is_possible = [&](const int lastDay, bool need_report) {
        assert(lastDay <= nDays);
        int minDay1 = int(std::min_element(cost1.begin()+1, cost1.begin()+lastDay+1)-cost1.begin());
        int minDay2 = int(std::min_element(cost2.begin()+1, cost2.begin()+lastDay+1)-cost2.begin());
        int minCost1 = cost1[minDay1];
        int minCost2 = cost2[minDay2];
        int n2 = std::min(nNeed, (int)gadgets2.size());
        int n1 = nNeed - n2;
        long long sum1 = 0; for (int i = 0; i < n1; ++i) sum1 += gadgets1[i].cost;
        long long sum2 = 0; for (int i = 0; i < n2; ++i) sum2 += gadgets2[i].cost;
        while (true) {
            long long sum = sum1 * minCost1 + sum2 * minCost2;
            if (sum <= totalSum) {
                if (need_report) {
                    assert(answer.empty());
                    for (int i = 0; i < n1; ++i) {
                        answer.push_back({gadgets1[i].id, minDay1});
                    }
                    for (int i = 0; i < n2; ++i) {
                        answer.push_back({gadgets2[i].id, minDay2});
                    }
                }
                return true;
            }
            n1++;
            n2--;
            if (n2 < 0 || n1 > (int)gadgets1.size()) {
                break;
            }
            sum2 -= gadgets2[n2].cost;
            sum1 += gadgets1[n1-1].cost;
        }
        return false;
    };
    
    // Binary search by minimal day:
    int low = 0, high = nDays+1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (is_possible(mid, false)) {
            high = mid;
        } else {
            low = mid;
        }
    }
    
    // Output answer:
    if (high == nDays+1) {
        std::cout << -1 << std::endl;
        return 0;
    }
    std::cout << high << std::endl;
    is_possible(high, true);
    for (auto& it : answer) {
        std::cout << it.first << " " << it.second << "\n";
    }
    return 0;
}