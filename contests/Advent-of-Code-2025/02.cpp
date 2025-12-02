#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define int int64_t
void solveEasy() {
    std::string s; std::getline(std::cin, s);
    s += ',';
    std::istringstream ss(s);
    char c1, c2;
    int answ{};
    for (int L, R; ss >> L >> c1 >> R >> c2; ) {
        std::cout << "[" << L << " ... " << R << "]" << std::endl;
        for (int x = L; x <= R; x++) {
            s = std::to_string(x);
            size_t len = s.size();
            std::string left = s.substr(0, len / 2);
            std::string right = s.substr(left.size());
            if (left == right)
                answ += x;
        }
    }
    std::cout << answ << std::endl;
}
void solveHard() {
    std::string s; std::getline(std::cin, s);
    s += ',';
    std::istringstream ss(s);
    char c1, c2;
    int answ{};
    for (int L, R; ss >> L >> c1 >> R >> c2; ) {
        std::cout << "[" << L << " ... " << R << "]" << std::endl;
        for (int x = L; x <= R; x++) {
            s = std::to_string(x);
            int len = (int)s.size();
            bool ok = false;
            for (int pref = 1; pref <= len / 2; pref++) {
                std::string t = s.substr(0, pref);
                while (isz(t) < isz(s))
                    t += s.substr(0, pref);
                if (t == s) {
                    ok = true;
                    break;
                }
            }
            if (ok)
                answ += x;
        }
    }
    std::cout << answ << std::endl;
}
main() {
    solveHard();
}
