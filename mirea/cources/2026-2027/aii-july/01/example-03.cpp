// Чтение массива через push_back и вывод в обратном порядке в C++

#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Чтение размера массива
    int n;
    cin >> n;

    // Чтение элементов и добавление их в конец вектора
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    // Вывод элементов в обратном порядке
    for (int i = n - 1; i >= 0; i--) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}