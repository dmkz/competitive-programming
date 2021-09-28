#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

int32_t main() {
  int tests;
  cin >> tests;
  for(int test = 0; test < tests; ++test) {
    int n;
    cin >> n;
    double p0, p1, p2, p3;
    cin >> p0 >> p1 >> p2 >> p3;

    double ans = n * (p1 + 2 * p2 + 3 * p3);

    cout << fixed << setprecision(12);
    cout << ans << endl;
  }
}
