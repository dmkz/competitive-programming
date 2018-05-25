#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

struct DataStruct {
    std::vector<int> arr, add;
    
    const int GSIZE = 128;
    
    DataStruct(int size, int value) {
        arr.assign(size, value);
        add.assign(size / GSIZE + 1, 0);
    }
    
    void push(int g) {
        if (add[g] == 0) {
            return;
        }
        const int begin = GSIZE * g;
        const int after = std::min(begin + GSIZE, (int)arr.size());
        int a = add[g];
        for (int i = begin; i < after; ++i) {
            arr[i] += a;
        }
        add[g] = 0;
    }
    
    void push_all() {
        for (int g = 0; g < (int)add.size(); ++g) {
            push(g);
        }
    }
    
    void inc(int left, int right) {
        assert(right < (int)arr.size());
        int gl = left / GSIZE;
        int gr = right / GSIZE;
        if (gl == gr) {
            push(gl);
            for (int i = left; i <= right; ++i) {
                arr[i]++;
            }
        } else {
            push(gl);
            push(gr);
            for (int i = left, after = (gl+1) * GSIZE; i < after; ++i) {
                arr[i]++;
            }
            for (int g = gl+1; g < gr; ++g) {
                add[g]++;
            }
            for (int i = gr * GSIZE; i <= right; ++i) {
                arr[i]++;
            }
        }
    }
};

bool solve(const std::vector<std::pair<int, int>>& input) {
    DataStruct ds(10000, 0);
    for (const auto& p : input) {
        ds.inc(p.first, p.second);
    }
    ds.push_all();
    for (int i = 0; i < (int)ds.arr.size(); ++i) {
        const auto& it = ds.arr[i];
        if (it == 0) {
            return false;
        }
    }
    std::vector<int> pref{0};
    for (auto& it : ds.arr) {
        pref.push_back(pref.back() + (it >= 2));
    }
    for (const auto& p : input) {
        if (pref[p.second+1] - pref[p.first] >= (p.second-p.first+1)) {
            return false;
        }
    }
    return true;
}

int main() {
    int nQueries;
    scanf("%d", &nQueries);
    while (nQueries--) {
        int n; 
        scanf("%d", &n);
        std::vector<std::pair<int, int>> input;
        for (int i = 0; i < n; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            input.push_back(std::make_pair(a, b-1));
        }
        printf(solve(input) ? "Accepted\n" : "Wrong Answer\n");
    }
    return 0;
}