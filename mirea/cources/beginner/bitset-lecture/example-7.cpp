#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>

using namespace std;

#define watch(x) cout << (x) << " <-- " << #x << endl

int main()
{
    const int n = (int)1e8;
    bitset<n> a;
    a.set();
    a.reset(0);
    a.reset(1);
    for (int x = 2; x * x < n; x++)
        if (a[x])
            for (int y = x * x; y < n; y += x)
                a.reset(y);
    cout << a.count() << endl;
    
}