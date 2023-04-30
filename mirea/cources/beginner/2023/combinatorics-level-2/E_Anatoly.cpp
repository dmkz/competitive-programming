#include <bits/stdc++.h>

using std::cin;
using std::cout;

int main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    std::vector<int> vec(n);
    std::map<int, int> cnt;
    for(int i = 0; i < n; ++i)
    {
        cin >> vec[i];
        ++cnt[vec[i]];
    }
    std::sort(vec.begin(), vec.end());
    long long ans = 1LL;
    for(int i = 0; i < 3; ++i)
    {
        ans *= cnt[vec[i]];
        --cnt[vec[i]];
    }
    int fact = 1;
    int eq_factor = (vec[0] == vec[1]) + (vec[1] == vec[2]);
    if(eq_factor == 2) fact = 6;
    if(eq_factor == 1) fact = 2;
    cout << ans / fact  << "\n";
    return 0;
}