// problem: 818E
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;

template<typename T, typename Func>
struct SparseTable {

    vector<vector<T>> data;
    
    SparseTable(const auto &vec) { build(vec); }
    
    void build(const auto &a) {
        data.assign(__lg(isz(a))+1, a);
        for (int p = 1; p < isz(data); p++)
            for (int i = 0; i + (1 << p) - 1 < isz(a); i++)
                data[p][i] = Func()(data[p-1][i], data[p-1][i+(1<<(p-1))]);
    }

    T getFunc(int L, int R) {
        assert(L <= R); // отрезок [L, R] - корректный
        const int p = __lg(R-L+1);
        return Func()(data[p][L],data[p][R+1-(1<<p)]);
    }
    
    int binary_lifting(int pos, auto decideMoveRight) {
        T value = Func::neutral();
        for (int p = isz(data)-1; p >= 0; p--) {
            if (pos + (1 << p) - 1 >= isz(data[p]))
                continue; // вышли за пределы массива
            T nextValue = Func()(value, data[p][pos]);
            if (decideMoveRight(nextValue)) {
                pos += (1 << p);
                value = nextValue;
            }
        }
        return pos;
    }
    
};

int k;

struct MultByModulo {
    
    static int neutral() {
        return 1 % k;
    }
    
    int operator()(int left, int right) {
        return (left * 1LL * right) % k;
    }
    
};

int main() {
    ios::sync_with_stdio(false);
    int n; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] %= k;
    }
    SparseTable<int, MultByModulo> st(a);
    int64_t answ{};
    for (int L = 0; L < n; L++) {
        int R = st.binary_lifting(L, [](int prod){ return prod != 0; });
        answ += n - R;
    }
    cout << answ << endl;
}