/*
    Выгодно объединять только в группы по 2 и 3. Остальные мы можем расформировать на группы меньшего размера с меньшим риском.
    
    Используем ДП по количество набранных участников. Переходы: последняя группа была либо из трех либо, из двух человек.
*/

#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <bits/stdc++.h>

struct Agent {
    int age, risk;
    
    static Agent read() {
        int a, r; scanf("%d %d", &a, &r);
        return Agent{a, r};
    }
};

int main() {
    int n; scanf("%d", &n);
    std::vector<Agent> arr(1+n);
    for (int i = 1; i <= n; ++i) {
        arr[i] = Agent::read();
    }
    std::sort(arr.begin(), arr.end(), [](const Agent& a, const Agent& b){
        assert(a.age != b.age);
        return a.age < b.age;
    });
    const int INF = (int)1e9+1;
    std::vector<int> min(1+n, INF);
    
    min[2] = arr[2].risk;
    if (n >= 3) {
        min[3] = arr[3].risk + arr[2].risk;
    }
    if (n >= 4) {
        min[4] = arr[2].risk + arr[4].risk;
    }
    for (int len = 5; len <= n; ++len) {
        min[len] = std::min(min[len-2]+arr[len].risk, min[len-3]+arr[len-1].risk+arr[len].risk);
    }
    printf("%d\n", min[n]);
    
    return 0;
}