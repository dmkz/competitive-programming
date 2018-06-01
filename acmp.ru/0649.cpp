#include <stdio.h>
#include <string>
#include <iostream>

int main() {
    int n, k; 
    scanf("%d %d", &n, &k);
    static char s[1000000+1];
    scanf("%1000000s", s);
    static int count[256];
    int left = 0, right = 0;
    long long answ = 0;
    while (right < n) {
        const char cur = s[right];
        count[cur]++;
        while (count[cur] > k) {
            count[s[left]]--;
            ++left;
        }
        answ += right-left+1;
        ++right;
    }
    std::cout << answ;
    return 0;
}