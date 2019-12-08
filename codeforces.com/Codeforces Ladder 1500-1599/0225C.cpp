/*
    Problem: 225C. Barcode
    Solution: dynamic programming, matrices
*/
#pragma GCC optimize ("O3")
#include <iostream>
#include <algorithm>
#include <vector>

int main() {    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nRows, n, x, y;
    std::cin >> nRows >> n >> x >> y;
    
    static int countBlack[1000+1];
    for (int i = 0; i < nRows; ++i) {
        std::string s; std::cin >> s;
        for (int j = 0; j < n; ++j) {
            countBlack[j] += (s[j] == '#');
        }
    }
    static int sum[1000+1];
    for (int i = n-1; i >= 0; --i) {
        sum[i] += sum[i+1] + countBlack[i];
    }
    
    const int INF = nRows * n+1;
    int answ = INF;
    
    {
        // Динамика по группам - первая группа белого цвета.
        std::vector<int> curr(1+n,INF), prev(1+n,INF);
        prev[0] = 0;
        
        for (int g = 1; g <= n; ++g) {
            std::fill(curr.begin(), curr.end(), INF);
            for (int i = g * x,lim = std::min(g*y,n); i <= lim; ++i) { // позиция конца текущей группы
                for (int s = std::min(i,y); s >= x; --s) {
                    int temp = prev[i-s] + ((g & 1) ? (nRows * s -(sum[i-s]-sum[i])) : (sum[i-s]-sum[i]));
                    if (curr[i] > temp) curr[i] = temp;
                }
            }
            answ = std::min(answ, curr.back());
            prev.swap(curr);
        }
    }
    {
        // Динамика по группам - первая группа черного цвета.
        std::vector<int> curr(1+n,INF), prev(1+n,INF);
        prev[0] = 0;
        
        for (int g = 1; g <= n; ++g) {
            std::fill(curr.begin(), curr.end(), INF);
            for (int i = g * x, lim = std::min(g*y,n); i <= lim; ++i) { // позиция конца текущей группы
                for (int s = std::min(i,y); s >= x; --s) {
                    int temp = prev[i-s] + ((g & 1) ? sum[i-s]-sum[i] : nRows * s -(sum[i-s]-sum[i]));
                    if (curr[i] > temp) curr[i] = temp;
                }
            }
            answ = std::min(answ, curr.back());
            prev.swap(curr);
        }
    }
    
    std::cout << answ << std::endl;
    
    return 0;
}