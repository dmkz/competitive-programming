#include <bits/stdc++.h>
// useful stuff:
#define all(x) std::begin(x), std::end(x)
#define isz(x) (int)std::size(x)
void setuniq(auto &x) { x.erase(std::unique(all(x)),x.end()); }
using vi = std::vector<int>;
using ll = long long;
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "{";
    bool isFirst = true;
    for (auto it : vec) {
        if (isFirst) isFirst = false;
        else os << ",";
        os << it;
    }
    return os << "}";
}
// first attempt to brute force solutions:
void stress() {
    std::map<int,vi> set;
    for (int x = 1; x <= (int)1e7; x++) {
        auto s = std::to_string(x);
        std::sort(all(s));
        int g = 0;
        do {
            g = std::gcd(g, std::stoi(s));
        } while (std::next_permutation(all(s)));
        set[g].push_back(x);
    }
    for (auto &[key,value] : set) {
        std::cout << key << ": " << value[0] << ", div = " << value[0] / key << std::endl;
    }
    std::exit(0);
}
// second attempt to brute force solutions:
int find(int x) {
    for (int y = 1; y <= 200000; y++) {
        int num = x * y;
        std::string s = std::to_string(num);
        std::sort(all(s));
        std::string r = s;
        setuniq(r);
        //if (isz(r) > 3) continue;
        int g = -1;
        do {
            if (g == -1) g = std::stoi(s);
            else g = std::gcd(g,std::stoi(s));
            if (g < x) break;
        } while (std::next_permutation(all(s)));
        if (g == x) return x * y;
    }
    return -1;
}
void stress2() {
    for (int x = 1000; x < 10000; x++) {
        int res = find(x);
        if (res != -1) {
            std::cout << x << ": " << res << std::endl;
        }
    }
    std::exit(0);
}
// third attempt to brute force solutions:
void stress3() {
    std::set<std::string> set;
    for (int d1 = 0; d1 <= 9; d1++) {
        for (int d2 = d1; d2 <= 9; d2++) {
            for (int d3 = d2; d3 <= 9; d3++) {
                for (int sn = 1; sn <= 18; sn++) {
                    for (int n1 = 1; n1 <= sn; n1++) {
                        for (int n2 = 1; n1 + n2 <= sn; n2++) {
                            const int n3 = sn - n1 - n2;
                            std::string s;
                            s += std::string(n1,'0'+d1);
                            s += std::string(n2,'0'+d2);
                            s += std::string(n3,'0'+d3);
                            set.insert(s);
                        }
                    }
                }
            }
        }
    }
    std::map<ll,std::vector<std::string>> answer;
    for (auto it : set) {
        ll g = -1;
        std::sort(all(it));
        do {
            if (g == -1) g = std::stoll(it);
            else g = std::gcd(g, std::stoll(it));
            if (g == 1) break;
        } while (std::next_permutation(all(it)));
        if (g > 1) {
            answer[g].push_back(it);
        }
    }
    for (auto &[key,value] : answer) {
        std::sort(all(value), [](const auto &lt, const auto &rt){
            return isz(lt) < isz(rt) || (isz(lt) == isz(rt) && lt < rt);
        });
        std::cout << key << ": " << value << std::endl;
    }
    std::exit(0);
}
int main() {
    //stress3();
    std::map<ll,ll> answ;
    answ[12]=48;    // 3 * 2^2
    answ[15]=5055;  // 3 * 5
    answ[18]=288;   // 3^2 * 2
    answ[21]=7077;  // 3 * 7
    answ[24]=8088;  // 3 * 2^3
    answ[27]=3699;  // 3^3
    answ[36]=48888; // 3^2 * 2^2
    answ[63]=111888; // 3^2 * 7
    answ[45]=5055555555LL;
    answ[54]=222888888LL;
    answ[72]=8088888888LL;
    answ[81]=9099999999LL;
    //stress();
    int tt; std::cin >> tt;
    while (tt --> 0) {
        ll n; std::cin >> n;
        if (answ.find(n) != answ.end()) {
            std::cout << answ[n] << '\n';
        } else {
            auto s = std::to_string(n);
            std::sort(all(s));
            setuniq(s);
            if (isz(s)==1) std::cout << n << '\n';
            else std::cout << -1 << '\n';
        }
    }
    return 0;
}