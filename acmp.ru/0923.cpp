#include <stdio.h>
#include <bits/stdc++.h>

typedef long long Int;

std::map<Int, Int> answer;

Int solve(Int n) {
    if (n < 3) {
        return 0;
    }
    if (n == 3) {
        return 1;
    }
    if (answer.find(n) == answer.end()) {
        answer[n] = solve((n+1) / 2) + solve(n / 2);
    }
    return answer[n];
}


int main() {
    Int n;
    std::cin >> n;
    std::cout << solve(n) << std::endl;
    return 0;
}