#include <bits/stdc++.h>
using namespace std;
int main(){
    // будем читать элементы один за одним и добавлять их в конец вектора
    // будем вставлять 1 между соседними элементами, если их gcd не равен 1
    // используем функцию std::gcd из C++17, альтернатива __gcd из GCC
    vector<int> v;
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int item; cin >> item;
        // если gcd с предыдущим добавленным не единица, то добавляем 1:
        if (!v.empty() && gcd(v.back(),item) != 1)
            v.push_back(1);
        // добавляем текущий элемент:
        v.push_back(item);
    }
    // выводим количество добавленных элементов и элементы нового вектора:
    cout << v.size() - n << '\n';
    for (auto it : v) cout << it << ' ';
    return 0;
}