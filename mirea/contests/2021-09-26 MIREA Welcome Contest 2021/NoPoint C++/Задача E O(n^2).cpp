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
    vector<int> arr(n);
    for(int i = 0; i < n; ++i) {
      cin >> arr[i];
    }

    int ans = 3e18;
    for(int split = 1; split < n; ++split) {
      int one = arr[split - 1];
      int other = arr[split];
      int p1 = split - 2;
      int p2 = split + 1;
      ans = min(ans, abs(one - other));
      while(true) {
        if (one < other) {
          if (p1 >= 0) {
            one += arr[p1--];
          } else {
            break;
          }
        } else {
          if (p2 < n) {
            other += arr[p2++];
          } else {
            break;
          }
        }
        ans = std::min(ans, abs(one - other));
      }
    }
    cout << ans << endl;
  }
}
