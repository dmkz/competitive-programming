#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cassert>

int main() {
    int len, count;
    scanf("%d %d", &len, &count);
    assert(len % count == 0);
    
    char buf[1000000+1];
    scanf("%1000000s", buf);
    std::string s(buf);
    
    std::vector<std::pair<std::string, int>> sub;
    sub.reserve(count);
    for (int i = 0; i < count; ++i) {
        scanf("%1000000s", buf);
        sub.push_back({buf, i+1});
    }
    std::sort(sub.begin(), sub.end());
    int sublen = len / count;
    for (int begin = 0, after = sublen; after <= len; begin += sublen, after += sublen) {
        auto substr = s.substr(begin, sublen);
        auto it = std::upper_bound(sub.begin(), sub.end(), std::make_pair(substr, 0));
        assert(it->first == substr && it->second > 0);
        printf("%d ", it->second);
        it->second = 0;
    }
    printf("\n");    
    return 0;
}