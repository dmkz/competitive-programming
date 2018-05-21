#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n; 
    std::cin >> n;
    
    std::vector<int> a(1+n); 
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    
    std::vector<int> best(1+n), from(1+n);
    for (int i = 1; i <= n; ++i) {
        best[i] = best[i-1] + a[i];
        from[i] = i-1;
        if (i-2 >= 0 && best[i-2] + a[i] > best[i]) {
            best[i] = a[i] + best[i-2];
            from[i] = i-2;
        }
    }
    
    std::vector<int> answ;
    for (int curr = n; curr >= 1; curr = from[curr]) {
        answ.push_back(curr);
    }
    std::reverse(answ.begin(), answ.end());
    
    std::cout << best[n] << std::endl;
    for (auto& it : answ) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
    return 0;
}