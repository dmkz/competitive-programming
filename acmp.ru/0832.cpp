/*
    "Игра в фишки": исследование, O(n)
*/

#include <iostream>
#include <functional>
#include <cstdlib>
#include <cassert>

typedef long long ll;

bool fast(ll a, ll b, ll c) {
    if (a > b) {
        return fast(b, a, c);
    }
    if (a > c) {
        return fast(c, b, a);
    }
    if (b > c) {
        return fast(a, c, b);
    }
    assert(0 <= a && a <= b && b <= c);
    if (a == 0 && b == 0) {
        return c == 1;
    }
    if (a == 0) {
        return b % 2 || c % 2;
    }
    if (a % 2 != b % 2) {
        return true;
    }
    return a % 2 != c % 2 || b % 2 != c % 2;
}

void research() {
    const int NMAX = 60;
    static char answ[1+NMAX][1+NMAX][1+NMAX];
    for (int i = 0; i <= NMAX; ++i) {
        for (int j = 0; j <= NMAX; ++j) {
            for (int k = 0; k <= NMAX; ++k) {
                answ[i][j][k] = -1;
            }
        }
    }
    answ[0][0][0] = 0;
    answ[1][0][0] = 1;
    answ[0][1][0] = 1;
    answ[0][0][1] = 1;
    for (int a = 0; a <= NMAX / 3; ++a) {
        for (int b = 0; b <= NMAX / 3; ++b) {
            for (int c = 0; c <= NMAX / 3; ++c) {                
                std::function<int(int,int,int)> get = [&](const int a, const int b, const int c) {
                    if (a < 0 || b < 0 || c < 0) {
                        return 0;
                    }
                    if (answ[a][b][c] == -1) {
                        answ[a][b][c] = get(a-1, b+1, c-1) || get(a-1,b-1,c+1) || get(a+1,b-1,c-1);
                    }
                    return (int)answ[a][b][c];
                };
                answ[a][b][c] = get(a,b,c);
                
                if (answ[a][b][c] != fast(a,b,c)) {
                    printf("a=%d, b=%d, c=%d: %s\n", a,b,c, answ[a][b][c] ? "YES":"NO");
                }
            }
        }
    }
    std::exit(0);
}

int main() {
    //research();
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nQ;
    std::cin >> nQ;
    while (nQ--) {
        ll a, b, c;
        std::cin >> a >> b >> c;
        std::cout << (fast(a,b,c) ? "Yes\n" : "No\n");
    }
    return 0;
}