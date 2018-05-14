#include <bits/stdc++.h>

using namespace std;

int main() {
//    freopen("input.txt", "rt", stdin);
//    freopen("output.txt", "wt", stdout);
    
    string s; 
    cin >> s;
    
    function<void(int, int)> Reverse = [&](int L, int R) {
        for (int i = L, j = R; i < j; ++i, --j) {
            swap(s[i], s[j]);
        }
    };
    
    function<void(int, int, int)> ShiftLeft = [&](int L, int R, int K) {
        Reverse(L,   L+K-1);
        Reverse(L+K, R);
        Reverse(L,   R);
    };
    
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r, k;
        cin >> l >> r >> k;
        --l, --r;
        k %= (r-l+1);
        ShiftLeft(l, r, (r-l+1)-k);
    }
    
    cout << s;
    
    
    return 0;    
}