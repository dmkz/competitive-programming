#include <bits/stdc++.h>
using namespace std;
int main() {
    int nPar, nChild;
    while (cin >> nPar >> nChild) {
        int answ = 0;
        while (nPar > 0 || nChild > 0) {
            // каждый раз мы отправляем либо 4 взрослых + 3 ребёнка
            // либо 3 взрослых + 4 ребёнка
            // выберем оптимальный вариант на основе того, кого больше:
            // детей или взрослых прямо сейчас
            answ++; // надо будет сгонять туда
            // берём 4 взрослых и 3 ребёнка сначала:
            int deltaP = min(nPar, 4);
            int deltaC = min(nChild, 3 + (deltaP < 4));
            if (deltaP == 4 && deltaC == 3) {
                // меняем на 3 взрослых и 4 ребёнка, если детей больше:
                if (nChild > nPar && nChild >= 4)
                    swap(deltaP, deltaC);
            }
            // отправляем:
            nPar -= deltaP;
            nChild -= deltaC;
            // возвращаемся если кто-то остался неотправленный:
            if (nPar > 0 || nChild > 0)
                answ++;
        }
        cout << answ << endl;
    }
}
