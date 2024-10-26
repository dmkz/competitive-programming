#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
void set_uniq(auto &s) { s.erase(unique(all(s)), s.end()); }
int getmask(int number) {
    int mask = 0;
    for (int i = 0; i < 5; i++) {
        int digit = number % 10;
        mask |= (1 << digit);
        number /= 10;
    }
    return mask;
}
void solve(int n, auto &out) {
    // делим номера на две группы: с повторяющимися цифрами и без них
    char buf[101];
    set<int> duplicates;
    set<int> uniqueNumbers[1 << 10]{};
    set<int> allUniqueNumbers;
    for (int number = 0; number <= 99999; number++) {
        sprintf(buf, "%05d", number);
        string s(buf);
        sort(all(s));
        set_uniq(s);
        if (s.size() == 5) { // уникальные номера
            uniqueNumbers[getmask(number)].insert(number);
            allUniqueNumbers.insert(number);
        } else
            duplicates.insert(number);
    }
    // берём сначала номера, которые имеют повторяющиеся цифры
    // набираем их группами по 10, увеличивая каждую цифру одновременно, пример:
    /*
        00123
        11234
        22345
        33456
        44567
        55678
        66789
        77890
        88901
        99012
    */
    //int n; cin >> n;
    while (n >= 10 && duplicates.size()) {
        int number = *duplicates.begin();
        sprintf(buf, "%05d", number);
        for (int cnt = 10; cnt --> 0; ) {
            out << buf << '\n';
            sscanf(buf, "%d", &number);
            duplicates.erase(number);
            for (int i = 0; i < 5; i++) {
                buf[i]++;
                if (buf[i] > '9')
                    buf[i] = '0';
            }
        }
        n -= 10;
    }
    // теперь выводим группами по 2 парами уникальный номер + его
    // оппонент, состоящий из противоположного набора цифр
    while (n > 0) {
        int number = *allUniqueNumbers.begin();
        sprintf(buf, "%05d", number);
        out << buf << '\n';
        allUniqueNumbers.erase(number);
        int mask = getmask(number);
        int opposite = ~mask & 1023;
        uniqueNumbers[mask].erase(number);
        n--;
        if (n > 0) {
            auto it = uniqueNumbers[opposite].begin();
            assert(it != uniqueNumbers[opposite].end());
            sprintf(buf, "%05d", *it);
            allUniqueNumbers.erase(*it);
            uniqueNumbers[opposite].erase(it);
            out << buf << '\n';
            n--;
        }
    }
}
main() {
    int n; cin >> n;
    solve(n, cout);
}
