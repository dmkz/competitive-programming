#include <bits/stdc++.h>
using namespace std;
int main() {
    size_t pf, pe, pd, total, pc = 1;
    cin >> pf >> pe >> pd >> total;
    if (total == 0) {
        cout << 'F';
    } else if (total >= 1 && total < pf + (pe+1)/2) {
        cout << "E";
    } else if (total == pf+(pe+1)/2) {
        cout << "D/E";
    } else if (total < pf+pe+(pd+1)/2) {
        cout << "D";
    } else if (total == pf+pe+(pd+1)/2) {
        cout << "C/D";
    } else if (total > pf+pe+(pd+1)/2 && total < pf+pe+pd+pc) {
        cout << "C";
    } else {
        cout << "Champ AB";
    }
}
