#include <bits/stdc++.h>
int main() {
    std::vector<int> cnt(10);
    cnt[0] = (5 + 5) * 2 * 4;
    cnt[1] = (7 - 2) * 4;
    cnt[2] = (19 - 2) * 4;
    cnt[3] = (15 + 4 - 4) * 4;
    cnt[4] = (4 + 4 + 6 - 4) * 4;
    cnt[5] = (15 + 4 - 2) * 4;
    cnt[6] = (15 + 6 - 2) * 4;
    cnt[7] = (5 + 6 - 2) * 4;
    cnt[8] = (15 + 8 - 2) * 4;
    cnt[9] = (15 + 6 - 2 ) * 4;
    std::string s; std::cin >> s;
    int64_t sum{};
    for (char c : s)
        sum += cnt[c-'0'];
    int red,blue,green;
    std::cin >> red >> green >> blue ;
    if (red >= sum) std::cout << "Red\n";
    if (green >= sum) std::cout << "Green\n";
    if (blue >= sum) std::cout << "Blue\n";
    if (std::max<int>({red,blue,green})<sum) std::cout << "No\n";
}
