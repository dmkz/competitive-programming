#include <iostream>
#include <vector>

typedef long long ll;

ll fast(int n) {
    std::vector<int> answers = {0, 4, 10, 20, 35, 56, 83, 116, 155, 198, 244, 292, 341};
    if (n < (int)answers.size()) {
        return answers[n];
    } else {
        return answers.back() + (n - (answers.size()-1)) * 49LL;
    }
}

int main() {
    int n; std::cin >> n; std::cout << fast(n);
    return 0;
}