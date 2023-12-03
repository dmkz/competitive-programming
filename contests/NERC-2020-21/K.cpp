#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using vi = vector<int>;
void op1(int n, vi&x) {
    for (int i = 1; i < 2 * n; i+=2)
        swap(x[i-1],x[i]);
}
void op2(int n, vi&x) {
    for (int i = n; i < 2 * n; i++)
        swap(x[i-n],x[i]);
}
auto bfs(int n) {
    vi a(2*n);
    for (int i = 0; i < isz(a); i++)
        a[i] = i;
    map<vi, int> steps;
    queue<vi> q;
    q.push(a);
    while (q.size()) {
        auto x = q.front();
        q.pop();
        int was = steps[x];
        // применяем первую операцию:
        op1(n,x);
        if (auto it = steps.find(x); it == steps.end()) {
            steps[x] = was+1;
            q.push(x);
        }
        op1(n,x);
        // применяем вторую операцию:
        op2(n,x);
        if (auto it = steps.find(x); it == steps.end()) {
            steps[x] = was+1;
            q.push(x);
        }
        op2(n,x);
    }
    return steps;
}
main() {
    int n; cin >> n;
    auto steps = bfs(n);
    vi a(2*n);
    for (auto &it : a)
        cin >> it;
    for (auto &it : a)
        it--;
    auto it = steps.find(a);
    if (it != steps.end())
        cout << it->second << endl;
    else
        cout << "-1\n";
}
