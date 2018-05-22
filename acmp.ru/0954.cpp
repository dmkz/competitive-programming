#include <iostream>
#include <vector>

int main() {
    int height; 
    std::cin >> height;
    std::vector<int> count(height+1, 0);
    count[0] = 1;
    const int mod = 1000*1000;
    for (int i = 1; i <= height; ++i) {
        if (i-10 >= 0) {
            count[i] += count[i-10];
        }
        if (i-11 >= 0) {
            count[i] += count[i-11];
        }
        if (i-12 >= 0) {
            count[i] += count[i-12];
        }
        count[i] %= mod;
    }
    printf("%d\n", 2*count[height] % mod);  
    
    return 0;
}