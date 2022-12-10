#include <bits/stdc++.h>

bool isIncludes(int L1, int R1, int L2, int R2) {
    return (L1 <= L2 && R2 <= R1) || (L2 <= L1 && R1 <= R2);
}

bool isOverlaps(int L1, int R1, int L2, int R2) {
    return !(R1 < L2 || R2 < L1);
}

int main() {
    std::string s;
    int answer1{},answer2{};
    while(std::cin >> s) {
        int a,b,c,d;
        sscanf(s.c_str(), "%d-%d,%d-%d",&a,&b,&c,&d);
        answer1 += isIncludes(a,b,c,d);
        answer2 += isOverlaps(a,b,c,d);
    }
    std::cout << answer1 << std::endl;
    std::cout << answer2 << std::endl;
}