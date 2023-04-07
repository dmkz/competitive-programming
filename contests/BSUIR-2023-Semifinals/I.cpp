#include <bits/stdc++.h>
int main() {
    int t; std::cin >> t;
    while (t --> 0) {
        int n, m; std::cin >> n >> m;
        std::cout << (n % 4 == 0 && m % 4 == 0? "Yes\n" : "No\n");
    }
}
