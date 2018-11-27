/*
    Problem: 27E. Number With The Given Amount Of Divisors
    
    Solution: number theory, brute force, O([log(n)]!)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

typedef long long ll;
const ll INF = (ll)1e18L+1;
const int primes[10] = {2,3,5,7,11,13,17,19,23,29};
ll pow[10][64], answ;

void brute(int pos, int max, int lim, int need, ll curr) {
    if (pos == lim) {
        if (need == 1) {
            answ = std::min(answ, curr);
        }
        return;
    }
    for (int i = max; i > 0; --i) {
        if (need % i == 0 && curr <= INF / pow[pos][i-1]) {
            brute(pos+1, i, lim, need / i, curr * pow[pos][i-1]);
        }
    }
}

int main() {
    std::fill(&pow[0][0], &pow[0][0]+61*10,INF);
    for (int i = 0; i < 10; ++i) {
        pow[i][0] = 1;
        for (int p = 1; pow[i][p-1] < INF / primes[i]; ++p) {
            pow[i][p] = pow[i][p-1] * primes[i];
        }
    }
    int need;
    while (std::cin >> need) {
        answ = INF;
        brute(0, 64, 10, need, 1);
        if (answ == INF) {
            answ = ll(1) << (need-1);
        }
        std::cout << answ << std::endl;
    }
    return 0;
}