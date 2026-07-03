// Чтение и вывод массива в исходном порядке в C++

#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Чтение размера массива и его элементов
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Вывод элементов в исходном порядке
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}