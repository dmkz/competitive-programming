/*
    Problem: 469B. Chat Online
    
    Solution: implementation, O(n * MAX^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

struct Pair {
    int a, b;
};

typedef std::vector<Pair> vp;
typedef std::vector<int> vi;

bool solve(int t, const vp& p1, const vp& p2) {
    vi time1(2001), time2(2001);
    for (auto& p : p1) {
        for (int i = p.a; i <= p.b; ++i) time1[i] = 1;
    }
    for (auto& p : p2) {
        for (int i = p.a+t; i <= p.b+t; ++i) time2[i] = 1;
    }
    for (int i = 0; i <= 2000; ++i) {
        if (time1[i] && time2[i]) return true;
    }
    return false;
}

int main() {
    int n1, n2, s, f; std::cin >> n1 >> n2 >> s >> f;
    vp p1(n1), p2(n2);
    for (int i = 0; i < n1; ++i) std::cin >> p1[i].a >> p1[i].b;
    for (int i = 0; i < n2; ++i) std::cin >> p2[i].a >> p2[i].b;
    int answ = 0;
    for (int t = s; t <= f; ++t) answ += solve(t, p1, p2);
    std::cout << answ;
    return 0;
}