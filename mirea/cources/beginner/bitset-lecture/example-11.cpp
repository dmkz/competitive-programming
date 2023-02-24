#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>

using namespace std;

#define watch(x) cout << (x) << " <-- " << #x << endl

int main()
{
    const int s = (int)1e6;
    int k; cin >> k;
    bitset<s> a(1);
    for (int i = 0; i < k; i++) {
        int w; cin >> w;
        a |= (a << w);
    }
    
    cout << a.count() << endl;
    
    int i = a._Find_first();
    while (i < a.size()) {
        cout << i << ' ';
        i = a._Find_next(i);
    }
    cout << endl;
}