#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) {
        std::cin >> it;
    }
    
    std::sort(arr.begin(), arr.end());
    arr.erase(std::unique(arr.begin(), arr.end()), arr.end());
    n = (int)arr.size();
    
    // Множество элементов не может иметь размер больший, чем 2:
    // a < b < c < d
    // dist(a,b) = 2^k, dist(b,c) = 2^t, dist(a,c) = dist(a,b)+dist(b,c) = 2^k+2^t = 2^m <=> k == t
    // dist(a,d) = 2^n = 3*dist(a,b) = 3*2^k - impossible
    
    // check size = 3:
    for (int i = 1; i+1 < n; ++i) {
        auto up = arr.begin()+i, down = arr.begin()+i;
        for (int pow = 0; pow <= 30; ++pow) {
            if (arr[i]-arr[0] < (1 << pow) || arr[n-1]-arr[i] < (1 << pow)) {
                break;
            }
            up   = std::lower_bound(         up, arr.end(), arr[i]+(1 << pow));
            down = std::lower_bound(arr.begin(),      down, arr[i]-(1 << pow));
            assert(up != arr.end());
            if (*up-arr[i] == (1 << pow) && arr[i]-*down == (1 << pow)) {
                std::cout << "3\n" << *down << ' ' << arr[i] << ' ' << *up;
                return 0;
            }
        }
    }
    // check size = 2:
    for (int i = 0; i+1 < n; ++i) {
        auto up = arr.begin()+i;
        for (int pow = 0; pow <= 30; ++pow) {
            if (arr[n-1] - arr[i] < (1 << pow)) {
                break;
            }
            up = std::lower_bound(up, arr.end(), arr[i]+(1 << pow));
            assert(up != arr.end());
            if (*up - arr[i] == (1 << pow)) {
                std::cout << "2\n" << arr[i] << ' ' << *up;
                return 0;
            }
        }
    }
    // size = 1:
    std::cout << "1\n" << arr.front();
    
    return 0;
}