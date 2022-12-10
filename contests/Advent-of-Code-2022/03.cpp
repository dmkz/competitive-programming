#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
void sort_and_unique(auto &x) {
    std::sort(all(x));
    x.erase(std::unique(all(x)), x.end());
}
int priority(char c) {
    return ('A' <= c && c <= 'Z') ? (c - 'A' + 27) : (c - 'a' + 1);
}
int main() {
    std::string a,b,c;
    int total{};
    while(std::cin >> a >> b >> c) {
        sort_and_unique(a);
        sort_and_unique(b);
        sort_and_unique(c);
        std::string res;
        std::set_intersection(all(a), all(b), std::back_inserter(res));
        a = res;
        res.clear();
        std::set_intersection(all(a), all(c), std::back_inserter(res));
        assert(isz(res) == 1);
        total += priority(res[0]);
    }
    std::cout << total << std::endl;
}