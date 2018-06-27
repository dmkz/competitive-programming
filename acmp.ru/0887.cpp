/*
    "Доказательство теоремы": деревья, поиск в глубину
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    int nVert;
    scanf("%d", &nVert);
    
    // Чтение ребер:
    std::vector<std::vector<int>> edges(1+nVert);
    
    for (int id = 1; id <= nVert; ++id) {
        int value;
        while (scanf("%d", &value), value) {
            edges[id].push_back(value);
        }
    }
    
    // Поиск в глубину для нахождения множеств теорем, которые нужно доказать:
    std::vector<std::vector<int>> from(1+nVert);
    
    std::function<int(int,int)> visit = [&](const int curr, const int parent) {
        std::vector<std::pair<int,int>> values;
        for (int next : edges[curr]) {
            if (next != parent) {
                values.push_back(std::make_pair(visit(next, curr), next));
            }
        }
        std::sort(values.begin(), values.end());
        int sum = 0;
        for (int i = 0; 2 * from[curr].size() < values.size(); ++i) {
            from[curr].push_back(values[i].second);
            sum += values[i].first + 1;
        }
        return sum;
    };
    
    visit(1,0);
    
    // Формирование ответа:
    std::vector<int> answ;
    
    std::function<void(int)> get_answ = [&](const int curr) {
        for (int next : from[curr]) {
            get_answ(next);
        }
        answ.push_back(curr);
    };
    
    get_answ(1);
    
    // Вывод ответа:
    printf("%d\n", (int)answ.size());
    for (auto& it : answ) {
        printf("%d\n", it);
    }
    
    return 0;
}