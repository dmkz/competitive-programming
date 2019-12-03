/*
    Problem: 321B. Ciel and Duel
    Solution: greedy, implementation, O(n*m)
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
template<typename A, typename B> A& remax(A& a, B b) { return a = (a < b ? b : a); }
const auto io_sync_off = [](){std::ios_base::sync_with_stdio(0);std::cin.tie(0);return 0;}();
using vi = std::vector<int>;
int main() {
    int n, m;
    while (std::cin >> n >> m) {
        vi atk, def, cards(m);
        for (int i = 0; i < n; i++) {
            std::string s; int v; 
            std::cin >> s >> v;
            if (s == "ATK") { atk.push_back(v); }
            else { def.push_back(v); }
        }
        for (auto &it : cards) std::cin >> it;
        std::sort(all(atk));
        std::sort(all(def));
        std::sort(all(cards));
        int answ = 0;
        for (int i = 1; i <= isz(atk); i++) {
            int tmp = 0;
            for (int j = isz(cards)-1, k = i-1; k >= 0 && j >= 0; j--,k--) {
                if (cards[j] >= atk[k]) {
                    tmp += cards[j] - atk[k];
                }
            }
            remax(answ, tmp);
        }
        bool ok = true;
        for (auto it : def) {
            auto rem = std::upper_bound(all(cards), it);
            if (rem == cards.end()) {
                ok = false;
                break;
            }
            cards.erase(rem);
        }
        if (ok) {
            int tmp = 0;
            for (int j = isz(cards)-1, k = isz(atk)-1; j >= 0; j--,k--) {
                int curr = 0;
                if (k >= 0) {
                    curr = atk[k];
                }
                if (cards[j] >= curr) {
                    tmp += cards[j] - curr;
                } else {
                    break;
                }
            }
            remax(answ, tmp);
        }
        std::cout << answ << std::endl;
    }
}