#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
main() {
	int n, k; cin >> n >> k;
	// ways[i][j] хранит число путей после i шагов вниз и j шагов вправо.
	vector<vector<int>> ways(n + 1, vector<int>(k + 1));
	ways[0][0] = 1;
	// В каждую клетку приходим из клетки сверху или слева.
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= k; j++) {
			if (i == 0 && j == 0) continue;
			int fromTop = i == 0 ? 0 : ways[i - 1][j];
			int fromLeft = j == 0 ? 0 : ways[i][j - 1];
			ways[i][j] = (fromTop + fromLeft) % mod;
		}
	cout << ways[n][k] << '\n';
}