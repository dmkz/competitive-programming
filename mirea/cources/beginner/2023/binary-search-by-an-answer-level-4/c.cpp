#include <bits/stdc++.h>

using namespace std;
const int INF = (int)1e9+1;
using vi = vector<int>;
using vvi = vector<vi>;

int wrap(const string& s, int begin, int after, int width) {
// функция формирует новую полосу объявления ширины width
// начиная с позиции begin и заканчивая позицией after в строке s
// Возвращает позицию в строке s, с которой нужно начинать следующую полосу
// объявления
    int last = -2;
    for (int i = begin; i < after; ++i) {
        if (i-begin >= width)
            return last+1;
        if (s[i] == '-')
            last = i;        
    }
    return after;
}

bool solve(const string& s, int limit, int width) {
    int n = (int)s.size();
    int p = 0, count = 0;
    do {
        // делим оставшуюся часть строки s на новую строку ширины width
        ++count;
        p = wrap(s, p, n, width);
        if (p == -1) // не смогли поделить
            return false;
    } while (p < n);
    return count <= limit;
}

main() {
    // читаем k из первой строки
    int k; char c; scanf("%d%c", &k, &c); assert(c == '\n');
    // читаем объявление из второй строки
    vector<char> buf(1+1000*1000,'?');
    scanf("%1000000[^\n]", &buf[0]);
    string s(&buf[0]);
    // сразу заменяем пробелы на тире:
    for (auto& it : s)
        if (it == ' ')
            it = '-';
    // теперь делаем бинарный поиск по ширине строки - по ответу
    int low = 0, high = (int)s.size();
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (solve(s, k, mid)) high = mid;
        else low = mid;
    }
    cout << high;
}
