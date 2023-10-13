#include "template.hpp"
#include "hash.hpp"

#pragma GCC optimize("Ofast")
#pragma GCC target("avx")

/*
    вывести в качестве ответа надо палиндром
    он должен быть получен путём удаления минимального количества символов из оригинальной строки и переупорядочивания оставшихся
    в ответ можно добавить <= одного символа так, чтобы он стал идеальным доводом
*/

using pis = std::pair<int, std::string>;

pis globalAnswer{1e9+1,""};

void updateAnswer(int nOps, const std::string &s) {
    if (globalAnswer.first < nOps)
        return;
    if (globalAnswer.first > nOps) {
        globalAnswer.first = nOps;
        globalAnswer.second = s;
    }
    remin(globalAnswer.second, s);
}

algos::hash::PolyHash ht, hr;

auto isPalAfterRemove(int i) {
    return ht.hashAfterRemove(i) == hr.hashAfterRemove(isz(hr)-i-1);
}

void construct(int n, int firstChar, int ops, const vi &sz, const auto &adj, char toRemove, vi cnt) {
    int p4 = 0, p2 = 0;
    std::string s(n, '?');
    bool ok = 1;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            p4 = firstChar;
            p2 = firstChar;
        } else if (i == 1) {
            p4 = 0;
            p2 = 0;
        }
        if (s[i] == '?') {
            if (sz[i] == 4) {
                for (int attempt = 0; attempt < 2; attempt++) {
                    while (p4 < 26 && cnt[p4] < 4)
                        p4++;
                    if (p4 == 26)
                        p4 = 0;
                }
                assert(p4 < 26);
                auto [x,y,z] = adj[i];
                s[i] = s[x] = s[y] = s[z] = char('a' + p4);
                cnt[p4] -= 4;
            } else {
                for (int attempt = 0; attempt < 2; attempt++) {
                    while (p2 < 26 && cnt[p2] % 4 != 2)
                        p2++;
                    if (p2 == 26)
                        p2 = 0;
                }
                if (p2 == 26)
                    ok = false;
                else {
                    auto [x,y,z] = adj[i];
                    s[i] = s[x] = char('a' + p2);
                    cnt[p2] -= 2;
                }
            }
        }
    }
    if (ok) {
        std::string t = s;
        std::string r(t.rbegin(), t.rend());
        ht.build(t);
        hr.build(r);
        if (toRemove != '?') {
            int posToRemove = -1;
            for (int j = isz(t)-1; j >= 0; j--) {
                if (t[j] == toRemove && isPalAfterRemove(j)) {
                    posToRemove = j;
                    break;
                }
            }
            for (int j = 0; j + 1 < isz(t); j++) {
                if (t[j] == toRemove && t[j] > t[j+1] && isPalAfterRemove(j))
                {
                    posToRemove = j;
                    break;
                }
            }
            if (posToRemove >= 0) {
                t.erase(t.begin()+posToRemove);
                updateAnswer(ops,t);
            }
        } else {
            updateAnswer(ops,t);
        }
    }
}
std::mt19937 gen((int)std::chrono::high_resolution_clock::now().time_since_epoch().count());
void solve(const vi origCnt, char toRemove, int &bestOps) {
    // символы присутствуют четвёрками либо двойками
    // двойка ровно одна
    pis answ{(int)1e9+1,""};
    vi poses;
    for (int pos2 = -1; pos2 <= 25; pos2++)
        poses << pos2;
    std::shuffle(all(poses), gen);
    for (int pos2 : poses) {
        vi cnt = origCnt;
        int ops = 0;
        for (int i = 0; i < 26; i++) {
            if (i != pos2) {
                ops += (cnt[i] % 4);
                cnt[i] -= (cnt[i] % 4);
            } else {
                ops += (cnt[i] % 2);
                cnt[i] -= (cnt[i] % 2);
            }
        }
        if (ops > bestOps)
            continue;
        int n = std::accumulate(all(cnt), 0);
        int k = n / 4;
        std::vector<tiii> adj(n);
        vi sz(n);
        for (int i = 0; i < k; i++) {
            int x = i, y = 2 * k - i - 1 + (n % 4 != 0);
            int w = n - x - 1, z = n - y - 1;
            adj[x] = {y,z,w};
            sz[x] = 4;
        }
        if (n % 4 == 2) {
            int x = k, y = n - k - 1;
            adj[x] = {y,-1,-1};
            sz[x] = 2;
        }
        vi chars = {0};
        if (toRemove != '?')
            chars << (toRemove - 'a');
        for (int firstChar : chars) {
            construct(n, firstChar, ops, sz, adj, toRemove, cnt);
            remin(bestOps, globalAnswer.first);
        }
    }
}

std::string fast(std::string s) {
    vi cnt(26);
    for (auto &it : s) cnt[it -= 'a']++;
    int bestOps = (int)1e9+1;
    globalAnswer = pis(1e9+1,"");
    solve(cnt,'?',bestOps);
    vi chars;
    for (int i = 0; i < 26; i++)
        chars << i;
    std::shuffle(all(chars), gen);
    for (int i : chars) {
        cnt[i]++;
        solve(cnt, char('a'+i), bestOps);
        cnt[i]--;
    }
    std::string t = globalAnswer.second;
    assert(isz(t) <= isz(s));
    return t;
}

int main() {
    std::string s; std::cin >> s;
    std::cout << fast(s) << std::endl;
}
