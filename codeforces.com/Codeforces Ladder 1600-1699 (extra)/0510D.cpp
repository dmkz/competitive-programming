/*
    Problem: 510D. Fox And Jumping
    
    Solution: dynamic programming, number theory, bitmasks, O(n^2 * 2^log(max))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct Card {
    int len, cost;
};

const int INF = (int)1e9+7;

int solve(const std::vector<Card>& cards) {
    // Precalc leading bit for all masks till 2^9:
    int leadingBit[512] = {};
    for (int mask = 1; mask < 512; ++mask) {
        for (int bit = 0; bit < 9; ++bit) {
            if ((mask >> bit) & 1) {
                leadingBit[mask] = bit;
            }
        }
    }
    // Calculate answer:
    int answ = INF, n = (int)cards.size();
    for (int i = 0; i < n; ++i) {
        int primes[9], size = 0;
        {   // factorization of card's length:
            int number = cards[i].len;
            for (int j = 2; j * j <= number; ++j) {
                if (number % j == 0) {
                    primes[size++] = j;
                    while (number % j == 0) {
                        number /= j; 
                    }
                }
            }
            if (number > 1) {
                primes[size++] = number;
            }
            assert(size <= 9);
        }
        // dynamic programming:
        std::vector<int> curr(1 << size, INF), next;
        curr.back() = cards[i].cost;
        next = curr;
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            std::vector<int> gcd(1 << size, 0); // gcd is bitmask of gcd(mask, length) over primes
            int a = cards[j].len, c = cards[j].cost;
            for (int mask = 1; mask < (1 << size); ++mask) {
                int b = leadingBit[mask];
                int p = primes[b];
                int g = mask ^ (1 << b);
                g = (a % p == 0) ? (gcd[g] | (1 << b)) : gcd[g];
                gcd[mask] = g;
                next[g] = std::min(next[g], curr[mask] + c);
            }
            curr = next;
        }
        answ = std::min(answ, curr[0]);
    }
    return answ == INF ? -1 : answ;
}

int main() {
    int n;
    while (std::cin >> n) {
        std::vector<Card> cards(n);
        for (auto& it : cards) {
            std::cin >> it.len;
        }
        for (auto& it : cards) {
            std::cin >> it.cost;
        }
        std::cout << solve(cards) << std::endl;
    }
    return 0;
}