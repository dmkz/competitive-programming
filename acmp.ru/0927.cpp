/*
    "A + B = C": динамическое программирование
*/

#include <iostream>
#include <string>
#include <algorithm>

const int MOD = (int)1e9+7;

inline int add(int a, int b) {
    return (a += b) >= MOD ? a - MOD : a;
}

const bool debug = false;

int main() {
    std::string s;
    std::cin >> s;
    
    std::reverse(s.begin(), s.end());
    
    static int count[10001][10][10][2]; // [len][digA][digB][carry]
    
    for (int digA = 0; digA < 10; ++digA) {
        for (int digB = 0; digB < 10; ++digB) {
            if ((digA + digB) % 10 == s[0] - '0') {
                ++count[1][digA][digB][(digA+digB) / 10];
            }
        }
    }

    for (int len = 2; len <= (int)s.size(); ++len) {
        for (int currA = 0; currA < 10; ++currA) {
            for (int currB = 0; currB < 10; ++currB) {
                for (int carry = 0; carry < 2; ++carry) {
                    int digit = currA + currB + carry;
                    int rem = digit / 10;
                    digit %= 10;
                    if (digit != s[len-1] - '0') continue;
                    for (int prevA = 0; prevA < 10; ++prevA) {
                        if (prevA == currA) continue;
                        for (int prevB = 0; prevB < 10; ++prevB) {
                            if (prevB == currB) continue;
                            count[len][currA][currB][rem] = add(count[len][currA][currB][rem], count[len-1][prevA][prevB][carry]);
                        }
                    }
                }
            }
        }
    }
    int answ = 0;
    for (int digA = 1; digA < 10; ++digA) {
        for (int digB = 1; digB < 10; ++digB) {
            answ = add(answ, count[s.size()][digA][digB][0]);
        }
    }
    printf("%d", answ);
    
    return 0;
}