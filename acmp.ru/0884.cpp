/*
    Задача: 884. Дорога
    
    Решение: динамическое программирование, дп по подмножествам, битовые маски, O(32 * n + 21 * 2^21 + 2^26)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
typedef uint32_t ui;
typedef std::vector<int> vi;
typedef std::pair<int,int> pii;
vi getMasks(int k, std::string s) {
    s += 'A';
    vi ret, cnt(26);
    for (int i = 0; i < k; ++i) {
        cnt[s[i]-'A']++;
    }
    for (int i = k; i < isz(s); ++i) {
        int mask = 0;
        for (int bit = 0; bit < 26; ++bit) {
            mask |= (cnt[bit] > 0) << bit;
        }
        ret.push_back(mask);
        cnt[s[i+0]-'A']++;
        cnt[s[i-k]-'A']--;
    }
    return ret;
}
vi remove_covered(vi arr, int mask) {
    int sz = 0;
    for (int i = 0; i < isz(arr); ++i) {
        if ((arr[i] & mask) == 0) {
            arr[sz++] = arr[i];
        }
    }
    arr.resize(sz);
    return arr;
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int k; std::string s;
    while (std::cin >> k >> s) {
        vi masks = getMasks(k, s);
        const int H = 21, L = 5;
        std::vector<ui> cannot(1 << H);
        for (auto it : masks) {
            auto mask = ~it & ((1 << (H + L)) - 1);
            auto high = mask >> L;
            auto low  = mask & ((1 << L) - 1);
            for (int sub = 0; sub < (1 << L); sub++) {
                if ((low & sub) == sub) {
                    cannot[high] |= ui(1) << sub;
                }
            }
        }
        for (int bit = H-1; bit >= 0; --bit) {
            for (int mask = (1 << H) - 1; mask >= 0; --mask) {
                if ((mask >> bit) & 1) {
                    cannot[mask ^ (1 << bit)] |= cannot[mask];
                }
            }
        }
        pii res(26, (1 << 26) - 1);
        for (int mask = 1; mask < (1 << 26); ++mask) {
            auto high = mask >> L;
            auto low  = mask & ((1 << L) - 1);
            if ((cannot[high] >> low) & 1) { continue; }
            res = std::min(res, pii(__builtin_popcount(mask), mask));
        }
        int answ = res.second;
        std::cout << __builtin_popcount(answ) << std::endl;
        for (char c = 'A'; c <= 'Z'; c++) {
            if ((answ >> (c - 'A')) & 1) {
                std::cout << c << std::endl;
            }
        }
    }
    return 0;
}