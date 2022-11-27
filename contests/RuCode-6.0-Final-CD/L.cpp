#include <bits/stdc++.h>

int n = 10;
const bool debug = 1;
int maxPrimeDiv(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            debug && std::cout << "max prime div for n = " << n << " is " << i << std::endl;
            return i;
        }
    }
    debug && std::cout << "max prime div for n = " << n << " is " << n << std::endl;
    assert(n > 1);
    return n;
}

int ask(int x) {
    assert(0 <= x && x <= 2022);
    std::cout << "? " << x << std::endl;
    n += x;
    int res = maxPrimeDiv(n); //std::cin >> res;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    const int max_req = 60;
    std::vector<int> nods(2000001, 0);
    nods[1] = 1;
    for (int it = 2; it < nods.size(); ++it) {
        if (nods[it] == 0) {
            for (int jt = it; jt < nods.size(); jt+=it) {
                if (nods[jt] == 0) {
                    nods[jt] = it;
                }
            }
        }
    }

    std::vector<int> substr(max_req);
    for (int it=0; it < max_req; ++it) {
        //substr[it] = ask(1);
        std::cout << "? " << 1 << std::endl;
        std::cin >> substr[it];
    }
    for (size_t it = 1; it < nods.size()-substr.size(); ++it) {
        bool is_eq = true;
        for (size_t jt = 0; jt < substr.size(); ++jt) {
            is_eq &= substr[jt] == nods[it+jt];
        }
        if (is_eq) {
            std::cout << "! " << it-1;
            return 0;
        }
    }
    return 0;
}