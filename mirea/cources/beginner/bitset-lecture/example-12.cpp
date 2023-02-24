#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>

using namespace std;

#define watch(x) cout << (x) << " <-- " << #x << endl
#define all(x) (x).begin(),(x).end()
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        bitset<9> r, l;
        // посчитаем r для нулевого
        for (int i = 0; i < s.size(); i++)
            r[i] = (s[i] == 'x');
        // считать количество пар:
        int64_t answ{};
        for (int i = 0; i < s.size(); i++) {
            l <<= 1;
            l[0] = (s[i] == 'x');
            cout << string(40,'-') << endl;
            watch(i);
            reverse(all(s));
            watch(s);
            reverse(all(s));
            watch(l);
            watch(r);
            if (s[i] == 'x')
                // вычитаем i == j == k
                answ += (l & r).count() - 1;
            r >>= 1;
        }
        cout << answ << '\n';
    }
}