#include <bits/stdc++.h>

#define Please return
#define Accepted 0
#define int long long
#define endl "\n"
#define double long double

using namespace std;

constexpr int MAXN = 10, mod = 998244353;

string int_to_string(int n)
{
    if (n == 0)
    {
        return "0";
    }
    string ans;
    while (n)
    {
        ans += n % 10 + '0';
        n /= 10;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

string int_to_rim(int n)
{
    string ans;
    if (n > 3999)
    {
        return ans;
    }
    string s = int_to_string(n);
    int m = s.size();
    vector<map<char, string> > c(4);
    c[0]['1'] = "I"; c[0]['2'] = "II"; c[0]['3'] = "III"; c[0]['4'] = "IV"; c[0]['5'] = "V"; c[0]['6'] = "VI"; c[0]['7'] = "VII"; c[0]['8'] = "VIII"; c[0]['9'] = "IX";
    c[1]['1'] = "X"; c[1]['2'] = "XX"; c[1]['3'] = "XXX"; c[1]['4'] = "XL"; c[1]['5'] = "L"; c[1]['6'] = "LX"; c[1]['7'] = "LXX"; c[1]['8'] = "LXXX"; c[1]['9'] = "XC";
    c[2]['1'] = "C"; c[2]['2'] = "CC"; c[2]['3'] = "CCC"; c[2]['4'] = "CD"; c[2]['5'] = "D"; c[2]['6'] = "DC"; c[2]['7'] = "DCC"; c[2]['8'] = "DCCC"; c[2]['9'] = "CM";
    c[3]['1'] = "M"; c[3]['2'] = "MM"; c[3]['3'] = "MMM";
    for (int i = 0; i < m; ++i)
    {
        ans += c[m - i - 1][s[i]];
    }
    return ans;
}

void solve ()
{
    set<string> c;
    for (int i = 1; i < 4000; ++i)
    {
        c.insert(int_to_rim(i));
    }
    string s;
    cin >> s;
    int n = s.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 1; j < min((long long) 16, i + 1); ++j)
        {
            string s1;
            for (int l = 0; l < j; ++l)
            {
                s1 += s[i - l - 1];
            }
            reverse(s1.begin(), s1.end());
            if (c.count(s1))
            {
                dp[i] = (dp[i] + dp[i - j]) % mod;
            }
        }
    }
    cout << dp[n] << endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0), cerr.tie(0);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int tt;
    // cin >> tt;
    tt = 1;
    while (tt--)
    {
        solve();
    }
}

/*
0 1
4
1 2 2 5
1 2 3 5
*/