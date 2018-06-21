#include <iostream>
#include <vector>

inline int mod(int n, int base) {
    return n < 0 ? base - (-n) % base : n % base;
}

inline int pow(int a, int n, int mod) {
    int res = 1 % mod;
    while (n > 0) {
        if (n & 1) {
            res = ::mod(res * a, mod);
        }
        a = ::mod(a * a, mod);
        n >>= 1;
    }
    return res;
}

inline int solve(int n, int mod) {
    if (n <= 20) {
        return pow(2, 1 << n, mod);
    }
    // Находим период и предпериод:
    std::vector<int> step(mod, -1);
    int period, pred, curr = 1 % mod;
    step[curr] = 0;
    while (true) {
        int next = ::mod(curr * 2, mod);
        if (step[next] == -1) {
            step[next] = step[curr]+1;
            curr = next;
        } else {
            pred = step[next];
            period = step[curr]+1-step[next];
            break;
        }
    }
    int power = pred + ::mod(pow(2, n, period) - pred, period);
    return pow(2, power, mod);
}

int main() {
    int n, mod;
    std::cin >> n >> mod;
    std::cout << solve(n, mod);
    return 0;
}