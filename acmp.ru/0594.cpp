#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

typedef long double ld;

struct Pair { int len, id; };

int get_len(int len, std::string suf) {
    if (suf == "mile") return len * 1609;
    if (suf == "km") return len * 1000;
    if (suf == "uin") return 33 * len;
    if (suf == "kairi") return 1852 * len;
    if (suf == "zhang") return 3 * len;
    if (suf == "sen") return 38 * len;
    assert(suf == "m");
    return len;
}

int main() {
    int n; scanf("%d", &n);
    std::vector<Pair> arr;
    for (int i = 0; i < n; ++i) {
        int len;
        char buf[10];
        scanf("%d%s", &len, buf);
        arr.push_back(Pair{get_len(len, buf), i+1});
    }
    
    std::sort(arr.begin(), arr.end(), [](const Pair& left, const Pair& right){
        return left.len > right.len || (left.len == right.len && left.id < right.id);
    });
    
    long long best_s = -1; int best_i = -1;
    for (int i = 1; i+1 < n; ++i) {
        if (arr[i-1].len < arr[i].len + arr[i+1].len) {
            int a = arr[i-1].len, b = arr[i].len, c = arr[i+1].len;
            long long temp_s = 1LL * (a+b+c)*(a+b-c)*(a+c-b)*(b+c-a);
            if (temp_s > best_s) {
                best_s = temp_s, best_i = i;
            }
        }
    }
    assert(best_s != -1 && best_i != -1);
    int id1 = arr[best_i-1].id, id2 = arr[best_i].id, id3 = arr[best_i+1].id;
    std::cout << std::fixed << std::setprecision(6) << std::sqrt(ld(best_s)) / 16 << std::endl;
    std::cout << id1 << " " << id2 << " " << id3 << std::endl;

    return 0;
}