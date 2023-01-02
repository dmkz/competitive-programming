#include <bits/stdc++.h>
#include "../Brute.hpp"
void testDistinct() {
    std::cout << std::string(40,'-') << std::endl;
    const int len = 3, min = 1, max = 4;
    std::cout << "test distinct: arrays with len " << len
              << ", min = " << min << ", max = " << max << ":\n";
    BruteDistinct<int> a(len, min, max);
    int total = 0;
    do {
        for (auto &it : a) {
            std::cout << ' ' << it;
        }
        std::cout << std::endl;
        total++;
    } while(a.next());
    std::cout << "total: " << total << " distinct arrays" << std::endl;
    int n = max - min + 1;
    int64_t expected = 1;
    for (int i = 1; i <= len; i++) {
        expected *= (n - i + 1);
    }
    std::cout << "expected: " << expected << std::endl;
}
void testAllVectors() {
    std::cout << std::string(40,'-') << std::endl;
    const int len = 3, min = 0, max = 1;
    std::cout << "test all vectors: arrays with len " << len
              << ", min = " << min << ", max = " << max << ":\n";
    BruteVector<int> a(len, min, max);
    int total = 0;
    do {
        for (auto &it : a) {
            std::cout << ' ' << it;
        }
        std::cout << std::endl;
        total++;
    } while (a.next());
    std::cout << "total: " << total << " arrays" << std::endl;
    std::cout << "expected: " << std::pow(max-min+1,len) << std::endl;
}
int main() {
    testDistinct();
    testAllVectors();
}