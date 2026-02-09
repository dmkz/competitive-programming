// бинарный поиск, двумерные префикс-суммы, O(N^2 * log(N))
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
    cin.tie(0);
	// читаем данные и считаем двумерные префикс-суммы:
    int n; cin >> n;
    vector sum(1+n, vector(1+n, 0));
	for (int r = 1; r <= n; r++) {
		string s; cin >> s;
		for (int c = 1; c <= n; c++)
			sum[r][c] = sum[r-1][c] + sum[r][c-1] - sum[r-1][c-1] + (s[c-1] == '1');
	}
    // функция для вычисления площади в прямоугольнике:
    auto square = [&](int r1, int c1, int r2, int c2) {
        return sum[r2][c2]-sum[r1-1][c2]-sum[r2][c1-1]+sum[r1-1][c1-1];
    };
    // функция для поиска квадрата с заданной стороной:
    auto findSquare = [&](int mid) -> bool {
        for (int r = 1; r + mid - 1 <= n; r++)
            for (int c = 1; c + mid - 1 <= n; c++)
                if (square(r, c, r+mid-1, c+mid-1) == mid * mid)
                    return true;
        return false;
    };
	// запускаем бинарный поиск по ответу:
	int low = 0, high = n+1;
	while (high - low > 1) {
		int mid = (high + low) / 2;
		if (findSquare(mid)) low = mid;
        else high = mid;
	}
	cout << low * low << endl;
}
