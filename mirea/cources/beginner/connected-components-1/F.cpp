#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int nVert, nEdges;
    cin >> nVert >> nEdges;
    vector adj(nVert, vector<int>{});
    for (int i = 0; i < nEdges; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // находим каждую компоненту связности
    vector<bool> used(nVert, false);
    vector<vector<int>> answer, teams1, teams2;
    bool possible = true;
    for (int s = 0; s < nVert; s++)
        if (!used[s]) {
            // запускаем обход в ширину из стартовой вершины, чтобы
            // найти компоненту связности
            queue<int> q;
            q.push(s);
            used[s] = 1;
            vector<int> currComp = {};
            while (q.size()) {
                // вынимаем вершину из начала очереди
                int u = q.front();
                q.pop();
                // обрабатываем текущую вершину
                currComp.push_back(u);
                // посещаем соседей
                for (int v : adj[u])
                    if (!used[v]) {
                        used[v] = 1;
                        q.push(v);
                    }
            }
            if (currComp.size() > 3) {
                // если размер больше трёх, то, по условию задачи,
                // невозможно составить команды, потому что
                // каждый человек должен быть в команде с каждым, с которым
                // он дружит, а нам придётся разорвать некоторые связи
                possible = false;
                break;
            } else if (currComp.size() == 3) {
                // команда уже собрана
                answer.push_back(currComp);
            } else {
                // иначе размер компоненты равен либо 2, либо 1
                // нужно их доукомлектовать
                if (currComp.size() == 2)
                    teams2.push_back(currComp);
                else
                    teams1.push_back(currComp);
            }
        }
    // доукомплектуем команды, состоящие из двух участников, одиночками
    for (auto &team : teams2) {
        if (!teams1.empty()) {
            team.insert(team.end(), all(teams1.back()));
            teams1.pop_back();
            answer.push_back(team);
        } else {
            // невозможно, так как команды из одного человека закончились
            possible = false;
        }
    }
    // затем команды из 3-х одиночек
    if (isz(teams1) % 3 == 0)
        for (int i = 0; i + 2 < isz(teams1); i += 3)
            answer.push_back({teams1[i][0], teams1[i+1][0], teams1[i+2][0]});
    // выводим ответ
    if (possible) {
        for (const auto &team : answer) {
            for (const auto &it : team)
                cout << it+1 << ' ';
            cout << '\n';
        }
    } else {
        cout << "-1\n";
    }
}
