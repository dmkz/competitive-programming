#include <bits/stdc++.h>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, nQueries, nItems;
    std::cin >> n >> nQueries >> nItems;
    
    std::vector<int> items(nItems);
    
    for (auto& it : items) {
        std::cin >> it;
    }
    
    int total = 0;
    while (n--) {
        for (int i = 0; i < nQueries; ++i) {
            int value; std::cin >> value;
            auto it = std::find(items.begin(), items.end(), value);
            total += int(it - items.begin())+1;
            std::rotate(items.begin(), it, it+1);
        }
    }
    
    std::cout << total;
    return 0;
}