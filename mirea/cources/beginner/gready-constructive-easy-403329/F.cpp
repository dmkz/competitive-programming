#include <bits/stdc++.h>
int main() {
    int n, r;
    std::cin >> n >> r;
    std::vector<int> a(n);
    for (auto &it : a) std::cin >> it;
    // заведём массив covered. covered[i] = 1 ==> i-й элемент покрыт обогревателем
    std::vector<int> covered(n);
    int answ = {0};
    for (int i = 0; i < n; i++) {
        // если уже покрыт, то ничего не делаем
        if (covered[i]) continue;
        // иначе надо найти самый дальний обогреватель справа от i,
        // который способен покрыть i-й элемент (входит в радиус его обогрева)
        int pos = -1;
        for (int j = i; j <= std::min(n-1,i + r - 1); j++) {
            if (a[j]) {
                pos = j;
            }
        }
        if (pos == -1) {
            // если справа от i нет обогревателя, способного его покрыть,
            // то ищем ближайший слева от i в радиусе обогрева
            for (int j = i; j >= std::max(0,i - r + 1); j--) {
                if (a[j]) {
                    pos = j;
                    break;
                }
            }
        }
        if (pos != -1) {
            // если обогреватель найден, то отметим, что он выбран, и ответим
            // что он обогревает все клетки в радиусе своего действия:
            // covered[j] := 1 если (abs(pos-j) <= r)
            for (int j = pos - r + 1; j <= pos + r - 1; j++) {
                if (0 <= j && j < n) {
                    covered[j] = 1;
                }
            }
            answ++;
        } else {
            // иначе не можем найти обогреватель (pos == -1). Хреново,
            // ответ равен -1
            answ = -1;
            break;
        }
    }
    std::cout << answ << '\n';
    return 0;
}