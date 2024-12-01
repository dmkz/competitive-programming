#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
void part1() {
    vector<int> fi, se;
    for (int a, b; std::cin >> a >> b; ) {
        fi.push_back(a);
        se.push_back(b);
    }
    sort(all(fi));
    sort(all(se));
    int64_t answ{};
    for (int i = 0; i < isz(fi); i++)
        answ += abs(fi[i] - se[i]);
    cout << answ << endl;
}
void part2() {
    vector<int> fi, se;
    for (int a, b; std::cin >> a >> b; ) {
        fi.push_back(a);
        se.push_back(b);
    }
    //sort(all(fi));
    sort(all(se));
    int64_t answ{};
    for (int i = 0; i < isz(fi); i++) {
        auto [begin, end] = equal_range(all(se), fi[i]);
        answ += int64_t(end - begin) * fi[i];
    }
    cout << answ << endl;
}
main() {
    part2();
}
