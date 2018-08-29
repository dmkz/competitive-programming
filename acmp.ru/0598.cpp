/*
    Задача: Друзья - 2
    
    Решение: перебор, O(2^n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>

#define size(x) (int)(x).size()

int n, g[16][16];
std::vector<int> answ, team;

void go(int cur) {
    if (size(team) > size(answ)) {
        answ = team;
    }
    if (size(team) == 5 || size(team) == n || cur > n) {
        return;
    }
    bool flag = true;
    for (auto u : team) {
        if (!g[u][cur]) { 
            flag = false; 
            break; 
        }
    }
    if (flag) {
        team.push_back(cur);
        go(cur+1);
        team.pop_back();
    }
    go(cur+1);
}


int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &g[i][j]);
        }
    }
    go(1);
    std::vector<int> group(1+n);
    for (auto it : answ) group[it] = 1;
    int cnt = 1;
    for (int i = 1; i <= n; ++i) {
        if (group[i] == 0) {
            group[i] = ++cnt;
        }
    }
    printf("%d\n", cnt);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", group[i]);
    }
    return 0;
}