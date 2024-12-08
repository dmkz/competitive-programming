#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
int sign(long double x) {
    if (x < 0) return -1;
    if (x > 0) return +1;
    return 0;
}
pii ask(int x, int y) {
    cout << "? " << x << " " << y << endl;
    long double x1, y1;
    cin >> x1 >> y1;
    if (x1 * x1 + y1 * y1 < 1e-9)
        return {0, 0};
    return {sign(x1), sign(y1)};
}
pii solve(int xmin, int xmax, int ymin, int ymax) {
    if (xmin == xmax && ymin == ymax)
        return {xmin, xmax};
    int xmid = (xmin + xmax) / 2;
    int ymid = (ymin + ymax) / 2;
    auto [x1, y1] = ask(xmid, ymid);
    if (x1 == 0 && y1 == 0) return {xmid, ymid};
    else if (x1 > 0 && y1 > 0) return solve(xmid+1, xmax, ymid+1, ymax);
    else if (x1 > 0 && y1 < 0) return solve(xmid+1, xmax, ymin, ymid-1);
    else if (x1 < 0 && y1 < 0) return solve(xmin, xmid-1, ymin, ymid-1);
    else if (x1 < 0 && y1 > 0) return solve(xmin, xmid-1, ymid+1, ymax);
    else if (x1 == 0 && y1 > 0) return solve(xmid, xmid, ymid+1, ymax);
    else if (x1 == 0 && y1 < 0) return solve(xmid, xmid, ymin, ymid-1);
    else if (y1 == 0 && x1 > 0) return solve(xmid+1, xmax, ymid, ymid);
    else if (y1 == 0 && x1 < 0) return solve(xmin, xmid-1, ymid, ymid);
    else assert(false && "THIS CASE IS IMPOSSIBLE!!!!!!");
    return {-1, -1};
}
const int XMIN = -(int)1e9;
const int XMAX = +(int)1e9;
main() {
    auto [x, y] = solve(XMIN, XMAX, XMIN, XMAX);
    cout << "! " << x << " " << y << endl;
}
