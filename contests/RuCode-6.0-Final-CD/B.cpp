//#pragma GCC optimize("O1")
//#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
#define all(x) std::begin(x), std::end(x)
#define isz(x) (int)std::size(x)
// +, если сумма цифр делится на 3
// -, если р
int f(std::string s) {
    std::vector<int> sum{0};
    for (auto it : s) {
        sum.push_back(sum.back() + (it - '0'));
    }
    auto getSum = [&](int i, int j) {
        return sum[j+1] - sum[i];
    };
    std::vector<int> remSuff(isz(s)+1);
    int pow10 = 1;
    for (int i = isz(s)-1; i>= 0; i--) {
        remSuff[i] = ((s[i] - '0') * 1LL * pow10 + remSuff[i+1]) % 3;
        pow10 = int(pow10 * 10LL % 3);
    }
    int rem = 0, answ{0};
    for (int len1 = 1; len1 < isz(s); len1++) {
        // [0 .. len1) [len1 .. )
        ((rem *= 10) += (s[len1-1]-'0')) %= 3;
        int sumDL = getSum(0,len1-1);
        int sumDR = getSum(len1, isz(s)-1);
        answ += (sumDL+sumDR)%3==0;
        answ += (sumDL-sumDR)%3==0;
        answ += (rem == 0 || remSuff[len1] == 0);
    }
    return answ;
}
int main() {
    std::string s;
    while (std::cin >> s) {
        std::cout << f(s) << std::endl;
    }
}