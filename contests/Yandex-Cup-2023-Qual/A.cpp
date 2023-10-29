#include "template.hpp"
int main() {
    int n; std::cin >> n;
    vi a(n); std::cin >> a;
    vi lastPos(1e6+1, -1);
    for (int i = 0; i < n; i++)
        lastPos[a[i]] = i;
    int pos = -1;
    int answ{};
    for (int item = 1; item <= 1e6; item++) {
        if (lastPos[item] > pos) {
            answ++;
            pos = lastPos[item];
        } else {
            break;
        }
    }
    std::cout << answ << std::endl;
}
