#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
using Int = uint64_t;
bool isEvenDigitNumber(Int ai, Int &left, Int &right) {
    string s = to_string(ai);
    if (isz(s) % 2 != 0)
        return false;
    int mid = isz(s) / 2;
    left = stoll(s.substr(0, mid));
    right = stoll(s.substr(mid));
    return true;
}
void part1() {
    // чтение
    vector<Int> a;
    for (int x; cin >> x; a.push_back(x));
    // моделирование
    vector<Int> b;
    for (int step = 0; step < 25; step++) {
        b.clear();
        for (int i = 0; i < isz(a); i++)
            if (a[i] == 0) {
                b.push_back(1);
            } else if (Int left, right; isEvenDigitNumber(a[i], left, right)) {
                b.push_back(left);
                b.push_back(right);
            } else {
                b.push_back(a[i] * 2024);
            }
        b.swap(a);
    }
    cout << a.size() << ", sum = " << accumulate(all(a), Int(0)) << endl;
}   
void part2() {
    // чтение
    vector<pair<Int,Int>> a;
    for (int x; cin >> x; a.emplace_back(x, 1));
    // моделирование
    vector<pair<Int,Int>> b;
    for (int step = 0; step < 75; step++) {
        b.clear();
        for (int i = 0; i < isz(a); i++)
            if (a[i].first == 0) {
                b.emplace_back(1, a[i].second);
            } else if (Int left, right; isEvenDigitNumber(a[i].first, left, right)) {
                b.emplace_back(left, a[i].second);
                b.emplace_back(right, a[i].second);
            } else {
                b.emplace_back(a[i].first * 2024, a[i].second);
            }
        
        // оставляем только уникальные + считаем их количество
        sort(all(b));
        a.clear();
        for (int i = 0, j = 0; i < isz(b); i = j) {
            Int sum = 0;
            while (j < isz(b) && b[i].first == b[j].first) {
                sum += b[j].second;
                j++;
            }
            a.emplace_back(b[i].first, sum);
        }
        //cout << step << ": " << a.size() << endl;
    }
    Int answ{};
    for (const auto &[_, cnt] : a)
        answ += cnt;
    cout << answ << endl;
}
main() {
    part2();
}

