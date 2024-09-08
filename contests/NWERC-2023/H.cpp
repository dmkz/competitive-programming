#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using vi = std::vector<int>;
std::string concat(const std::multiset<std::pair<int, std::string>> &expr)
{
    std::string result;
    bool first = true;
    for (const auto &[v, e] : expr) {
        if (!first)
            result += '*';
        first = false;
        result += e;
    }
    return result;
}

// 1 1 1 2 2
// перебираем сколько троек делаем из единиц
// перебираем сколько двоек делаем из единиц
// оставшиемся прибавляем к остальным минимумам

std::string solve(vi aa)
{
    // считаем число единиц
    std::multiset<std::pair<int, std::string>> expr;
    std::sort(all(aa), std::greater<>());
    int n1 = 0;
    while (isz(aa) > 0 && aa.back() == 1) {
        n1++;
        aa.pop_back();
    }
    // остальные элементы загоняем в мультисет
    for (int i = 0; i < isz(aa); i++) {
        expr.insert({aa[i], std::to_string(aa[i])});
    }
    // Шаг 1. Ко всем двойкам добавить единицы:
    while (isz(expr) && expr.begin()->first == 2 && n1 > 0) {
        auto [val1, expr1] = *expr.begin();
        expr.erase(expr.begin());
        val1 += 1;
        expr1 = "((" + expr1 + ")+1)";
        n1--;
        expr.insert({val1, expr1});
    }
    // дальше в зависимости от остатка от деления на 3 мы кидаем единицы к другим числам
    if (n1 % 3 == 0) {
        // объединяем все единицы в тройки (1+1+1)
        for (int i = 0; i < n1 / 3; i++)
            expr.insert({3, "(1+1+1)"});
        return concat(expr);
    } else if (n1 % 3 == 1) {
        if (isz(expr) && (expr.begin()->first <= 3 || n1 / 3 == 0)) {
            // кидаем единственную единицу к минимальному текущему числу
            auto [val1, expr1] = *expr.begin();
            expr.erase(expr.begin());
            val1 += 1;
            expr1 = "((" + expr1 + ")+1)";
            expr.insert({val1, expr1});
            // остальные единицы объединяем в тройки (1+1+1)
            for (int i = 0; i < n1 / 3; i++)
                expr.insert({3, "(1+1+1)"});
        } else {
            // остальные единицы объединяем в тройки (1+1+1)
            for (int i = 0; i < n1 / 3; i++)
                expr.insert({3, "(1+1+1)"});
            if (expr.size()) {
                // кидаем единицу к минимуму
                auto [val1, expr1] = *expr.begin();
                expr.erase(expr.begin());
                val1 += 1;
                expr1 = "((" + expr1 + ")+1)";
                expr.insert({val1, expr1});
            } else {
                // просто кидаем единицу
                expr.insert({1, "1"});
            }
        }
        return concat(expr);
    } else {
        assert(n1 % 3 == 2);
        // формируем максимальное количество троек (1+1+1)
        for (int i = 0; i < n1 / 3; i++)
            expr.insert({3,"(1+1+1)"});
        
        if (isz(expr) >= 2 && expr.begin()->first == 2 &&
            std::next(expr.begin())->first <= 3)
        {
            // кидаем единицы в два минимума
            auto [val1, expr1] = *expr.begin();
            expr.erase(expr.begin());
            auto [val2, expr2] = *expr.begin();
            expr.erase(expr.begin());
            val1 += 1;
            expr1 = "((" + expr1 + ")+1)";
            val2 += 1;
            expr2 = "((" + expr2 + ")+1)";
            expr.insert({val1, expr1});
            expr.insert({val2, expr2});
        } else {
            // объединяем единицы друг с другом
            expr.insert({2, "(1+1)"});
        }
        return concat(expr);
    }
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n; std::cin >> n;
    vi a(n);
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    auto res = solve(a);
    std::cout << res << std::endl;
}
