#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define range(x,l,r) (x).begin()+(l),(x).begin()+(r)
using namespace std;
using vi = vector<int>;
string ask(vi a, vi b) {
    cout << "? " << isz(a) << "\n";
    for (auto it : a)
        cout << it << ' ';
    cout << '\n';
    for (auto it : b)
        cout << it << ' ';
    cout << endl;
    string res;
    cin >> res;
    return res;
}
main() {
    // делить пополам не получится, будет 10 запросов в худшем случае:
    // 1000->500->250->125->63->32->16->8->4->2->1
    
    // выделим три группы монет и сравним две из них
    // за два сравнения можем определить знак, например, сравниваем g1 и g2
    // если g1 > g2, то сравниваем g1 и g3. Если g1 > g3, то фальшивая монета в g1 и
    // она больше остальных монет, если g1 == g3, то фальшивая монета в g2 и она меньше остальных монет
    
    // когда мы знаем знак, то найти монету можно за log3 сравнений
    // в каждом сравнении мы делим на 3 группы примерно равные и сравниваем
    // две из них за 1 сравнение. Если они равны, то монета в третьей группе
    // иначе смотрим на знак и однозначно определяем в какой группе наша монета
    int n; cin >> n;
    vi candidates(n);
    for (int i = 0; i < n; i++)
        candidates[i] = i+1;
    const int UNDEF = -1, LESS = 0, GREATER = 1;
    int sign = UNDEF; // изначально знак не определён
    while (isz(candidates) >= 3) {
        n = isz(candidates);
        int m = n / 3;
        vi a(range(candidates, 0, m));
        vi b(range(candidates, m, 2*m));
        vi c(range(candidates, 2*m, n));
        string s = ask(a, b);
        if (s == "=") {
            // монета в 3-й группе, точно в группе "c"
            if (sign == UNDEF) {
                // мы можем определить знак, если монет хватает,
                // так как теперь знаем, что среди 2*m монет нет фальшивой
                if (2 * m >= isz(c)) {
                    vi temp(range(candidates,0,isz(c)));
                    s = ask(c, temp);
                    if (s == ">") sign = GREATER;
                    else if (s == "<") sign = LESS;
                    else assert(false);
                }
            }
            candidates = c;
        } else if (s == ">") {
            if (sign == GREATER) candidates = a;
            else if (sign == LESS) candidates = b;
            else {
                // надо определить знак
                vi temp(range(candidates,2*m,3*m));
                s = ask(a, temp);
                if (s == ">") {
                    sign = GREATER;
                    candidates = a;
                } else if (s == "=") {
                    sign = LESS;
                    candidates = b;
                } else {
                    // невозможный случай
                    assert(false);
                }
            }
        } else if (s == "<") {
            if (sign == GREATER) candidates = b;
            else if (sign == LESS) candidates = a;
            else {
                // надо определить знак
                vi temp(range(candidates,2*m,3*m));
                s = ask(a, temp);
                if (s == "<") {
                    sign = LESS;
                    candidates = a;
                } else if (s == "=") {
                    sign = GREATER;
                    candidates = b;
                } else {
                    // невозможный случай
                    assert(false);
                }
            }
        }
    }
    // осталось две или менее монет
    // также однозначно определён знак
    assert(sign != UNDEF);
    if (isz(candidates) == 2) {
        string s = ask({candidates[0]}, {candidates[1]});
        if (s == ">") {
            if (sign == LESS) candidates = {candidates[1]};
            else if (sign == GREATER) candidates = {candidates[0]};
            else assert(false);
        } else if (s == "<") {
            if (sign == LESS) candidates = {candidates[0]};
            else if (sign == GREATER) candidates = {candidates[1]};
            else assert(false);
        }
    }
    assert(isz(candidates) == 1);
    cout << "! " << candidates[0] << endl;
}
