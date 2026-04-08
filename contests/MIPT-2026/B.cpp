// перестановки, конструктив, стресс-тест, перебор, XOR, закономерность
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
using vi = vector<int>;
int score(const vi &a, const vi &b) {
    int res = 0;
    for (int i = 0; i < isz(a); i++)
        res ^= (a[i] + b[i]);
    return res;
}
vi constructMin(int n) {
    if (n == 1) return {1};
    vi b(n);
    for (int i = 0; i < n; i++)
        b[i] = i+1;
    if (n % 2 == 0) {
        for (int i = 0; i < n; i += 2)
            swap(b[i], b[i+1]);
    } else {
        if (n == 3) return {1, 2, 3};
        for (int i = 3; i + 1 < n; i += 2)
            swap(b[i], b[i+1]);
    }
    return b;
}
vi constructMax(int n) {
    if (n == 1) return {1};
    if (n == 2) return {1, 2};
    vi a(n);
    for (int i = 0; i < n; i++)
        a[i] = i+1;
    vi b = a;
    int res = score(a, b);
    vi posOf(n+1);
    for (int i = 0; i < n; i++)
        posOf[b[i]] = i;
    // что будет, если поменяем местами b[i] и b[j]?
    res /= 2;
    // 1: 1
    // 2..3: 3
    // 4..7: 7
    // 8..10: 15
    // знаем максимальный результат:
    int maxPow = 0;
    while (n > (1 << maxPow) - 1)
        maxPow++;
    int maxRes = (1 << maxPow) - 1;
    assert(maxRes >= n);
    if (res == maxRes)
        return b;
    // иначе нужно обменять местами два элемента
    for (int i = 0; i < n; i++) {
        // res ^ b[i] ^ b[j] == maxRes
        int want = maxRes ^ (res ^ b[i]);
        if (1 <= want && want <= n && i != posOf[want]) {
            swap(b[i], b[posOf[want]]);
            return b;
        }
    }
    return b;
}
void stress() {
    for (int n = 1; n <= 26; n++) {
        auto a = constructMin(n);
        cout << "n = " << n << ": OK" << endl;
    }
    for (int n = 1; n <= 13; n++) {
        vector<int> a(n);
        for (int i = 0; i < n; i++)
            a[i] = i+1;
        vector<int> b = a;
        int maxRes = INT_MIN, minRes = INT_MAX;
        vector<int> maxVec, minVec;
        do {
            int res = score(a, b);
            if (res > maxRes) {
                maxRes = res;
                maxVec = b;
            }
            if (res < minRes) {
                minRes = res;
                minVec = b;
            }
        } while (next_permutation(all(b)));
        cout << "n = " << n << ", maxRes = " << maxRes << ", minRes = " << minRes << endl;
        cout << "   a:";
        for (int i = 0; i < n; i++)
            cout << ' ' << a[i];
        cout << endl;
        cout << " min:";
        for (int i = 0; i < n; i++)
            cout << ' ' << minVec[i];
        cout << endl;
        cout << " max:";
        for (int i = 0; i < n; i++)
            cout << ' ' << maxVec[i];
        cout << endl;
        auto fastMin = constructMin(n);
        auto fastMax = constructMax(n);
        assert(score(fastMax, a) == maxRes);
        assert(score(fastMin, a) == minRes);
        cout << "    OK" << endl;
    }
}
main() {
    //stress();
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vi a(n), p(n+1), b(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        p[a[i]] = i;
    }
    vi mn = constructMin(n);
    vi mx = constructMax(n);
    for (int i = 0; i < n; i++) {
        // i+1 -> mn[i]
        b[p[i+1]] = mn[i];
        c[p[i+1]] = mx[i];
    }
    for (auto it : b) cout << it << ' ';
    cout << endl;
    for (auto it : c) cout << it << ' ';
    cout << endl;
}
