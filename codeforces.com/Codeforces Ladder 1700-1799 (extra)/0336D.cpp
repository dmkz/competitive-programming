/*
    Problem: 336D. Vasily the Bear and Beautiful Strings
    
    Solution: brute force, combinatorics, math, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef std::pair<int,int> pii;

const int mod = (int)1e9+7;

int& addto(int &a, int b) {
    return (a += b) >= mod ? (a -= mod) : a;
}

int &subfrom(int &a, int b) {
    return (a -= b) < 0 ? (a += mod) : a;
}

int add(int a, int b) {
    return addto(a,b);
}

int sub(int a, int b) {
    return subfrom(a,b);
}

int mul(int a, int b) {
    return int(1LL * a * b % mod);
}

int pow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = mul(res, a);
        }
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}

int inverse(int a) {
    return pow(a, mod-2);
}

pii fast(int n0, int n1) {
    if (n1 == 0) {
        if ((n0 + n1) % 2 == 0) { return pii(0, 1); } 
        else { return pii(1,0); }
    }
    if (n1 == 1) {
        if ((n0 + n1) % 2 == 0) { return pii((n0+n1)/2+1,(n0+n1)/2-1); }
        else { return pii((n0+n1)/2, (n0+n1+1)/2); }
    }
    int cnt0 = 1, cnt1 = 0, bin = 1;
    for (int i1 = n0+n1; i1 > n1; --i1) {
        bin = mul(mul(bin, i1), inverse(n0+n1-i1+1));
        cnt1 = sub(cnt0, cnt1);
        cnt0 = sub(bin, cnt1);
    }
    return pii(cnt0, cnt1);
}


int main() {
    int n0, n1, g;
    while (std::cin >> n0 >> n1 >> g) {
        auto ret = fast(n0,n1);
        std::cout << (g == 0 ? ret.first : ret.second) << std::endl;
    }
    return 0;
}