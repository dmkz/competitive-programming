#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Читаем размер вектора
    int n;
    cin >> n;
    // Создаём вектор из n чисел
    vector<int> a(n);
    // Читаем его содержимое:
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // Выводим содержимое вектора на экран:
    for (int i = n-1; i >= 0; i--)
        cout << a[i] << ' ';
    cout << endl;
}
