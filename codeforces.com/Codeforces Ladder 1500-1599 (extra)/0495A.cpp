/*
    Problem: 495A. Digital Counter
    
    Solution: implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>

int inc(const std::string& a, const std::string& b) {
    int c = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] < b[i]) ++c;
    }
    return c;
}

int dec(const std::string& a, const std::string& b) {
    int c = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] > b[i]) --c;
    }
    return c;
}
const bool debug = true;
int main() {
    std::vector<std::string> mask(10);
    mask[0] = "1110111";
    mask[1] = "0010010";
    mask[2] = "1011101";
    mask[3] = "1011011";
    mask[4] = "0111010";
    mask[5] = "1101011";
    mask[6] = "1101111";
    mask[7] = "1010010";
    mask[8] = "1111111";
    mask[9] = "1111011";
    int n; std::cin >> n;
    int answ = 0;
    for (int x = 0; x <= 99; ++x) {
        // кол-во разрядов в x должно быть больше, чем в n
        int dec1 = dec(mask[n % 10], mask[x % 10]);
        if (dec1 != 0) continue;
        int dec2 = dec(mask[n / 10], mask[x / 10]);
        if (dec2 != 0) continue;
        int inc1 = inc(mask[n % 10], mask[x % 10]);
        int inc2 = inc(mask[n / 10], mask[x / 10]);
        answ++;
        //answ += (inc1 + inc2);
    }
    std::cout << answ;    
    return 0;
}