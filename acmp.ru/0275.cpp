#include <stdio.h>
#include <string>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        char buf[1000+1];
        scanf("%1000s", buf);
        std::string s(buf);
        std::reverse(s.begin(), s.end());
        int mod = 0;
        int pow = 1;
        for (auto& it : s) {
            (mod += pow * (it - '0')) %= 7;
            (pow *= 2) %= 7;
        }
        printf(mod ? "No\n" : "Yes\n");
    }
    return 0;
}