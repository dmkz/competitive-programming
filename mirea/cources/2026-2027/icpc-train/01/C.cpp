#include <bits/stdc++.h>
#include <bits/extc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
using ll = long long;
void solve() {
    int a, b, c, k;
    cin >> a >> b >> c >> k;
    int n = a + b + c;
    // нужно определить, можно ли, чередуя группы из одинаковых букв с длинами len[i], получить:
    // sum(len[i]-1) = k => n - nGroups = k => nGroups = n - k. То есть, мы знаем количество групп.
    int nGroups = n - k;
    // попробуем сначала получить максимальное количество групп, затем объединить некоторые группы в одну
    // первую группу нам нужно построить аналитически: берём букву с максимальным количеством
    vector<pair<int,char>> rem{{a,'A'},{b,'B'},{c,'C'}};
    sort(rem.begin(), rem.end(), greater<>());
    int mx = rem[0].first;
    int sum = rem[1].first + rem[2].first;
    // чтобы суметь разделить, нам нужно сделать mx <= sum
    vector<pair<int,char>> answ;
    if (int delta = mx - sum; delta > 0) {
        answ.emplace_back(delta, rem[0].second);
        rem[0].first -= delta;
    }
    // теперь первая группа построена. для каждой следующей группы отделяем один символ
    // с максимальным количеством и ставим группу с одним элементом:
    while (true) {
        sort(rem.begin(), rem.end(), greater<>());
        bool was = false;
        for (auto &[cnt, letter] : rem)
            if (cnt > 0 && (answ.empty() || answ.back().second != letter)) {
                answ.emplace_back(1, letter);
                cnt--;
                was = true;
                break;
            }
        if (!was) break;
    }
    if (isz(answ) < nGroups) {
        cout << "NO\n";
        return;
    }
    // теперь нужно уменьшать количество групп, объединяя похожие. сохраняем номера групп для каждой буквы
    reverse(all(answ));
    map<char, vector<int>> ids;
    for (int i = 0; const auto &[cnt, letter] : answ) {
        ids[letter].push_back(i);
        i++;
    }
    // объединяем группы, отделяя последнюю и сливая её с любой другой группой той же буквы
    while (isz(answ) > nGroups) {
        // берём последнюю группу и сливаем её
        if (ids[answ.back().second].size() == 1) {
            // но если не можем слить, смотрим с другого конца
            reverse(all(answ));
            ids.clear();
            for (int i = 0; const auto &[cnt, letter] : answ)
                ids[letter].push_back(i++);
        }
        auto [lastCnt, lastLetter] = answ.back();
        answ.pop_back();
        ids[lastLetter].pop_back();
        if (ids[lastLetter].size()) {
            int i = ids[lastLetter].front();
            answ[i].first += lastCnt;
        } else {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    for (const auto &[cnt, letter] : answ)
        cout << string(cnt, letter);
    cout << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}