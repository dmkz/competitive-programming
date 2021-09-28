#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

vector<vector<vector<bool>>> precalc(int max_prod) {
  const vector<int> SHIFTS = {2, 3, 5};
  const int MOVES = (int)SHIFTS.size();
  vector<vector<vector<bool>>> dp(MOVES, vector<vector<bool>>(max_prod));
  for(int i = 0; i < max_prod; ++i) {
    int cols = max_prod / (i + 1);
    for(int k = 0; k < MOVES; ++k) {
      dp[k][i].resize(cols, false);
    }
  }

  for(int i = 0; i < max_prod; ++i) {
    for(int j = 0; j < (int)dp[0][i].size(); ++j) {
      for(int k = 0; k < MOVES; ++k) {
        int prev_i = i - SHIFTS[k];
        if(prev_i >= 0 && dp[(k + 1) % MOVES][prev_i][j] == false)
          dp[k][i][j] = true;
        int prev_j = j - SHIFTS[k];
        if(prev_j >= 0 && dp[(k + 1) % MOVES][i][prev_j] == false)
          dp[k][i][j] = true;
      }
    }
  }

  return dp;
}

int32_t main() {
  int queries;
  cin >> queries;
  vector<pair<int, int>> tests(queries);
  int max_prod = 0;
  for(int query = 0; query < queries; ++query) {
    auto &[n, m] = tests[query];
    cin >> n >> m;
    max_prod = max(max_prod, n * m);
  }
  vector<vector<vector<bool>>> dp = precalc(max_prod);
  for(auto &[n, m] : tests) {
    cout << (dp[0][n - 1][m - 1] ? "Alice" : "Bob") << endl;
  }
}
