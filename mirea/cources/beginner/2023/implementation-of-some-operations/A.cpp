#include <bits/stdc++.h>
int main() {   
    std::vector<int> digit_count = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    int a, b; std::cin >> a >> b;
    int sum = 0;
    for (int i = a; i <= b; ++i)
        for (int temp = i; temp > 0; temp /= 10)
            sum += digit_count[temp % 10];
    std::cout << sum << std::endl;
    return 0;
}