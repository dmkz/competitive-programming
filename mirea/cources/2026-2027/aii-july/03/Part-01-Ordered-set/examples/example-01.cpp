#include <iostream>
#include <vector>
#include <set>

using namespace std;

void print(const string &name, const auto &s) {
    cout << name << " = {";
    int i = 0;
    for (const auto &item : s) {
        if (i > 0) cout << ',';
        cout << item;
        i++;
    }
    cout << '}' << endl;
}

int main() {
    vector<int> a = {6, 1, 1, 7, 7, 5, 4, 4, 2};

    // вставка элементов в set:
    set<int> s;
    for (int i = 0; i < a.size(); i++)
        s.insert(a[i]);

    // количество уникальных элементов:
    cout << s.size() << '\n';

    // вывод элементов на экран:
    print("s", s);

    // поиск и удаление элементов:
    for (int i = 0; i < a.size(); i++) {
        cout << "Delete " << a[i] << ": ";
        auto iter = s.find(a[i]);
        if (iter == s.end()) {
            cout << "fail";
        } else {
            cout << "ok";
            s.erase(iter);
        }
        print(", s", s);
    }

    return 0;
}