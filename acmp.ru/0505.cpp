#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <bits/stdc++.h>

template<typename T>
bool operator<(const std::vector<T>& a, const std::vector<T>& b) {
    assert(a.size() == b.size());
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] < b[i]) {
            return true;
        } else if (a[i] > b[i]) {
            return false;
        }
    }
    return false;
}

int main() {
    std::map<std::vector<int>, int> pattern;
    int len, nPatterns, nQueries;
    scanf("%d %d %d", &len, &nPatterns, &nQueries);
    
    std::vector<int> temp(len);
    for (int i = 0; i < nPatterns; ++i) {
        int id; scanf("%d", &id); 
        for (auto& it : temp) scanf("%d", &it);
        pattern[temp] = id;
    }
    int ok = 0, bad = 0;
    for (int i = 0; i < nQueries; ++i) {
        for (auto& it : temp) scanf("%d", &it);
        auto it = pattern.find(temp);
        if (it == pattern.end()) {
            printf("-\n"); ++bad;
        } else {
            printf("%d\n", it->second); ++ok;
        }
    }
    printf("OK=%d BAD=%d\n", ok, bad);

    return 0;
}