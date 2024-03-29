#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    vector<ll> answers = {0, 1, 1, 2, 4, 6, 9, 14};
    vector<ll> diff(answers.size(), 0);
    for (int i = 1; i < (int)answers.size(); i++)
        diff[i] = answers[i] - answers[i-1];
    
    int n; cin >> n;
    for (int i = (int)answers.size(); i <= n; i++) {
        ll nextDiff = diff[i-1] + diff[i-3];
        diff.push_back(nextDiff);
        answers.push_back(answers.back() + nextDiff);
    }
    cout << answers[n] << endl;
}
