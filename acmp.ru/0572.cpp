/*
    Задача: 572. Технология программирования
    Решение: жадный алгоритм, сортировка, динамическое программирование, O(n^2)
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
template<typename A, typename B> A& remax(A& a, B b) { return a = (a < b) ? b : a; }
struct Pair { int a, b, i; };
struct State {
    int res; int16_t id, prev_i, prev_j;
    State(int res_ = INT_MIN, int16_t id_ = 0, int16_t prev_i_ = -1, int16_t prev_j_ = -1)
        : res(res_), id(id_), prev_i(prev_i_), prev_j(prev_j_) { }
};
bool operator<(const State& a, const State& b) {
    return a.res < b.res;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n, st; std::cin >> n >> st; ) {
        std::vector<Pair> pos, neg;
        vi answ;
        for (int i = 0,a,b; i < n; i++) {
            std::cin >> a >> b;
            if (b >= 0) {
                pos.push_back(Pair{a,b,i+1});
            } else {
                neg.push_back(Pair{a,b,i+1});
            }
        }
        std::stable_sort(all(pos), [](auto lhs, auto rhs) { return lhs.a < rhs.a; });
        for (auto it : pos) {
            if (it.a <= st) {
                answ.push_back(it.i);
                st += it.b;
            }
        }
        std::stable_sort(all(neg), [](auto lhs, auto rhs) { return lhs.a + lhs.b > rhs.a + rhs.b; } );
        // dp[visited][taken];
        std::vector<std::vector<State>> dp(1+n, std::vector<State>(1+n, State()));
        dp[0][0] = State(st);
        n = isz(neg);
        for (int i = 0; i < n; i++) {
            int visited = i;
            for (int taken = 0; taken <= n; ++taken) {
                remax(dp[visited+1][taken], dp[visited][taken]);
            }
            for (int taken = 0; taken < n; ++taken) {
                auto prev = dp[visited][taken];
                if (prev.res >= neg[i].a) {
                    prev.id = neg[i].i;
                    prev.prev_i = visited;
                    prev.prev_j = taken;
                    prev.res += neg[i].b;
                    remax(dp[visited+1][taken+1], prev);
                }
            }
        }
        int i = 0, j = 0;
        for (int taken = 0; taken <= n; ++taken) {
            if (dp[n][taken].res > INT_MIN) {
                i = n; j = taken;
            }
        }
        vi stack;
        while (i > 0 && j > 0) {
            stack.push_back(dp[i][j].id);
            int pi = dp[i][j].prev_i;
            int pj = dp[i][j].prev_j;
            i = pi; j = pj;
        }
        std::reverse(all(stack));
        answ.insert(answ.end(), all(stack));
        std::cout << isz(answ) << "\n";
        for (auto it : answ) { std::cout << it << ' '; }
        std::cout << std::endl;
    }
    return 0;
}