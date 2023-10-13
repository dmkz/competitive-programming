#include <bits/stdc++.h>
int main() {
    std::vector<int> fib(100000+1, 1);
    for (int i = 2; i <= 100000; i++)
        fib[i] = (fib[i-1] + fib[i-2]) % 3;
    int L, R; std::cin >> L >> R;
    int answ{};
    for (int i = L; i <= R; i++)
        answ += (fib[i] == 0);
    std::cout << answ << std::endl;
}
