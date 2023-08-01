#include <bits/stdc++.h>
int main() {
    // чтение матриц a и b:
    int n,m; std::cin >> n >> m;
    std::vector<std::string> a(n), b(m);
    for (auto &row : a) std::cin >> row;
    for (auto &row : b) std::cin >> row;
    bool answ = 0;
    for (int startRow = 0; startRow + m - 1 < n; startRow++) {
        for (int startCol = 0; startCol + m - 1 < n; startCol++) {
            // Переберем координаты левого верхнего угла вхождения
            // Проверим явно, равна ли перебираемая подматрица матрице b
            bool curr = 1;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) {
                    curr &= (a[startRow+i][startCol+j] == b[i][j]);
                }
            }
            answ |= curr;
        }
    }
    std::cout << (answ ? "yes" : "no") << std::endl;
    return 0;
}