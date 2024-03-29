#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using Key = pair<int, ll>;

map<Key, ll> cache;

bool check(ll canUse) {
    int last = -1;
    for (int bit = 1; bit <= 55; bit++)
        if ((canUse >> bit) & 1) {
            if (last != -1 && bit - last > 2)
                return false;
            last = bit;
        }
    return true;
}

ll dfs(int lastElement, ll canUse) {
    if (!check(canUse))
        return 0;
    
    Key key(lastElement, canUse);
    if (auto it = cache.find(key); it != cache.end())
        return it->second;
    
    if (canUse == 0)
        return 1;
    ll result = 0;
    for (int nextElement = lastElement-2; nextElement <= lastElement+2; nextElement++)
        if (0 <= nextElement && (((canUse >> nextElement) & 1) == 1)) {
            canUse ^= (1LL << nextElement);
            result += dfs(nextElement, canUse);
            canUse ^= (1LL << nextElement);
        }
    return cache[key] = result;
}

ll solve(int n) {
    cache.clear();
    ll canUse = 0;
    for (int i = 2; i <= n; i++)
        canUse |= (1LL << i);
    return dfs(1, canUse);
}

signed main() {
    int n; cin >> n;
    cout << solve(n) << endl;
}
