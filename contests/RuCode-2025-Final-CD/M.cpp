// Задача: M, Вердикт: OK, Время: 0.006 сек, Память: 2.4 MB

// Идея: будем работать с остатками по модулю 60. Нужно добиться остатка равного 0.
// добавляя букву в конец, остаток меняется по вормуле: (rem * 16 + newDigit) % 60.
// Добавляя в начало строки, нужно знать длину строки, тогда остаток меняется по
// формуле (rem + newDigit * 16^{len}) % 60.
// Ответ находится довольно быстро, потому что мы уже имеем какой-то остаток на
// отрезке [0, 59] и нам нужно его добить до 0, добавляя цифры 10-15.
// Для поиска оптимального ответа запустим алгоритм поиска в ширину. Переходы:
// добавления букв в начало или конец. Среди лучших по длине ответом найдём
// лексикографически минимальную строку и выведем её.

#include <bits/stdc++.h>
#define int int64_t
using namespace std;

// служебные функции для удобства при решении задачи:

// бинарное возведение в степень по модулю mod:
int modPow(int a, int n, int mod) {
    int r = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            r = r * a % mod;
        }
        a = a * a % mod;
        n >>= 1;
    }
    return r;
}

// получение значения цифры, записанной в 16-ричной системе:
int digit(char c) {
    assert('A' <= c && c <= 'F');
    return c - 'A' + 10;
}

// конвертация строки в пару (длина строки, остаток от деления на 60)
pair<int, int> convert(const string &s) {
    // возвращаем длину числа и остаток от деления на 60:
    const int n = (int)s.size();
    int rem = 0;
    for (auto c : s)
        rem = (rem * 16 + digit(c)) % 60;
    return make_pair(n, rem);
}

// преобразование массива, содержащего количество добавленных букв, в строку:
string arrToStr(const array<int, 6> &cnt) {
    string res;
    for (int i = 0; i < 6; i++)
        res += string(cnt[i], char('A' + i));
    if (res.empty())
        res = "OK";
    return res;
}

// решение задачи:
// запустим поиск в ширину, чтобы найти оптимальный способ дополнить исходную строку
// чтобы получить остаток 0. Так как нам нужно набрать разность от 0 до 59, нам не
// понадобится много букв, так как мы можем варьировать остаток, добавляя от 10 до 15
string solve(pair<int, int> start) {
    // в очереди храним: {{длину, остаток}, {количество добавленных букв A-F}}
    using State = pair<pair<int, int>, array<int, 6>>;
    queue<State> que;
    que.push(State{start, {0, 0, 0, 0, 0, 0}});
    int bestLen = INT_MAX;
    vector<string> answ;
    while (que.size()) {
        auto [curr, letters] = que.front();
        que.pop();
        const auto [len, rem] = curr;
        if (rem == 0) {
            // получили остаток равный 0. Обновим оптимальную длину ответа и
            // множество различных символов, которые его достигают:
            if (bestLen > len)
                bestLen = len;
            if (bestLen == len)
                answ.push_back(arrToStr(letters));
            continue;
        }
        // нет смысла обрабатывать варианты, которые превысили по длине
        // оптимальный ответ (по условию), пропускаем.
        if (len >= bestLen)
            continue;
        // переберём добавления букв в конец:
        for (int i = 0; i < 6; i++) {
            int d = 10 + i;
            int newRem = (rem * 16 + d) % 60;
            letters[i]++;
            que.push(State{{len+1, newRem}, letters});
            letters[i]--;
        }
        // переберём добавления букв в начало:
        for (int i = 0; i < 6; i++) {
            int d = 10 + i;
            int newRem = (modPow(16, len, 60) * d + rem) % 60;
            letters[i]++;
            que.push(State{{len+1, newRem}, letters});
            letters[i]--;
        }
    }
    // выводим лексикографический минимум:
    return *min_element(answ.begin(), answ.end());
}

string solve(const string &s) {
    return solve(convert(s));
}

main() {
    string s; cin >> s;
    cout << solve(s) << endl;
}
