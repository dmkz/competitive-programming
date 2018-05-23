#include <iostream>
#include <functional>
#include <climits>

int main() {
    int n; std::cin >> n;
    
    static int arr[100];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    
    static int min[100][100];
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            min[i][j] = -1;
        }
    }
    
    std::function<int(int, int)> get = [&](const int left, const int right) {
        if (right <= left+1) {
            return 0;
        }
        if (min[left][right] == -1) {
            int value = INT_MAX;
            for (int p = left+1; p < right; ++p) {
                value = std::min(value, get(left, p) + get(p, right) + (arr[left] + arr[right]) * arr[p]);
            }
            min[left][right] = value;
        }
        return min[left][right];
    };
    std::cout << get(0, n-1);
    return 0;
}