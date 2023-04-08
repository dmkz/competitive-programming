//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
const int mod = (int)1e9+7;
// 500 500, 20k: 904795293
// 500 500,  1k: 904795293
void addTo(int &x, const int y) {
    x += y;
    if(x >= mod) x -= mod;
}
int main() { 
    int n, m; std::cin >> n >> m;
    // нужно знать три слоя динамики
    const int zero = (n+m)*2;
    //std::vector dp[4]; std::vector(2*zero+1, 0));
    int dp[4][2*zero+1]{};
    dp[0][zero] = 1;
    auto valid = [&](int row, int col){
        return row <= zero && row >= -zero;
    };
    auto get = [&](int row, int col) -> int& {
        return dp[(row+col)%4][row+zero];
    };
    auto addto = [&](int r1, int c1, int r2, int c2) {
        addTo(get(r1,c1),get(r2,c2));
    };
    auto addto3 = [&](int r1, int c1, int x) {
        addTo(get(r1,c1),x);
    };
    std::vector<int> min1(n+m+1), max1(n+m+1);
    std::vector<int> min2(n+m+1), max2(n+m+1);
    min1[0] = max1[0] = 0;
    for (int diag = 1; diag <= n + m; diag++) {
        min1[diag] = min1[diag-1]-1;
        max1[diag] = max1[diag-1]+2;
    }
    min2[n+m] = max2[n+m] = n;
    for (int diag = n+m-1; diag >= 0; diag--) {
        min2[diag] = min2[diag+1]-2;
        max2[diag] = max2[diag+1]+1;
    }
    for (int diag = 0; diag < n + m; diag++) {
        const int min = std::max(min1[diag],min2[diag]);
        const int max = std::min(max1[diag],max2[diag]);
        for (int row = min; row <= max; row++) {
            int col = diag - row;
            int x = dp[diag%4][row+zero];//get(row,col);
            //get(row,col) = 0;
            dp[diag%4][row+zero] = 0;
            //if(valid(row+2,col-1))
                addto3(row+2,col-1,x);
            //if(valid(row+2,col+1))
                addto3(row+2,col+1,x);
            //if(valid(row+1,col+2))
                addto3(row+1,col+2,x);
            //if(valid(row-1,col+2))
                addto3(row-1,col+2,x);
            //get(row,col) = 0;
        }
        //std::fill(all(dp[diag%4]), Int(0));
    }
    std::cout << get(n,m) << '\n';
}
