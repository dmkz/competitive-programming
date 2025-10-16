// Задача: H, Вердикт: OK, Время: 39ms, Память: 2.71Mb

// Римских чисел всего 4000. Построим взвешенный граф на римских числах,
// где переходы между числами описываются правилами из условия.
// На построенном графе запустим алгоритм Дейкстры поиска всех кратчайших
// расстояний начиная из пустого римского числа.
// Затем ответим на запросы о кратчайших расстояниях до чисел из ввода

#include <bits/stdc++.h>
using namespace std;

// функция преобразования из арабского в римское:
const vector<pair<int,string>> table = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
    {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
    {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
};
string toRoman(int x) {
    string result;
    for (const auto &[n, s] : table)
        while (x >= n) {
            result += s;
            x -= n;
        }
    return result;
}

// генерируем словарь из всех римских чисел и запоминаем их стоимости
map<string, int> idOfRomanNum;
vector<string> romanNumber;
vector<int> addCost, delCost;
void generateAllRomanNumbers() {
    romanNumber.resize(4000);
    addCost.resize(4000);
    delCost.resize(4000);
    for (int i = 1; i <= 3999; i++) {
        string roman = toRoman(i);
        romanNumber[i] = roman;
        idOfRomanNum[roman] = i;
        addCost[i] = i;
        delCost[i] = i;
    }
}

// функция поиска номера по записи римского числа в словаре
int getRomanId(const std::string &s) {
    auto it = idOfRomanNum.find(s);
    if (it == idOfRomanNum.end())
        return 0;
    return it->second;
}

// предподсчитываем переходы в графе римских чисел
vector<vector<pair<int,int>>> add, del;
void precalcGraphEdges() {
    add.resize(4000);
    del.resize(4000);
    // для каждого числа предподсчитываем способы его разделения на два числа:
    for (int u = 1; u <= 3999; u++) {
        string s = romanNumber[u];
        for (int prefix = 1; prefix < (int)s.size(); prefix++) {
            auto left = s.substr(0, prefix); // префикс
            auto right = s.substr(prefix); // суффикс
            int leftId = getRomanId(left); // номер префикса
            int rightId = getRomanId(right); // номер суффикса
            if (leftId && rightId) // если и префикс, и суффикс римские
                del[u].push_back({leftId, rightId}); // добавляем переход
        }
    }
    // используем предподсчитанное разделение чтобы предподсчитать добавления:
    for (int uv = 1; uv <= 3999; uv++)
        for (const auto &[u, v] : del[uv]) {
            add[u].push_back({v, uv}); // добавление "v" к "u" чтобы получить "uv"
            add[v].push_back({u, uv}); // добавление "u" к "v" чтобы получить "uv"
        }
    // добавления к пустой строке: "" -> "v"
    for (int v = 1; v <= 3999; v++)
        add[0].push_back({v, v});
}

// находим расстояния до всех римских чисел алгоритмом Дейкстры
vector<int> dist;
void runDijkstra() {
    // инициализируем расстояния
    dist.assign(4000, 1'000'000'000);
    // инициализируем очередь
    using pii = pair<int, int>; // {расстояние, число}
    priority_queue<pii, vector<pii>, greater<pii>> queue;
    queue.push({0, 0});
    // итерации
    while (queue.size()) {
        auto [d, u] = queue.top();
        queue.pop();
        if (d >= dist[u])
            continue;
        dist[u] = d;
        string s = romanNumber[u];
        // переходы: сначала пробуем удалять префикс или суффикс:
        for (const auto &[leftId, rightId] : del[u]) {
            // удаляем префикс:
            queue.push({d + delCost[leftId], rightId});
            // удаляем суффикс:
            queue.push({d + delCost[rightId], leftId});
        }
        // теперь пробуем добавлять к префиксу или суффиксу:
        for (const auto &[num, res] : add[u])
            queue.push({d + addCost[num], res});
    }
}
main() {
    // ускорение ввода-вывода:
    ios::sync_with_stdio(false);
    cin.tie(0);
    generateAllRomanNumbers();
    // обновляем числа, стоимости который изменены:
    int n; cin >> n;
    while (n --> 0) {
        int num, currAddCost, currDelCost;
        cin >> num >> currAddCost >> currDelCost;
        addCost[num] = currAddCost;
        delCost[num] = currDelCost;
    }
    precalcGraphEdges();
    runDijkstra();
    // отвечаем на запросы:
    int nQueries; cin >> nQueries;
    while (nQueries --> 0) {
        int v; cin >> v;
        cout << dist[v] << '\n';
    }
}
