#include <bits/stdc++.h>
#define all(x) std::begin(x), std::end(x)
#define isz(x) (int)std::size(x)
using pss = std::pair<std::string,std::string>;

auto split(std::vector<pss> teams) {
    // split list of participants into winners and losers:
    std::vector<pss> win,lose;
    for (auto &[fi,se] : teams) {
        if (se.front() == '0') lose.emplace_back(fi,se.substr(1));
        else win.emplace_back(fi,se.substr(1));
    }
    return std::make_pair(win,lose);
}

std::vector<std::tuple<int,int,std::string>> answer;

void finish(int place, std::vector<pss> teams) {
    // add given participants to table - they are finished participanting
    for (auto &[fi,se] : teams) {
        assert(isz(se)==0);
        answer.emplace_back(place,place+isz(teams)-1,fi);
    }
}
void solve(std::vector<pss> teams) {
    auto [W8,L8a] = split(teams);
    auto [W4,W8L] = split(W8);
    auto [L8b,L8L] = split(L8a);
    finish(13,L8L);
    L8b.insert(L8b.end(), all(W8L));
    auto [L4a, losers] = split(L8b);
    finish(9, losers);
    auto [L4b, losers2] = split(L4a);
    finish(7, losers2);
    auto [W2,W4L]=split(W4);
    L4b.insert(L4b.end(),all(W4L));
    auto [L2a,losers3]=split(L4b);
    finish(5,losers3);
    auto [L2b,losers4]=split(L2a);
    finish(4,losers4);
    auto [grand, L2b2]=split(W2);
    L2b.insert(L2b.end(),all(L2b2));
    auto [grand2, losers5] = split(L2b);
    finish(3,losers5);
    grand.insert(grand.end(),all(grand2));
    auto [winner,loser] = split(grand);
    finish(2,loser);
    finish(1,winner);
}
int main() {
    // input:
    std::vector<pss> a;
    for (int i = 0; i < 16; i++) {
        std::string fi, se;
        std::cin >> fi >> se;
        a.emplace_back(fi,se);
    }
    // solve:
    solve(a);
    // print answer:
    std::sort(all(answer));
    for (auto &[fi,se,th] : answer) {
        std::cout << fi;
        if (fi < se) {
            std::cout << "-" << se;
        }
        std::cout << " " << th << '\n';
    }
    return 0;
}