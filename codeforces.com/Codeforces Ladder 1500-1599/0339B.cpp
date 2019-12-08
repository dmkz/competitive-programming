/*
    Problem: 339B. Xenia and Ringroad
    Solution: implementation
*/
#include <iostream>
#include <vector>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, q; 
    std::cin >> n >> q;
    
    int curr = 0; ll answ = 0;
    while (q--) {
        int next; std::cin >> next; --next;
        answ += (next - curr + n) % n;
        curr = next;
    }
    std::cout << answ;

    return 0;
}