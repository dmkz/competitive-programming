#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
const int PMAX = 40;

using ll = long long;
using vl = std::vector<ll>;

struct Trie {
    
    struct Node {
        int next[2]{0};
    };
    
    std::vector<Node> data{Node()};
    
    void insert(ll x) {
        int v = 0;
        for (int p = PMAX; p >= 0; p--) {
            if ((x >> p) & 1) {
                if (!data[v].next[1]) {
                    data[v].next[1] = isz(data);
                    data.push_back({});
                }
                v = data[v].next[1];
            } else {
                if (!data[v].next[0]) {
                    data[v].next[0] = isz(data);
                    data.push_back({});
                }
                v = data[v].next[0];
            }
        }
    }
    
    ll max(ll x) const {
        int v = 0;
        ll answ = 0;
        for (int p = PMAX; p >= 0; p--) {
            int want = ((x >> p) & 1) ? 0 : 1;
            if (data[v].next[want]) {
                v = data[v].next[want];
                answ |= (1LL << p);
            } else {
                assert(data[v].next[1-want]);
                v = data[v].next[1-want];
            }
        }
        return answ;
    }
    
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    while (std::cin >> n) {
        vl a(1+n), s(1+n);
        for (int i = 1; i <= n; i++) {
            std::cin >> a[i];
            s[i] = a[i] ^ s[i-1];
        }
        Trie trie;
        trie.insert(0);
        ll answ(0), suff(0);
        for (int len = n; len >= 0; len--) {
            answ = std::max(answ, trie.max(s[len]));
            suff ^= a[len];
            trie.insert(suff);
        }
        std::cout << answ << std::endl;
    }
    return 0;
}