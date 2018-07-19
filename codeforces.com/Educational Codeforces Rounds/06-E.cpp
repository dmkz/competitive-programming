/*
    Problem: 620E. New Year Tree

    Solution: Bitmasks, Sqrt-Decomposition, Euler tour, O(n sqrt(n))
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

typedef long long ll;

struct SqrtDecomposition {
    
    std::vector<ll> data, val, set;
    
    const int gsize = 512; // 2*100*1000 = 256 * 1024 = 512 * 512
    
    // Apply saved changes to group g:
    void push(int g) {
        if (set[g] == -1) return;
        int begin = g * gsize;
        int after = std::min((int)data.size(), (g+1)*gsize);
        for (int i = begin; i < after; ++i) {
            data[i] = set[g];
        }
        val[g] = set[g];
        set[g] = -1;
    }
    
    // Re-calculate value for group g:
    void recalc(int g) {
        int begin = g * gsize;
        int after = std::min((int)data.size(), (g+1)*gsize);
        ll value = 0;
        for (int i = begin; i < after; ++i) {
            value |= data[i];
        }
        val[g] = value;
    }
    
    // Set-query:
    void set_val(int l, int r, ll value) {
        const int gl = l / gsize;
        const int gr = r / gsize;
        if (gl == gr) {
            push(gl);
            for (int i = l; i <= r; ++i) {
                data[i] = value;
            }
            recalc(gl);
        } else {
            push(gl);
            push(gr);
            for (int i = l; i < (gl+1) * gsize; ++i) {
                data[i] = value;
            }
            for (int g = gl+1; g < gr; ++g) {
                set[g] = val[g] = value;
            }
            for (int i = gr * gsize; i <= r; ++i) {
                data[i] = value;
            }
            recalc(gl);
            recalc(gr);
        }
    }
    
    // Get-query:
    ll get(int l, int r) {
        const int gl = l / gsize;
        const int gr = r / gsize;
        ll answ = 0;
        if (gl == gr) {
            push(gl);
            for (int i = l; i <= r; ++i) {
                answ |= data[i];
            }
        } else {
            push(gl);
            push(gr);
            for (int i = l; i < (gl+1) * gsize; ++i) {
                answ |= data[i];
            }
            for (int g = gl+1; g < gr; ++g) {
                answ |= val[g];
            }
            for (int i = gr * gsize; i <= r; ++i) {
                answ |= data[i];
            }
        }
        return answ;
    }
    
    // Construct Sqrt-Decomposition from array:
    SqrtDecomposition(const std::vector<ll>& arr) : data(arr) {
        set.assign((arr.size() + gsize - 1) / gsize, -1);
        val.assign((arr.size() + gsize - 1) / gsize,  0);
        
        for (int g = 0; g < (int)val.size(); ++g) {
            recalc(g);
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nVert, nQueries;
    std::cin >> nVert >> nQueries;
    
    // Input colors:
    std::vector<ll> colors(nVert);
    for (auto& it : colors) {
        int pow; std::cin >> pow; --pow;
        it = ll(1) << pow;
    }
    
    // Input edges:
    std::vector<std::vector<int>> edges(nVert);
    for (int i = 0; i < nVert-1; ++i) {
        int a, b;
        std::cin >> a >> b;
        edges[a-1].push_back(b-1);
        edges[b-1].push_back(a-1);
    }
    
    
    // Run euler tour on tree:
    std::vector<int> l(nVert), r(nVert);
    
    std::vector<ll> arr;
    
    std::function<void(int,int)> visit = [&](const int curr, const int parent) {
        arr.push_back(colors[curr]);
        l[curr] = (int)arr.size()-1;
        for (auto& next : edges[curr]) {
            if (next != parent) {
                visit(next, curr);
            }
        }
        r[curr] = (int)arr.size()-1;
    };
    
    visit(0, -1);
    
    // Build Sqrt-Decomposition on array:
    SqrtDecomposition sd(arr);
    
    // Answer on queries in O(sqrt(n)) per one query:
    while (nQueries --> 0) {
        int t; std::cin >> t;
        if (t == 1) {
            int v, c; std::cin >> v >> c; --v; --c;
            sd.set_val(l[v], r[v], ll(1) << c);
        } else {
            int v; std::cin >> v; v--;
            std::cout << __builtin_popcountll(sd.get(l[v], r[v])) << '\n';
        }
    }
    
    return 0;
}