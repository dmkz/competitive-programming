#include <bits/stdc++.h>
using namespace std;
const int INF = (int)1e9;
void setmin(auto &x, const auto &y) {
    if (y < x) x = y;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные
    int n; cin >> n;
    string a, b; cin >> a >> b;
    // делим символы на группы симметричных (по 4 символа в группе)
    // пробуем различные замены для этой группы и анализируем результаты
    // учтите что можно заменять ТОЛЬКО СИМВОЛЫ СТРОКИ A
    // строка B неприкосновенна для замен, там можно только переставлять
    int64_t answer = 0;
    for (int i = 0, j = n-1; i < j; i++, j--) {
        // проще всего перебрать все различные замены и выбрать минимум
        // иначе придётся ифать все случаи и это трудно
        int currMinReplaces = INF;
        for (char newAi : {a[i], a[j], b[i], b[j]}) {
            for (char newAj : {a[i], a[j], b[i], b[j]}) {
                // количество выполненных замен
                int nReplaces = 0;
                nReplaces += (newAi != a[i]);
                nReplaces += (newAj != a[j]);
                // проверим, можно ли теперь переставить символы,
                // чтобы получить равенство
                map<char,int> count;
                count[newAi]++;
                count[newAj]++;
                count[b[i]]++;
                count[b[j]]++;
                if (count.size() == 1u) // 4 одинаковых символа
                    setmin(currMinReplaces, nReplaces);
                // 2 символа, количество каждого равно 2:
                if (count.size() == 2u && count.begin()->second == 2)
                    setmin(currMinReplaces, nReplaces);
            }
        }
        answer += currMinReplaces;
    }
    // случай нечётного n:
    if (n % 2 == 1 && a[n / 2] != b[n / 2])
        answer++; // одна замена, если середины не равны
    if (answer >= INF) // не получилось
        answer = -1;
    cout << answer << endl;
    return 0;
}