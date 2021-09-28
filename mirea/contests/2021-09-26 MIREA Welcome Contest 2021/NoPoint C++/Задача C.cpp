#include <bits/stdc++.h>
using namespace std;

int main() {
  int tests;
  cin >> tests;
  for(int test = 0; test < tests; ++test) {
    long long n, l, r;
    cin >> n >> l >> r;
    long long min = (l + n - 1) / n;
    long long max = (r + n - 1) / n;
    long long ans = max - min;
    cout << ans << endl;
  }
}
