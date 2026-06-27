#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;

// Поиск всех циклов:
vector<vector<int>>
findCycles(const vector<int> &p)
{
    vector<int> visited(isz(p));
    vector<vector<int>> cycles;
    for (int i = 0; i < isz(p); i++)
        if (!visited[i])
        {
            visited[i] = true;
            cycles.push_back({i});
            for (int j = p[i]; j != i; j = p[j])
            {
                visited[j] = true;
                cycles.back().push_back(j);
            }
        }
    return cycles;
}


main() {
    // читаем элементы и запоминаем, на каких позициях они стоят:
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i], p[i]--;
    vector<vector<pair<int,int>>> answer;
    auto doSwap = [&](int i, int j) {
        answer.back().emplace_back(i+1, j+1);
        swap(p[i], p[j]);
    };    
    while (true) {
        // новый раунд:
        answer.push_back({});
        // раскладываем на циклы и разделяем циклы на пары:
        auto cycles = findCycles(p);
        for (const auto &cycle : cycles)
            for (int i = 0, j = isz(cycle)-1; i < j; i++, j--)
                doSwap(cycle[i], cycle[j]);
        // если ничего не сделали, то выходим:
        if (answer.back().empty()) {
            answer.pop_back();
            break;
        }
    }
    cout << answer.size() << "\n";
    for (const auto &vec : answer) {
        cout << vec.size() << "\n";
        for (auto [u,v] : vec)
            cout << u << ' ' << v << "\n";
    }
}