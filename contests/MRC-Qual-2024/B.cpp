#include <bits/stdc++.h>
main() {
    std::string org;
    while(std::cin >> org) {
        bool isOrg = (org == "org");
        int t; std::cin >> t;
        int qual; std::cin >> qual;
        int s; std::cin >> s;
        int b = 2;
        if (isOrg) {
            b = 4;
        } else if (s >= 30) {
            b = 3;
        } else if (t >= 2) {
            b = 3;
        }
        int T = 0;
        if (qual >= 60) {
            T = 2;
        } else if (qual >= 30) {
            T = 1;
        }
        std::cout << b + T << std::endl;
    }
}
