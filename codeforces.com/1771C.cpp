/*
    Problem: 1771C. Hossam and Trainees
    Solution: factorization, primes, O(n sqrt(A) / log(A))
*/

#pragma GCC optimize("Ofast")
#pragma GCC target("fma")
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;

using pii = pair<int,int>;
using vpii = vector<pii>;

const int AMAX = (int)1e9;
const int PMAX = (int)sqrt(AMAX);

const auto primes = [](){
// находим список простых от 2 до sqrt(AMAX)
    vector<bool> isPrime(PMAX+1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= PMAX; i++)
        for (int j = i * i; j <= PMAX; j += i)
            isPrime[j] = false;
    vector<int> pr;
    for (int i = 2; i <= PMAX; i++)
        if (isPrime[i])
            pr.push_back(i);
    return pr;
}();

void factorize(int x, vpii& divs) {
    divs.clear();
    const int end = int(upper_bound(all(primes), sqrt(x)) - primes.begin());
    for (int id = 0; id < end; id++) {
        const int i = primes[id];
        if (int j = x / i; i * j == x) {
            int p = 0;
            do {
                p++;
                x = j;
                j = x / i;
            } while (j * i == x);
            if (divs.empty() || divs.back().first != i)
                divs.push_back({i, 0});
            if (divs.back().first == i)
                divs.back().second++;
        }
    }
    if (x > 1)
        divs.push_back({x,1});
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vpii divs;
    map<int,int> used;
    bool answ = false;
    for (auto &it : a) {
        cin >> it;
        factorize(it, divs);
        for (const auto &[p, _] : divs) {
            used[p]++;
            if (used[p] == 2)
                answ = true;
        }
    }
    cout << (answ ? "YES\n" : "NO\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}