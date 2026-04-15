#include <bits/stdc++.h>
#define watch(x) false && cout << #x << " = " << (x) << endl
using namespace std;
int myGCD(int a, int b) {
    if (b == 0) return a;
    if (a < b) return myGCD(b, a);
    return myGCD(b, a % b);
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
    os << "{";
    for (size_t i = 0; i < vec.size(); i++) {
        if (i > 0)
            os << ", ";
        os << vec[i];
    }
    return os << "};";
}

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    watch(a);
    const int gsize = (int)sqrt(n/2.0);
    const int nGroups = (n+gsize-1)/gsize; // a/b = (a+b-1)/b = (int)ceil(a/b)
    watch(nGroups);
    watch(gsize);
    vector<int> g(nGroups, 0); // НОД(0, x) = x
    for (int i = 0; i < n; i++) {
        int gi = i / gsize;
        g[gi] = myGCD(g[gi], a[i]);
    }
    watch(g);
    // отвечаем на запросы:
    int q; cin >> q;
    //for (int i = 0; i < q; i++) {
    while (q --> 0) {
        char c; cin >> c;
        if (c == 'g') {
            // найти НОД
            int l, r; cin >> l >> r;
            l--, r--;
            //cout << "find gcd(" << l << ", " << r << ")" << endl;
            int gl = l / gsize, gr = r / gsize;
            int answ = 0;
            if (gl == gr) {
                for (int i = l; i <= r; i++) {
                    watch(i);
                    watch(answ);
                    watch(a[i]);
                    answ = myGCD(answ, a[i]);
                    watch(answ);
                }
            } else {
                // левая группа:
                for (int i = l; i <= (gl+1) * gsize - 1; i++)
                    answ = myGCD(answ, a[i]);
                // группы между ними
                for (int gi = gl + 1; gi < gr; gi++)
                    answ = myGCD(answ, g[gi]);
                // правая группа
                for (int i = gr * gsize; i <= r; i++)
                    answ = myGCD(answ, a[i]);
            }
            cout << answ << '\n';
        } else {
            assert(c == 'u');
            int i, x; cin >> i >> x;
            i--;
            a[i] = x;
            // с нуля пересчитывать НОД в этой группе
            int gi = i / gsize;
            g[gi] = x;
            for (int j = gi * gsize; j < min(n, (gi + 1) * gsize); j++)
                g[gi] = myGCD(g[gi], a[j]);
        }
    }
}
