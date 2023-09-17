#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> storage(2*n+1, -100);
    
    int *leftMost = &storage[n];
    
    leftMost[0] = 0;
    int answ = 0, height = 0;
    for (int i = 0, x = 1; i < n; i++, x++) {
        height += (s[i] == '1' ? +1 : -1);
        if (leftMost[height] == -100)
            leftMost[height] = x;
        
        if (answ < x - leftMost[height])
            answ = x - leftMost[height];
    }
    cout << answ << endl;
}