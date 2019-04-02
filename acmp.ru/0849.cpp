/*
    Задача: 849. Задача про ферзей
    
    Решение: конструктив, перебор, рекурсия, O(n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef std::pair<int,int> pii;
typedef std::vector<pii> vpii;

vpii greedy(const int n) {
    vpii answ;
    int row, col;
    for (row = 1, col = 2; col <= n; row++, col+=2) {
        answ.push_back(pii(row,col));
    }
    col = 1;
    while (row <= n) {
        answ.push_back(pii(row,col));
        row++; col += 2;
    }
    assert(isz(answ) == n);
    return answ;
}

vpii greedy2(const int n) {
    vpii answ;
    int row, col;
    for (row = 0, col = (n - 1) / 2; row < n / 2; ) {
        answ.push_back(pii(row+1,col+1));
        row++;
        col = (col + 2) % n;
    }
    for (row = n-1, col = n / 2; row >= n / 2; ) {
        answ.push_back(pii(row+1,col+1));
        row--;
        col -= 2;
        if (col < 0) {
            col += n;
        }
    }
    return answ;
}

vpii greedy3(int n) {
    vpii answ = greedy2(n / 2 * 2);
    if (n % 2 == 1) {
        answ.push_back(pii(n,n));
    }
    return answ;
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        if (n == 1) { std::cout << "1 1\n"; }
        else if (n <= 3) { std::cout << "No solution\n"; }
        else if (n % 6 != 2 && n % 6 != 3) {
            auto answ = greedy(n);
            for (auto it : answ) {
                assert(1 <= it.first && it.first <= n);
                assert(1 <= it.second && it.second <= n);
                std::cout << it.first << ' ' << it.second << "\n";
            }
        } else {
            auto answ = greedy3(n);
            for (auto it : answ) {
                assert(1 <= it.first && it.first <= n);
                assert(1 <= it.second && it.second <= n);
                std::cout << it.first << ' ' << it.second << "\n";
            }
        }
    }
    return 0;
}