#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using vs = std::vector<std::string>;
void reuniq(auto &v) { v.erase(std::unique(all(v)), v.end()); }
// есть ровно 8 правильных квадратов. Вот они:
const vs res = {
    "294753618",
    "492357816",
    
    "276951438",
    "672159834",
    
    "438951276",
    "834159672",
    
    "816357492",
    "618753294",
};
// это алгоритм полного перебора, который находит список всех правильных квадратов выше:
void research() {
    for (int d11 = 1; d11 <= 9; d11++)
        for (int d12 = 1; d12 <= 9; d12++)
            for (int d21 = 1; d21 <= 9; d21++) {
                int d13 = 15 - d11 - d12;
                int d31 = 15 - d21 - d11;
                int d22 = 15 - d13 - d31;
                int d33 = 15 - d11 - d22;
                int d32 = 15 - d31 - d33;
                int d23 = 15 - d13 - d33;
                if (d11 + d12 + d13 == 15 &&
                    d21 + d22 + d23 == 15 &&
                    d31 + d32 + d33 == 15 &&
                    d11 + d21 + d31 == 15 &&
                    d12 + d22 + d32 == 15 &&
                    d13 + d23 + d33 == 15 &&
                    d11 + d22 + d33 == 15 &&
                    d13 + d22 + d31 == 15)
                {
                    std::string s;
                    s += char('0' + d11);
                    s += char('0' + d12);
                    s += char('0' + d13);
                    s += char('0' + d21);
                    s += char('0' + d22);
                    s += char('0' + d23);
                    s += char('0' + d31);
                    s += char('0' + d32);
                    s += char('0' + d33);
                    std::string t = s;
                    std::sort(all(t));
                    reuniq(t);
                    bool ok = (t.size() == 9);
                    for (char it : t)
                        ok &= ('1' <= it && it <= '9');
                    if (ok)
                        std::cout << s << std::endl;
                }
            }
}

// функция, которая спрашивает систему и получает от неё ответ:
int ask(int r, int c) {
    assert(1 <= r && r <= 3);
    assert(1 <= c && c <= 3);
    std::cout << r << " " << c << std::endl;
    int digit; std::cin >> digit;
    return digit;
}

// функция, в которой мы отгадываем квадрат:
void play() {
    // сначала спрашиваем цифру в клетке (3, 2)
    int d32 = ask(3, 2);
    // определяем, соврали нам или нет
    // в клетке (3, 2) должны быть только нечётные цифры. Соврали, если цифра чётная
    bool wasFail = (d32 % 2 == 0);
    // находим кандидатов на ответ: квадраты, которые удовлетворяют первому нашему запросу
    vs cand;
    for (const auto &s : res) {
        if (!wasFail) {
            if (s[7] == char('0' + d32)) {
                cand.push_back(s);
            }
        } else {
            char want = char('0' + d32);
            if (std::abs(s[7] - want) <= 1)
                cand.push_back(s);
        }
    }
    // теперь вторым запросом мы должны сделать так, чтобы ответ был единственным
    if (wasFail) {
        // нам соврали, значит вторым запросом точно скажут правду
        // найдём столбец, в котором у кандидатов все цифры уникальные, и спросим его:
        int cell = -1;
        for (int i = 0; i < 9; i++) {
            if (i == 7) continue;
            std::string alp;
            for (const auto &s : cand)
                alp += s[i];
            std::sort(all(alp));
            reuniq(alp);
            if (isz(alp) == isz(cand)) {
                // все цифры уникальные, будем спрашивать его
                cell = i;
                break;
            }
        }
        assert(cell != -1);
        // спрашиваем:
        int temp = ask(cell / 3 + 1, cell % 3 + 1);
        // находим ответ среди кандидатов, который удовлетворяет второму запросу:
        char digit = char('0' + temp);
        std::string answ;
        for (const auto &s : cand)
            if (s[cell] == digit) {
                answ = s;
                break;
            }
        assert(answ.size() == 9);
        // выводим ответ:
        std::cout << answ << std::endl;
    } else {
        // здесь нам изначально сказали правду
        // значит могут соврать вторым запросом
        // поэтому ищем столбец в котором кандидаты отличаются более чем на 2
        // чтобы даже в случае вранья мы определили ответ однозначно
        int cell = -1;
        for (int i = 0; i < 9; i++) {
            if (i == 7) continue;
            std::string alp;
            for (const auto &s : cand)
                alp += s[i];
            std::sort(all(alp));
            reuniq(alp);
            if (isz(alp) == isz(cand)) {
                // в текущем столбце все цифры уникальные, смотрим их попарное расстояние:
                bool ok = true;
                for (int j = 0; j < isz(alp); j++)
                    for (int k = j+1; k < isz(alp); k++) {
                        int dist = std::abs(alp[j] - alp[k]);
                        // оно должно быть > 2 для всех цифр в столбце
                        ok &= (dist > 2);
                    }
                if (ok) {
                    // норм, столбец нам подходит
                    cell = i;
                    break;
                }
            }
        }
        assert(cell != -1);
        // спрашиваем цифру в выбранном столбце
        int temp = ask(cell / 3 + 1, cell % 3 + 1);
        // однозначно определяем ответ - какой из кандидатов подходит ко второму запросу
        char digit = char('0' + temp);
        std::string answ;
        for (const auto &s : cand)
            if (std::abs(s[cell] - digit) <= 1) {
                answ = s;
                break;
            }
        // выводим ответ
        assert(answ.size() == 9);
        std::cout << answ << std::endl;
    }
}   


main() {
    play();
}
