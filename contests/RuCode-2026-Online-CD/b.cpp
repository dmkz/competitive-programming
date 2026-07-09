// конструктив, строки, математика
// Задача: B, Вердикт: OK, Время: 0.014 сек, Память: 2.2 МБ
#include <bits/stdc++.h>
#include <cassert>
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int q; std::cin >> q;
    while (q --> 0) {
        int t; std::cin >> t;
        if (t == 1) {
            int k; std::cin >> k;
            // III = 3, VIII = 8
            std::string s((k+1)/2, '9');
            if (k % 2 == 0) s.front() = '8';
            else s.front() = '3';
            std::cout << s << "\n";
        } else { assert((t == 2));
            std::string s;
            std::cin >> s;
            int k = int((s.size()-1)*2);
            if (s.front() <= '3') k++;
            else if (s.front() <= '8') k += 2;
            else k += 3;
            std::cout << k << "\n";
        }
    }
}
