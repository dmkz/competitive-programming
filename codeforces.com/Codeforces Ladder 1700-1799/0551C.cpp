/*
    Problem: 551C. GukiZ hates Boxes
    
    Solution: binary search, greedy, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
typedef long long ll;
typedef std::vector<int> vi;
bool can(vi arr, int nStud, ll time) {
    ll sum = std::accumulate(all(arr), ll(0));
    int last = isz(arr)-1;
    for (int id = 0; sum > 0 && id < nStud; ++id) {
        while (last > 0 && arr[last] == 0) { --last; }
        assert(arr[last] != 0);
        ll curTime = last;
        while (curTime < time && sum > 0) {
            while (last > 0 && arr[last] == 0) { --last; }
            assert(arr[last] != 0);
            int delta = (int)std::min((ll)arr[last], time - curTime);
            arr[last] -= delta;
            sum -= delta;
            curTime += delta;
        }
    }
    return (sum == 0);
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n, m; std::cin >> n >> m; ) {
        vi arr(1+n);
        for (int i = 1; i <= n; ++i) { std::cin >> arr[i]; }
        ll low = 0, high = (ll)1e18L;
        while (high - low > 1) {
            ll mid = (low + high) / 2;
            if (can(arr,m,mid)) { high = mid; }
            else { low = mid; }
        }
        std::cout << high << std::endl;
    }
    return 0;
}