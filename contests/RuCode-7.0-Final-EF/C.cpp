#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем ограничения на переменные:
    int n; scanf("%d", &n);
    int min[n], max[n], hasMin[n]{}, hasMax[n]{};
    string name[n];
    for (int i = 0; i < n; i++) {
        char buf[100];
        scanf(" inf.readInt (%d, %d, \"%[^\"]\");", min+i, max+i, buf);
        name[i] = buf;
    }
    // читаем тесты + выводим ошибку если она есть:
    int t; scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        for (int j = 0; j < n; j++) {
            int x; scanf("%d", &x);
            if (x < min[j] || x > max[j]) {
                printf("Error\n%d %s\n", i, name[j].c_str());
                return 0;
            }
            hasMin[j] |= (x == min[j]);
            hasMax[j] |= (x == max[j]);
        }
    }
    // смотрим кто там без минимума и без максимума:
    vector<int> withoutMin, withoutMax;
    for (int j = 0; j < n; j++) {
        if (!hasMin[j]) withoutMin.push_back(j);
        if (!hasMax[j]) withoutMax.push_back(j);
    }
    // выводим инфу о минимумах:
    if (withoutMin.empty()) printf("Min OK\n");
    else {
        printf("Warning: Min");
        for (int j : withoutMin)
            printf(" %s", name[j].c_str());
        printf("\n");
    }
    // выводим инфу о максимумах:
    if (withoutMax.empty()) printf("Max OK\n");
    else {
        printf("Warning: Max");
        for (int j : withoutMax)
            printf(" %s", name[j].c_str());
        printf("\n");
    }
}