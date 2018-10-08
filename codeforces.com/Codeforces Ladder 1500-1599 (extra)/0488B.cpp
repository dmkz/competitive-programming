/*
    Problem: 488B. Candy Boxes
    
    Solution: math, number theory, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    int n; scanf("%d", &n);
    std::vector<int> a(n);
    for (auto& it : a) scanf("%d", &it);
    if (n == 0) {
        int x = 5;
        printf("YES\n%d\n%d\n%d\n%d\n", x, 2*x-1, 2*x+1, 3*x);
        return 0;
    }
    if (n == 1) {
        int x = a[0];
        printf("YES\n%d\n%d\n%d\n", 2*x-1, 2*x+1, 3*x);
        return 0;
    }
    std::sort(a.begin(), a.end());
    if (n == 2) {
        if (3 * a[0] > a[1]) {
            printf("YES\n%d\n%d\n", 3 * a[0], 3 * a[0] - (a[1]-a[0]));
            return 0;
        }
        if (3 * a[0] == a[1]) {
            printf("YES\n%d\n%d\n", 2 * a[0] - 1, 2 * a[0] + 1);
            return 0;
        }
        printf("NO\n"); return 0;
    }
    
    std::function<bool(int)> try_to_add = [&](int item) {
        std::vector<int> temp = a;
        temp.push_back(item);
        std::sort(temp.begin(), temp.end());
        int x1 = 4 * (temp[3] - temp[0]);
        int x2 = 2 * (temp[1] + temp[2]);
        int x3 = (temp[0]+temp[1]+temp[2]+temp[3]);
        return x1 == x2 && x1 == x3;
    };
    
    std::function<void(int)> print = [&](int item) {
        printf("YES\n%d\n", item);
    };
    
    if (n == 3) {
        if (a[2] % 3 == 0) {
            if (try_to_add(a[2] / 3)) {
                print(a[2] / 3);
                return 0;
            }
        }
        if (try_to_add(3*a[0])) {
            print(3*a[0]);
            return 0;
        }
        if (try_to_add(a[2]-(a[1]-a[0]))) {
            print(a[2]-(a[1]-a[0]));
            return 0;
        }
        printf("NO\n");
        return 0;
    }
    if (n == 4) {
        int x1 = 4 * (a[3] - a[0]);
        int x2 = 2*(a[1]+a[2]);
        int x3 = (a[0]+a[1]+a[2]+a[3]);
        printf(x1 == x2 && x1 == x3 ? "YES\n" : "NO\n");
    }
    return 0;
}