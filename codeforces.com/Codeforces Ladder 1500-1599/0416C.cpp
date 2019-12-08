/*
    Problem: 416C. Booking System
    Solution: dynamic programming, greedy, implementation
*/
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int nGroups;
    std::cin >> nGroups;
    
    std::vector<int> count(nGroups), price(nGroups);
    for (int i = 0; i < nGroups; ++i) {
        std::cin >> count[i] >> price[i];
    }
    int nPlaces; std::cin >> nPlaces;
    std::vector<int> size(nPlaces);
    for (int i = 0; i < nPlaces; ++i) {
        std::cin >> size[i];
    }
    // Минимальное из неиспользованных:
    std::vector<int> placeFor(nGroups,-1), groupFor(nPlaces,-1), invalid(nPlaces, 0);
    
    while (true) {
        int min = -1;
        for (int p = 0; p < nPlaces; ++p) {
            if (groupFor[p] != -1 || invalid[p]) continue;
            if (min == -1 || size[min] > size[p]) {
                min = p;
            }
        }
        if (min == -1) break;
        int place = min;
        min = -1;
        for (int g = 0; g < nGroups; ++g) {
            if (placeFor[g] != -1) continue;
            if (count[g] > size[place]) continue;
            if (min == -1 || (price[min] < price[g] || (price[min] == price[g] && size[min] < size[g]))) {
                min = g;
            }
        }
        if (min == -1) {
            invalid[place] = 1;
            continue;
        }
        int group = min;
        placeFor[group] = place;
        groupFor[place] = group;
    }
    int sum = 0, cnt = 0;
    for (int p = 0; p < nPlaces; ++p) {
        int g = groupFor[p];
        if (g == -1) continue;
        sum += price[g];
        cnt++;
    }
    std::cout << cnt << ' ' << sum << '\n';
    for (int g = 0; g < nGroups; ++g) {
        int p = placeFor[g];
        if (p == -1) continue;
        std::cout << g+1 << ' ' << p+1 << '\n';
    }
    return 0;
}