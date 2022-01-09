#include <bits/stdc++.h>
int main() {
    int a,b,c,d,e,f;
    while (std::cin >> a >> b >> c >> d >> e >> f) {
        if (a*c*e != b*d*f) {
            std::cout << "-1\n";
            continue;
        }
        // triangle rules:
        if (a*c<b*c+d*b &&
            b*c<a*c+d*b &&
            d*b<a*c+b*c)
        {
            std::cout << "1\n";
        }
        else
        {
            std::cout << "-1\n";
        }
    }
    return 0;
}