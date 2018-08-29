/*
    Problem: 817B. Makes And The Product
    
    Solution: combinatorics, sorting, prefix sums, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#define all(x) (x).begin(), (x).end()
#define size(x) (int)(x).size()
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<ll> vll;

int main() {
    int n; std::cin >> n;
    vi arr(n), item{0}; 
    for (auto& it : arr) { 
        std::cin >> it; 
        item.push_back(it); 
    }
    std::sort(all(item));
    item.erase(std::unique(all(item)),item.end());
    for (auto& it : arr) {
        it = int(std::lower_bound(all(item), it) - item.begin());
    }
    std::map<int,int> pref, suff;
    for (int i = 1; i < size(arr); ++i) {
        suff[arr[i]]++;
    }
    pref[arr[0]]++;
    ll answ = 0, min = (ll)1e18L;
    for (int i = 1; i+1 < size(arr); ++i) {
        suff[arr[i]]--;
        if (suff[arr[i]] == 0) {
            suff.erase(arr[i]);
        }
        ll curr = pref.begin()->first * 1LL * arr[i] * suff.begin()->first;
        if (curr < min) {
            min = curr;
            answ = pref.begin()->second * 1LL * suff.begin()->second;
        } else if (curr == min) {
            answ += pref.begin()->second * 1LL * suff.begin()->second;
        }
        pref[arr[i]]++;
    }
    std::cout << answ;
    return 0;
}