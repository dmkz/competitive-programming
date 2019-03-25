#include <bits/stdc++.h>
#include "FastIO.hpp"

int main() {
    FastIO::Reader fin;
    FastIO::Writer fout;
    typedef std::vector<int> vi;
    typedef std::pair<int,int> pii;
    for (int n; fin >> n; fout << '\n') {
        std::string fi, se;
        fin >> fi >> se;
        std::map<char, vi> fiCnt, seCnt;
        for (int i = 0; i < n; ++i) {
            fiCnt[fi[i]].push_back(i+1);
        }
        for (int i = 0; i < n; ++i) {
            seCnt[se[i]].push_back(i+1);
        }
        std::vector<pii> answ;
        for (char c = 'a'; c <= 'z'; ++c) {
            while (!(fiCnt[c].empty() || seCnt[c].empty())) {
                answ.push_back(pii(fiCnt[c].back(), seCnt[c].back()));
                fiCnt[c].pop_back();
                seCnt[c].pop_back();
            }
        }
        for (char c = 'a'; c <= 'z'; ++c) {
            vi& first = fiCnt[c];
            vi& second = seCnt['?'];
            while (!(first.empty() || second.empty())) {
                answ.push_back(pii(first.back(), second.back()));
                first.pop_back();
                second.pop_back();
            }
        }
        for (char c = 'a'; c <= 'z'; ++c) {
            vi& first = fiCnt['?'];
            vi& second = seCnt[c];
            while (!(first.empty() || second.empty())) {
                answ.push_back(pii(first.back(), second.back()));
                first.pop_back();
                second.pop_back();
            }
        }
        {
            vi& first = fiCnt['?'];
            vi& second = seCnt['?'];
            while (!(first.empty() || second.empty())) {
                answ.push_back(pii(first.back(), second.back()));
                first.pop_back();
                second.pop_back();
            }
        }
        fout << answ.size() << '\n';
        for (auto &p : answ) {
            fout << p.first << ' ' << p.second << '\n';
        }
    }
    return 0;
}