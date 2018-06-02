#include <iostream>
#include <string>
#include <algorithm>

const int INF = (int)1e9+1;

int solve(std::string s, std::string sub) {
    const int n = (int)s.size();
    if (n == 2) {
        if (s == sub) {
            return 0;
        }
        if (s[0] == sub[1] && s[1] == sub[0]) {
            return 1;
        }
        return INF;
    }
    if (sub == "00") {
        int p0 = s.rfind(sub[0]);
        if (p0 == -1) {
            return INF;
        }
        int p1 = s.rfind(sub[1], p0-1);
        if (p1 == -1) {
            return INF;
        }
        int answ = 0;
        while (p0+1 < n) {
            std::swap(s[p0], s[p0+1]);
            p0++;
            answ++;
        }
        while (p1+1 < p0) {
            std::swap(s[p1], s[p1+1]);
            p1++;
            answ++;
        }
        return answ;
    }
    int p0 = s.rfind(sub[0]);
    if (p0 == -1) return INF;
    int p1 = s.rfind(sub[1]);
    if (p1 == -1) return INF;
    int answ = 0;
    if (p1 < p0) {
        while (s[n-1] != sub[0]) {
            std::swap(s[p0], s[p0+1]);
            ++p0;
            ++answ;
        }
        if (p1 == 0) {
            int j = p1+1;
            while (s[j] == '0') {
                j++;
            }
            while (j > 0) {
                std::swap(s[j], s[j-1]);
                ++answ;
                --j;
            }
            p1++;
        }
        while (s[n-1] != sub[1]) {
            std::swap(s[p1], s[p1+1]);
            answ++;
            p1++;
        }
    } else {
        while (s[n-1] != sub[1]) {
            std::swap(s[p1], s[p1+1]);
            ++p1;
            ++answ;
        }
        if (p0 == 0) {
            int j = p0+1;
            while (s[j] == '0') {
                j++;
            }
            while (j > 0) {
                std::swap(s[j], s[j-1]);
                ++answ;
                --j;
            }
            p0++;
        }
        while (s[n-2] != sub[0]) {
            std::swap(s[p0], s[p0+1]);
            answ++;
            p0++;
        }
    }
    return answ;
}

int smart(std::string s) {
    if ((int)s.size() <= 2 && std::stoll(s) < 25) {
        return -1;
    }
    int answ = std::min({solve(s, "00"), solve(s, "25"), solve(s, "50"), solve(s, "75")});
    return answ == INF ? -1 : answ;
}

int main() {
    std::string s;
    std::cin >> s;
    std::cout << smart(s);
    return 0;
}