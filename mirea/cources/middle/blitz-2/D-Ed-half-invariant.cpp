//#pragma GCC optimize("Ofast,fast-math,unroll-loops")
//#pragma GCC target("avx2,bmi2")
#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <algorithm>
#include <string>
#include <set>
#include <bitset>
#include <time.h>
#include <cmath>
#include <iomanip>
#include <numeric>
#define F first
#define S second
#define pb push_back
#define ppb pop_back
#define all(x) x.begin(), x.end()

using namespace std;
using ld = long double;
using ll = long long;
using ull = unsigned long long;
using pll = pair <long, long>;
const ll mod = 998244353;
const ll mll = 1e18;
ostream &operator<<(ostream &os, __int128 x);

template <typename T>
istream& operator >> (istream & in, vector <T> &a);

template <typename T>
ostream& operator << (ostream & os, vector <T> &a);

void solve(){
    ll n;
    cin >> n;
    vector <ll> a(n);
    vector <ll> b(n);
    cin >> a >> b;
    ll a_sum = 0, b_sum = 0;
    for (int i=0; i<n; i++){
        a_sum+=a[i];
        b_sum+=b[i];
    }
    if (n==1){
        cout << max(-1ll, a[0]-b[0]);
        return;
    }
    if (n==2){
            if (a_sum==b_sum){
                ll k = abs(a[0]-b[0]);
                cout << max(0ll, a[0]-b[0]) << " " << max(0ll, a[1]-b[1]);
            }else{
                cout << -1;

            }
            return;
        }
    if (b_sum-a_sum<0 || (b_sum-a_sum)%(n-2)!=0) cout << -1;
    else{
        ll k = (b_sum-a_sum)/(n-2);
        bool f = 1;
        vector <ll> c(n);
        for (int i=0; i<n; i++){
            ll x = a[i]+k-b[i];
            if (x<0 || x>2*k || x%2!=0){
                f = 0;
                break;
            }
            c[i] = x/2;
        }
        if (f) cout << c;
        else cout << -1;
    }
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t=1;
    //cin >> t;
    while (t--){
        solve();
    }
}

ostream &operator<<(ostream &os, __int128 x) {
    bool sign = (x >= 0);
    if (x < 0) x = -x;
    ll high = ll(x / 1e18L);
    ll low = x - __int128(high) * 1e18L;
    if (!sign) {
        os << "-";
    }
    if (high) {
        os << high << setfill('0')
           << setw(18) << low;
    } else {
        os << low;
    }
    return os;
}
template <typename T>
istream& operator >> (istream & in, vector <T> &a){
    for (int i=0; i<a.size(); i++){
        in >> a[i];
    }
    return in;
}
template <typename T>
ostream& operator << (ostream & os, vector <T> &a){
    for (int i=0; i<a.size(); i++){
        os << a[i] << " ";
    }
    os << '\n';
    return os;
}

