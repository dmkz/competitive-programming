#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int64_t n, nSteps, need;
    cin >> n >> nSteps >> need;
    
    if (nSteps > need || nSteps * (n-1) < need) {
        cout << "NO";
        return 0;
    }
    
    cout << "YES\n";
    int64_t pos = 1, currStep = n-1;
    while (nSteps--) {
        // будем стараться делать такой прыжок, чтобы остаток потом
        // допрыгать единичными прыжками
        
        // уменьшаем текущий прыжок, пока он слишком большой, иначе,
        // если сделаем огромный прыжок, то не сможем допрыгать потом
        // даже единичными прыжками. Критерий выхода: nSteps > need
        while (need - currStep < nSteps) --currStep;
        
        // прыгаем на currStep вправо или влево (куда можем)
        if (pos + currStep <= n) {
            pos += currStep;            
        } else {
            assert(pos - currStep >= 1);
            pos -= currStep;
        }
        cout << pos << ' ';
        need -= currStep;
    }    
    return 0;
}