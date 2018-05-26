#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

void assert_tle(bool q) {
    if (!q) {
        while (true);
    }
}

struct SqrtDecomposition {
    
    struct Group {
        int begin, after, add;
        std::vector<int> values, sorted;
        
        
        Group(int begin, int after, const std::vector<int>& arr)
            : begin(begin), after(after)
        {
            add = 0;
            values = arr;
            sorted = values;
            std::sort(sorted.begin(), sorted.end());
            assert_tle(after-begin == (int)values.size());
        }
        
        bool include(int x) const {
            x -= add;
            return binary_search(sorted.begin(), sorted.end(), x);
        }
        
        bool include(int l, int r, int x) const {
            assert_tle(begin <= l && l <= r && r < after);
            if (l == begin && r+1 == after) {
                return include(x);
            }
            for (int i = l; i <= r; ++i) {
                if (values[i-begin] + add == x) {
                    return true;
                }
            }
            return false;
        }
        
        void inc(int x) {
            add += x;
        }
        
        void inc(int l, int r, int x) {
            assert_tle(begin <= l && l <= r && r < after);
            if (l == begin && r+1 == after) {
                inc(x);
                return;
            }
            for (int i = begin; i < after; ++i) {
                values[i-begin] += add;
                if (l <= i && i <= r) {
                    values[i-begin] += x;
                }
            }
            add = 0;
            sorted = values;
            std::sort(sorted.begin(), sorted.end());
        }
        
    };
    
    std::vector<Group> groups;
    
    const int GSIZE = 64;
    
    SqrtDecomposition(const std::vector<int>& arr) {
        int count = ((int)arr.size() + GSIZE - 1) / GSIZE;
        for (int g = 0; g < count; ++g) {
            auto begin = arr.begin() + g * GSIZE;
            auto after = begin + std::min(GSIZE, int(arr.end()-begin));
            groups.push_back(
                Group(begin - arr.begin(), after-arr.begin(), std::vector<int>(begin, after))
            );
        }
    }
    
    bool include(int l, int r, int x) {
        int gl = l / GSIZE;
        int gr = r / GSIZE;
        if (gl == gr) {
            return groups[gl].include(l, r, x);
        } else {
            bool flag = groups[gl].include(l, (gl+1)*GSIZE-1, x);
            if (flag) return true;
            flag = groups[gr].include(gr*GSIZE, r, x);
            if (flag) return true;
            for (int g = gl+1; g < gr; ++g) {
                if (groups[g].include(x)) {
                    return true;
                }
            }
            return false;
        }
    }
    
    void inc(int l, int r, int x) {
        int gl = l / GSIZE;
        int gr = r / GSIZE;
        if (gl == gr) {
            groups[gl].inc(l, r, x);
        } else {
            groups[gl].inc(l, (gl+1)*GSIZE-1, x);
            groups[gr].inc(gr*GSIZE, r, x);
            for (int g = gl+1; g < gr; ++g) {
                groups[g].inc(x);
            }
        }
    }
    
};

int main() {
    int n, limit, q;
    scanf("%d %d %d", &n, &limit, &q);
    SqrtDecomposition sd(std::vector<int>(n, 0));
    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        if (sd.include(l, r-1, limit)) {
            printf("No\n");
        } else {
            sd.inc(l, r-1, 1);
            printf("Yes\n");
        }
    }
    return 0;
}