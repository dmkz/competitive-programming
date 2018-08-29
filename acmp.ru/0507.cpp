/*
    Задача: 507. Адронный коллайдер
    
    Решение: BFS, O(4^n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <set>
#include <queue>

struct State {

    int number;

    State(int num) : number(num) { }
    
    State(int n1, int n2, int n3, int n4) {
        number = n1 + (n2 << 2) + (n3 << 4) + (n4 << 6);
    }
    
    int get(int i) {
        return (number >> 2*i) & 3;
    }
    
    State dec(int i) {
        return State(number - (1 << 2 * i));
    }
};

inline bool operator<(const State& a, const State& b) {
    return a.number < b.number;
}

int main() {
    int n; scanf("%d", &n);
    State s(0);
    {
        int cnt[4] = {};
        for (int i = 0; i < n; ++i) {
            int c; scanf("%d", &c);
            cnt[i] = c;
        }
        s = State(cnt[0], cnt[1], cnt[2], cnt[3]);
    }
    int g[4][4];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &g[i][j]);
        }
    }
    std::set<State> visited;
    std::set<State> stfinal;
    std::queue<State> queue;
    visited.insert(s);
    queue.push(s);
    while (!queue.empty()) {
        auto curr = queue.front(); queue.pop();
        bool flag = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!g[i][j]) continue;
                if (i == j) {
                    if (curr.get(i) >= 2) {
                        flag = false;
                        auto next = curr.dec(j);
                        if (visited.find(next) == visited.end()) {
                            queue.push(next);
                            visited.insert(next);
                        }
                    }
                } else if (curr.get(i) > 0 && curr.get(j) > 0) {
                    flag = false;
                    auto next = curr.dec(j);
                    if (visited.find(next) == visited.end()) {
                        queue.push(next);
                        visited.insert(next);
                    }
                }
            }
        }
        if (flag) {
            stfinal.insert(curr);
        }
    }
    printf("%d\n", (int)stfinal.size());
    for (auto curr : stfinal) {
        for (int i = 0; i < n; ++i) {
            printf("%d ", curr.get(i));
        }
        printf("\n");
    }
    
    return 0;
}