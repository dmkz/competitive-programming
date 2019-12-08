/*
    Problem: 371C. Hamburgers
    Solution: math, implementation
*/
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;
int main() {
    string s; cin >> s;
    ll k1=0,k2=0,k3=0;
    for (auto c : s) {
        k1 += (c == 'B');
        k2 += (c == 'S');
        k3 += (c == 'C');
    }
    ll n1,n2,n3; cin >> n1 >> n2 >> n3;
    ll p1,p2,p3,sum; cin >> p1 >> p2 >> p3 >> sum;
    if (k1 == 0) { k1 = 1; p1 = 0; n1 = 1e13 + 1; }
    if (k2 == 0) { k2 = 1; p2 = 0; n2 = 1e13 + 1; }
    if (k3 == 0) { k3 = 1; p3 = 0; n3 = 1e13 + 1; }
    ll answ = min({n1/k1,n2/k2,n3/k3});
    n1 -= answ * k1;
    n2 -= answ * k2;
    n3 -= answ * k3;
    int count = 0;
    while ((n1 || n2 || n3) && count < 2e6) {
        if (n1 / k1 == 0) {
            ll t = max(1LL,min(n2 / k2, n3 / k3));
            ll buy = min(sum / p1, t * k1 - n1);
            sum -= buy * p1;
            n1 += buy;
        }
        if (n2 / k2 == 0) {
            ll t = max(1LL,min(n1 / k1, n3 / k3));
            ll buy = min(sum / p2, t * k2 - n2);
            sum -= buy * p2;
            n2 += buy;
        }
        if (n3 / k3 == 0) {
            ll t = max(1LL,min(n1 / k1, n2 / k2));
            ll buy = min(sum / p3, t * k3 - n3);
            sum -= buy * p3;
            n3 += buy;
        }
        ll get = min({n1/k1,n2/k2,n3/k3});
        if (get == 0) break;
        answ += get;
        n1 -= get * k1;
        n2 -= get * k2;
        n3 -= get * k3;
        ++count;
    }
    
    answ += sum / (k1*p1+k2*p2+k3*p3);
    cout << answ;
    return 0;
}