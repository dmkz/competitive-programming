/*
    Problem: 349A. Cinema Line
    Solution: greedy, implementation
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    
    int n25 = 0, n50 = 0, n100 = 0;
    while (n--) {
        int value; std::cin >> value;
        if (value == 25) {
            n25++;
        } else if (value == 50) {
            if (n25 == 0) {
                printf("NO");
                return 0;
            }
            n25--;
            n50++;
        } else if (value == 100) {
            if (n50 > 0 && n25 > 0) {
                n50--;
                n25--;
                n100++;
            } else if (n25 >= 3) {
                n100++;
                n25 -= 3;
            } else {
                printf("NO");
                return 0;
            }
        }
    }
    printf("YES");
    return 0;
}