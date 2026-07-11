#include <iostream>
#include <set>
#include <vector>
using namespace std;

void print(const string &name, const auto &a) {
    cout << name << " = {";
    int i = 0;
    for (int x : a) {
        if (i > 0) cout << ',';
        cout << x;
        i++;
    }
    cout << "}" << '\n';
}

int main() {
    vector<int> a = {5, 2, 5, 7, 5, 2};

    set<int> s;
    multiset<int> ms;
    for (int x : a) {
        s.insert(x);
        ms.insert(x);
    }

    // set оставляет только различные значения.
    // multiset хранит все копии одинаковых значений.
    print("set", s);
    print("multiset", ms);
    cout << "set.size() = " << s.size() << '\n';
    cout << "multiset.size() = " << ms.size() << '\n';
    cout << "multiset.count(5) = " << ms.count(5) << '\n';

    // erase(value) удаляет все копии значения.
    ms.erase(5);
    print("after ms.erase(5)", ms);

    // Восстановим multiset и удалим только одну копию через итератор.
    ms = {5, 2, 5, 7, 5, 2};
    auto it = ms.find(5);
    if (it != ms.end()) {
        ms.erase(it);
    }
    print("after erase(it)", ms);
}
