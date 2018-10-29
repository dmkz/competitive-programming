/*
    Problem: 270B. Multithreading
    
    Solution: greedy, implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

const int INF = (int)1e9;

int main() {
    int n;
    while (std::cin >> n) {
        std::vector<int> arr(n);
        for (auto& it : arr) {
            std::cin >> it;
        }
        int min = INF, answ = 0;
        for (int i = n-1; i >= 0; --i) {
            min = std::min(arr[i], min);
            if (arr[i] > min) {
                answ = i+1;
                break;
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}