#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
const int EMPTY = -1;
void part1() {
    int64_t answ{};
    string s;
    cin >> s;
    vector<int> v;
    int number = 0;
    for (int i = 0; i < isz(s); i++) {
        if (i % 2 == 0) {
            for (int cnt = s[i] - '0'; cnt --> 0; )
                v.push_back(number);
            number++;
        } else {
            for (int cnt = s[i] - '0'; cnt --> 0; )
                v.push_back(EMPTY);
        }
    }
    int firstEmpty = 0, lastNumber = isz(v)-1;
    while (true) {
        // находим первую пустую клетку:
        while (firstEmpty <= lastNumber && v[firstEmpty] != EMPTY)
            firstEmpty++;
        // находим самое правое число:
        while (firstEmpty <= lastNumber && v[lastNumber] == EMPTY)
            lastNumber--;
        if (firstEmpty > lastNumber) // пустые клетки закончились
            break;
        // ставим самое правое число на самую левую пустую клетку:
        swap(v[firstEmpty], v[lastNumber]);
    }
    for (int i = 0; i < isz(v); i++)
        if (v[i] != EMPTY)
            answ += i * 1LL * v[i];
    cout << answ << endl;
}
void part2() {
    int64_t answ{};
    string s;
    cin >> s;
    vector<int> v;
    int number = 0;
    for (int i = 0; i < isz(s); i++) {
        if (i % 2 == 0) {
            for (int cnt = s[i] - '0'; cnt --> 0; )
                v.push_back(number);
            number++;
        } else {
            for (int cnt = s[i] - '0'; cnt --> 0; )
                v.push_back(EMPTY);
        }
    }
    int lastBlockEnd = isz(v)-1;
    while (lastBlockEnd >= 0) {
        // ищем начало и конец блока, который будем сейчас двигать:
        while (lastBlockEnd >= 0 && v[lastBlockEnd] == EMPTY)
            lastBlockEnd--;
        int lastBlockStart = lastBlockEnd;
        while (lastBlockStart-1 >= 0 && v[lastBlockStart-1] == v[lastBlockEnd])
            lastBlockStart--;
        // считаем его длину:
        int lastBlockLen = lastBlockEnd - lastBlockStart + 1;
        // ищем первый подходящий для него слева пустой блок, куда мы сможем
        // его целиком поместить:
        int emptyBlockStart = 0;
        while (emptyBlockStart < lastBlockStart) {
            while (emptyBlockStart < lastBlockStart && v[emptyBlockStart] != EMPTY)
                emptyBlockStart++;
            int emptyBlockEnd = emptyBlockStart;
            while (emptyBlockEnd < lastBlockStart && v[emptyBlockEnd] == EMPTY)
                emptyBlockEnd++;
            int emptyBlockLen = emptyBlockEnd - emptyBlockStart;
            if (emptyBlockLen >= lastBlockLen) {
                // нашли пустой блок: перемещаем и завершаем поиск
                for (int i = 0; i < lastBlockLen; i++)
                    swap(v[emptyBlockStart+i], v[lastBlockStart+i]);
                break;
            } else {
                // этот блок не подошёл, значит смотрим дальше:
                emptyBlockStart = emptyBlockEnd;
            }
        }
        // независимо от того, был перемещен блок, или нет, переходим к
        // следующему непустому блоку:
        lastBlockEnd = lastBlockStart-1;
    }
    for (int i = 0; i < isz(v); i++)
        if (v[i] != EMPTY)
            answ += i * 1LL * v[i];
    cout << answ << endl;
}
main() {
    part2();
}

