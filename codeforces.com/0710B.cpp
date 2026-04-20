// сортировки, конструктив, медиана, O(n log(n))
#include <bits/stdc++.h>
using namespace std;
main() {
    int n; cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++)
        cin >> x[i];
    sort(x.begin(), x.end());
    cout << x[(n-1)/2] << endl;
}