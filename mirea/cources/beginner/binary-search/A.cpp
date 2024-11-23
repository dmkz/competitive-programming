#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
//  low = 1'999'999'998
// high = 2'000'000'000
// (low+high) > 2^31-1
main() {
    cin.tie(nullptr);
    int n; cin >> n;
    int low = 1, high = n+1;
    while (high - low > 1) {
        int mid = (low + high) / 2; // low + (high - low) / 2 = (2*low+high-low)/2
        cout << mid << endl;
        cout.flush();
        string s; cin >> s;
        if (s == ">=") low = mid;
        else high = mid;
    }
    cout << "! " << low << endl;
}
