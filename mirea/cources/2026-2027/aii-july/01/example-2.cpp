// Example 2
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Создаём пустой вектор из целых чисел
    vector<int> a;
    // Читаем размер вектора
    int n;
    cin >> n;
    // Читаем его элементы и добавляем их в конец:
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a.push_back(x);
    }
    // Выводим содержимое вектора на экран в обратном порядке:
    for (int i = n-1; i >= 0; i--)
        cout << a[i] << ' ';
    cout << endl;
}
