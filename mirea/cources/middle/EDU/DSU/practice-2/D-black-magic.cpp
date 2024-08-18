#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using namespace std;
random_device rd;
mt19937_64 gen(rd()); // генератор
const ll mod = 1e9 + 7;
const ll mod2 = 998244353;
vector <ll> parent;
vector <ll> nxt;
ll Find(ll x)
{
    if (parent[x] != x)
        parent[x] = Find(parent[x]);
    return parent[x];
}
void unite(ll x,ll y)
{
    ll root_x = Find(x);
    ll root_y = Find(y);
    if (root_x != root_y)
    {
        if (root_x < root_y)
            parent[root_x] = root_y;
        else
            parent[root_y] = root_x;
    }
}
void Solve()
{
    ll n,q;
    cin >> n >> q;
    parent = vector <ll> (n + 3);
    nxt = vector <ll> (n + 3);
    for (ll i = 0; i < n; i++)
    {
        parent[i] = i;
        nxt[i] = (i + 1) % n;
    }
    while (q-->0)
    {
        ll type;
        cin >> type;
        if (type == 1)
        {
            ll a,b;
            cin >> a >> b;
            --a; --b;
            unite(a,b);
        }
        if (type == 2)
        {
            ll L , R;
            cin >> L >> R;
            L--;
            R--;
            while (L < R)
            {
                unite(nxt[L],L);
                ll new_pos = nxt[L];
                nxt[L] = max(nxt[L],R);
                L = new_pos;
            }
        }
        if (type == 3)
        {
            ll x,y;
            cin >> x >> y;
            x--;
            y--;
            ll root_x = Find(x);
            ll root_y = Find(y);
            cout << (root_x == root_y ? "YES\n" : "NO\n");
        }
    }

}

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    ll tt = 1;
    //cin >> tt;
    while (tt-->0)
    {
        Solve();
    }
}