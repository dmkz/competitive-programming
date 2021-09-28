#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

int32_t main() {
  int tests;
  cin >> tests;
  for(int test = 0; test < tests; ++test) {
    int n, k, d;
    cin >> n >> k >> d;
    vector<int> arr(n);
    for(int i = 0; i < n; ++i) {
      cin >> arr[i];
    }

    vector<vector<int>> costs(d);
    for(int i = 0; i < n; ++i) {
      costs[i % d].push_back(arr[i]);
    }
    int ans = 0;
    for(int i = 0; i < d; ++i) {
      vector<int> ps(costs[i].size() + 1);
      partial_sum(costs[i].begin(), costs[i].end(), next(ps.begin()));
      auto get_sum = [&ps](int left, int right) {
        return ps[right] - ps[left];
      };
      for(int j = k; j <= (int)costs[i].size(); ++j) {
        ans = max(ans, get_sum(j - k, j));
      }
    }

    cout << ans << endl;
  }
}
