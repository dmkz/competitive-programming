#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
void task1() {
    int x = 1, timer = 0;
    std::string s;
    std::map<int,int> table;
    table[timer] = x;
    while (std::cin >> s) {
        const int t = (s == "addx" ? 0 : 1);
        switch(t) {
            case 0: {
                int delta; std::cin >> delta;
                timer++;
                table[timer] = x;
                timer++;
                table[timer] = (x += delta);
                break;
            }
            case 1: {
                timer++;
                table[timer] = x;
                break;
            }
            default: assert(false);
        };
    }
    auto getMult = [&](int tt, bool inc) {
        return (tt+inc) * table[tt];
    };
    for (auto [tt,val] : table)
        std::cout << tt << ' ' << val << std::endl;
    int res = getMult(19,true);
    std::cout << "res = " << res << std::endl;
    for (int tt = 59; tt <= table.rbegin()->first; tt += 40) {
        res += getMult(tt,true);
        std::cout << res << std::endl;
    }
}

void task2() {
    std::string sprite = "###.....................................";
    int x = 1, timer = 0;
    std::string s, image;
    std::map<int,int> table;
    auto print = [&](){
        auto newChar = sprite[isz(image)%40];
        image += newChar;
    };
    //print();
    while (std::cin >> s) {
        const int t = (s == "addx" ? 0 : 1);
        switch(t) {
            case 0: {
                int delta; std::cin >> delta;
                print();
                print();
                delta = (delta % 40 + 40) % 40;
                while(delta--)
                    std::rotate(sprite.begin(),sprite.end()-1,sprite.end());
                std::cout << "sprite = " << sprite << std::endl;
                break;
            }
            case 1: {
                print();
                break;
            }
            default: assert(false);
        };
    }
    std::cout << "image:\n";
    for (int i = 0, j = 40; j <= isz(image); i += 40, j += 40)
        std::cout << image.substr(i, 40) << std::endl;
}
int main() {
    task2();
}