#include <iostream>
#include <map>
#include <vector>
using namespace std;

void print(const string &name, const auto &mp) {
    cout << name << " = {";
    int i = 0;
    for (const auto &[key, value] : mp) {
        if (i > 0) cout << ", ";
        cout << key << ": " << value;
        i++;
    }
    cout << "}" << '\n';
}

int main() {
    vector<int> a = {6, 1, 1, 7, 7, 5, 4, 4, 2};

    // Считаем частоты значений в массиве через map:
    map<int, int> cnt;
    for (int x : a) {
        cnt[x]++;
    }

    // Количество различных ключей.
    cout << cnt.size() << '\n';

    // Вывод всех пар ключ -> значение.
    print("cnt", cnt);

    // Поиск по ключу.
    for (int x : {7, 3}) {
        cout << "Find " << x << ": ";
        auto it = cnt.find(x);
        if (it == cnt.end()) {
            cout << "fail";
        } else {
            cout << "ok, value = " << it->second;
        }
        cout << ", count = " << cnt.count(x) << '\n';
    }

    // Удаление ключей.
    for (int x : {7, 3, 1, 7}) {
        cout << "Erase " << x << ": ";
        auto it = cnt.find(x);
        if (it == cnt.end()) {
            cout << "fail";
        } else {
            cout << "ok";
            cnt.erase(it);
        }
        print(", cnt", cnt);
    }

    return 0;
}