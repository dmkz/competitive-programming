#include <bits/stdc++.h>
bool isTriangle(int a, int b, int c) {
    return a + b > c && a + c > b && b + c > a;
}
int findY(int x) {
    // старший бит:
    int pw = std::__lg(x);
    return (1 << pw) - 1;
}
void research() {
    for (int x = 2; x <= 1000; x++) {
        int y = findY(x);
        if (!isTriangle(x,y,x^y)) {
            std::cout << "Wrong answer for x = " << x << ", y = " << y << std::endl;
        }
        int answ = -1;
        for (int y = x-1; y >= 1; y--) {
            if (isTriangle(x,y,x^y)) {
                answ = y;
                break;
            }
        }
        std::cout << "x = " << x << ": " << answ << std::endl;
    }
    std::exit(0);
}
main() {
    //research();
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) {
        int x; std::cin >> x;
        // условие невырожденности: a+b>c, a+c>b, b+c>a
        // представим число в двоичной системе
        //  x = 10010110
        // в качестве y возьмём все единицы, кроме лидирующего разряда
        //  y = 01111111
        int y = findY(x);
        std::cout << (isTriangle(x,y,x^y) ? y : -1) << "\n";
    }
}
