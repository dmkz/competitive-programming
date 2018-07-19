/*
    Problem: 652C. Foe Pairs
    
    Solution: sorting, unique, two pointers, O(n log(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

typedef long long ll;

int main() {
    int n, m; 
    scanf("%d %d", &n, &m);
    
    std::vector<int> a(n), pos(n);
    for (int i = 0; i < n; ++i) {
        int value;
        scanf("%d", &value);
        --value;
        a.at(i) = value;
        pos.at(value) = i;
    }
    
    std::vector<std::vector<int>> left(n), right(n);
    
    std::vector<std::pair<int,int>> pairs;
    
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a, --b;
        a = pos.at(a);
        b = pos.at(b);
        if (a > b) {
            std::swap(a,b);
        }
        pairs.push_back(std::make_pair(a, b));
    }
    // Sorting and erasing repeats:
    std::sort(pairs.begin(), pairs.end());
    pairs.erase(std::unique(pairs.begin(), pairs.end()), pairs.end());
    
    // Creating events:
    m = pairs.size();
    for (int i = 0; i < m; ++i) {
        int a = pairs[i].first;
        int b = pairs[i].second;
        left.at(a).push_back(i);
        right.at(b).push_back(i);
    }
    
    std::vector<bool> include(m); // Is there a pair?
    
    // The method of two pointers:
    int l = 0, r = 0, count = 0;
    ll answ = 0;
    while (l < n) {
        // Move r
        while (r < n && count == 0) {
            for (auto id : right[r]) {
                assert(!include[id]);
                if (pairs[id].first >= l) { // add pair
                    include[id] = true;
                    ++count;
                }
            }
            
            if (count == 0) {
                ++r;
            } else {
                break;
            }
        }
        
        // Increase answer:
        answ += r-l;
        
        // Move l:
        for (auto id : left[l]) {
            if (include[id]) { // erase pair
                include[id] = false;
                --count;
            }
        }
        
        ++l;
    }
    std::cout << answ;
    return 0;
}