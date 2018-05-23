#include <iostream>
#include <string>
#include <cassert>

int main() {
    int n; std::cin >> n;
    if (n == 1) {
        std::cout << "10 0";
        return 0;
    }
    static int count[21][201][201]; // [len][sum][prod]
    for (int digit = 1; digit <= 9; ++digit) {
        count[1][digit][digit] = 1;
    }
    for (int len = 1; len < n; ++len) {
        for (int sum = 0; sum < 201; ++sum) {
            for (int prod = 0; prod < 201; ++prod) {
                for (int digit = 1; digit <= 9; ++digit) {
                    if (sum+digit < 201 && prod * digit < 201) {
                        count[len+1][sum+digit][prod * digit] += count[len][sum][prod];
                    }
                }
            }
        }
    }
    int answ = 0;
    for (int sum = 0; sum < 201; ++sum) {
        answ += count[n][sum][sum];
    }
    
    std::string number(n, '1');
    int sum = n, prod = 1;
    while (prod != sum) {
        int pos = n-1;
        while (pos >= 0 && number[pos] == '9') {
            number[pos] = '1';
            sum -= 8;
            prod /= 9;
            --pos;
        }
        assert(pos >= 0);
        sum++;
        prod = prod / (number[pos] - '0') * (number[pos] - '0' + 1);
        number[pos]++;
    }
    std::cout << answ << ' ' << number;
    return 0;
}