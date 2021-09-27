// Решение: строки, O(n)
// Ссылка на сабмит: https://codeforces.com/group/LB1sSRhotq/contest/346286/submission/129986856
#include <bits/stdc++.h>
int main() {
    int tt; std::cin >> tt;
    while (tt --> 0) {
        // читаем для каждой буквы какой маской она задается:
        std::vector<std::string> mask(256);
        for (char c = 'a'; c <= 'z'; c++)
            std::cin >> mask[c];
        // читаем результат шифрования и оригинальную строку:
        std::string result,original;
        std::cin >> result >> original;
        // зашифруем оригинальную строку:
        std::string crypted;
        for (char c : original)
            crypted = crypted + mask[c];
        // сравним то, что получилось, с данным результатом шифрования и выведем ответ:
        std::cout << (crypted == result ? "Yes" : "No") << std::endl;
    }
}