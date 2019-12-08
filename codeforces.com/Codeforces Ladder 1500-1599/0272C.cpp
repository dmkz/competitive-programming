/*
    Problem: 272C. Dima and Staircase
    Solution: sqrt-decomposition
*/
#include <iostream>
#include <vector>

typedef long long ll;

struct SqrtDecomposition {

    std::vector<ll> data, max, set;
    
    const int GSIZE = 256;
    
    SqrtDecomposition(const std::vector<ll>& arr) : data(arr) {
        max.resize(((int)data.size() + GSIZE - 1) / GSIZE);
        set.resize(((int)data.size() + GSIZE - 1) / GSIZE);
        for (int g = 0; g < (int)max.size(); ++g) {
            const int begin = g * GSIZE;
            const int after = std::min(begin + GSIZE, (int)data.size());
            for (int i = begin; i < after; ++i) {
                max[g] = std::max(max[g], data[i]);
            }
        }
    }
    
    void push(int g) {
        if (set[g] == 0) return;
        auto val = set[g];
        set[g] = 0;
        max[g] = val;
        const int begin = g * GSIZE;
        const int after = std::min(begin + GSIZE, (int)data.size());
        for (int i = begin; i < after; ++i) {
            data[i] = val;
        }
    }
    
    void set_val(int l, int r, ll value) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        if (gl == gr) {
            push(gl);
            max[gl] = std::max(max[gl], value);
            for (int i = l; i <= r; ++i) {
                data[i] = value;
            }
        } else {
            push(gl);
            push(gr);
            max[gl] = std::max(max[gl], value);
            max[gr] = std::max(max[gr], value);
            for (int i = l; i < (gl+1) * GSIZE; ++i) {
                data[i] = value;
            }
            for (int g = gl+1; g < gr; ++g) {
                max[g] = set[g] = value;
            }
            for (int i = gr * GSIZE; i <= r; ++i) {
                data[i] = value;
            }
        }
    }
    
    ll get_max(int l, int r) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        ll answ = 0;
        if (gl == gr) {
            push(gl);
            for (int i = l; i <= r; ++i) {
                answ = std::max(answ, data[i]);
            }
        } else {
            push(gl);
            push(gr);
            for (int i = l; i < (gl+1) * GSIZE; ++i) {
                answ = std::max(answ, data[i]);
            }
            for (int g = gl+1; g < gr; ++g) {
                answ = std::max(answ, max[g]);
            }
            for (int i = gr * GSIZE; i <= r; ++i) {
                answ = std::max(answ, data[i]);
            }
        }
        return answ;
    }
    

};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n;
    std::cin >> n;
    
    std::vector<ll> arr(n);
    for (auto& it : arr) {
        std::cin >> it;
    }
    
    SqrtDecomposition sd(arr);

    int nQ; std::cin >> nQ;
    
    while (nQ--) {
        int w, h; std::cin >> w >> h;
        ll r = sd.get_max(0, w-1);
        std::cout << r << '\n';
        sd.set_val(0, w-1, r+h);
    }
    return 0;
}