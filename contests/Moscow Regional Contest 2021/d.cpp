#include <bits/stdc++.h>
#define all(x) std::begin(x), std::end(x)
#define isz(x) (int)std::size(x)
void setmin(auto &x, auto y) { if (y < x) x = y; }
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using pii = std::pair<int,int>;
int main() {
    // read data and find person with minimal size of vector
    // we will start round from this person
    int n; std::cin >> n;
    vvi numbers(n);
    pii min(n,0);
    for (int i = 0; i < n; i++) {
        auto &it = numbers[i];
        int sz; std::cin >> sz;
        it.resize(sz);
        for (auto &item : it) std::cin >> item;
        std::sort(all(it));
        setmin(min,pii(sz,i));
    }
    int start = min.second;
    vi answer(n);
    auto play = [&](int x){
        // try to start with number `x` from position `start`
        answer[start] = x;
        for (int dist = 1; dist < n; dist++) {
            int i = (start + dist) % n;
            int prev = answer[(i-1+n)%n];
            if (std::binary_search(all(numbers[i]),prev)) {
                answer[i] = prev;
            } else {
                int next = (i+1)%n;
                for (auto it : numbers[i]) {
                    auto found = std::binary_search(all(numbers[next]),it);
                    if (found && (answer[next] == 0 || answer[next] == it)) {
                        answer[i] = it;
                        break;
                    }
                }
                if (!answer[i]) {
                    for (auto it : numbers[i]) {
                        auto found = std::binary_search(all(numbers[next]),it);
                        if (!found) {
                            answer[i] = it;
                            break;
                        }
                    }
                }
                if (!answer[i]) return false;
            }
        }
        return true;
    };
    // solution: brute all numbers for position 'start':
    bool found = false;
    for (int x : numbers[start]) {
        if (play(x)) {
            found = 1;
            break;
        }
    }
    assert(found);
    // print answer:
    for (auto it : answer) std::cout << it << ' ';
    std::cout << std::endl;
    return 0;
}