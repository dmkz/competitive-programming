#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
void setmin(auto &x, const auto &y) { if (x > y) x = y; }
using namespace std;
using pii = pair<int,int>;
using vi = vector<int>;
pii calcBalance(const std::string &s) {
    // {минимальный префикс, суммарный баланс}
    int balance = 0, minBalance = 0;
    for (auto it : s) {
        balance += (it == '(' ? +1 : -1);
        setmin(minBalance, balance);
    }
    return {minBalance, balance};
}
using Item = pair<pii, int>;
vi solve(const auto &data)
{
    // сначала надо как можно больше набрать, а потом только сливать
    // делим строки в три группы: положительный баланс, нулевой и отрицательный
    int n = isz(data);
    vector<Item> plus, zero, minus;
    for (int i = 1; i <= n; i++) {
        string s = data[i-1];
        auto [m,b] = calcBalance(s);
        if (b < 0) minus.push_back({{m,b},i});
        else if (b > 0) plus.push_back({{m,b},i});
        else zero.push_back({{m,b},i});
    }
    // рассмотрим две проблемные строки
    // порядок ij: min(imin, ibal+jmin)
    // порядок ji: min(jmin, jbal+imin)
    // итоговый баланс будет одним и тем же
    // выберем такой порядок, в котором минимум как можно больше
    // посортим отдельно каждую группу, используя этот компаратор
    auto comp = [&](const auto &lhs, const auto &rhs) {
        auto [imin, ibal] = lhs.first;
        auto [jmin, jbal] = rhs.first;
        return min(imin, ibal+jmin) > min(jmin, jbal+imin);
    };
    stable_sort(all(plus), comp);
    stable_sort(all(zero), comp);
    stable_sort(all(minus), comp);
    // теперь формируем ответ + проверяем его на корректность
    vi answ;
    int balance{};
    bool ok = 1;
    for (auto vec : {&plus, &zero, &minus}) {
        for (const auto &[mb, id] : *vec) {
            auto [minBalance, bal] = mb;
            if (balance + minBalance >= 0) {
                balance += bal;
                answ.push_back(id);
            } else {
                ok = false;
            }
        }
    }
    ok &= (balance == 0);
    return ok ? answ : vi{};
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<string> data(n);
    for (auto &it : data)
        cin >> it;
    auto answ = solve(data);
    if (isz(answ)) {
        cout << "YES\n";
        for (auto it : answ)
            cout << it << ' ';
        cout << endl;
    } else
        cout << "NO\n";
}
