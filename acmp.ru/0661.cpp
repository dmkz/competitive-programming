/*
    Задача: 661. «Стабильный» интернет
    
    Решение: std::priority_queue, динамическое программирование, O(n*log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define unique(x) (x).erase(std::unique(all(x)), (x).end())
#define lowpos(y,x) int(std::lower_bound(all(y), (x)) - (y).begin())

typedef std::vector<int> vi;
typedef std::pair<int,int> pii;

struct Card { 
    int lt, rt, cost; 
};

struct GreaterByCost {
    bool operator()(const Card& a, const Card& b) {
        return a.cost > b.cost;
    }
};

int solve(int L, int R, vi lt, vi rt, vi cost) {
    // Сжимаем координаты:
    vi x{0,L,L+1,R-1,R};
    for (int l : lt) { x.insert(x.end(), {std::max(L,l-1), l, std::min(l+1,R)}); }
    for (int r : rt) { x.insert(x.end(), {std::max(L,r-1), r, std::min(r+1,R)}); }
    std::sort(all(x));
    unique(x);
    L = lowpos(x, L);
    R = lowpos(x, R);
    for (int& coord : lt) { coord = lowpos(x, coord); }
    for (int& coord : rt) { coord = lowpos(x, coord); }
    assert(L == 1);
    // Создаем события на вход в отрезок действия карты:
    std::vector<pii> needOpen;
    for (int i = 0; i < isz(cost); ++i) {
        needOpen.push_back(pii(lt[i], i));
    }
    std::sort(all(needOpen));
    std::reverse(all(needOpen));
    // Динамическое программирование:
    std::priority_queue<Card, std::vector<Card>, GreaterByCost> opened;
    vi dp(isz(x));
    for (int i = 1; i < isz(x); ++i) {
        while (isz(needOpen) > 0 && needOpen.back().first == i) {
            auto back = needOpen.back();
            needOpen.pop_back();
            int id = back.second;
            opened.push(Card{lt[id], rt[id], cost[id]+dp[i-1]});
        }
        while (isz(opened) > 0 && opened.top().rt < i) {
            opened.pop();
        }
        assert(isz(opened) > 0);
        dp[i] = opened.top().cost;
    }
    return dp[R];
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        int L, R; std::cin >> L >> R;
        vi lt, rt, cost;
        for (int i = 0; i < n; ++i) {
            int l, r, c; std::cin >> l >> r >> c;
            l = std::max(l, L);
            r = std::min(r, R);
            if (l <= r) {
                lt.push_back(2*l);
                rt.push_back(2*r);
                cost.push_back(c);
            }
        }
        std::cout << solve(2*L,2*R,lt,rt,cost) << std::endl;
    }
    return 0;
}