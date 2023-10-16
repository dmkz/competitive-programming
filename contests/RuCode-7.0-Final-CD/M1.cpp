#include <bits/stdc++.h>
using namespace std;
int main() {
    int l, r;
    cin >> l >> r;
    if (r-l==0) cout << l;
    else if (r-l==1) cout << -1;
    else cout << r-1;
}
