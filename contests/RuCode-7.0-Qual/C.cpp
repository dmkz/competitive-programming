#include "template.hpp"
int main() {
    int n; std::cin >> n;
    int low = 1;
    int high = n+1;
    // y >= low - всегда
    // y < high - всегда
    // ответ: low!
    while (high - low > 1) {
        int mid = (low+high)/2;
        std::cout << "? " << mid << std::endl;
        std::string s; std::cin >> s;
        if (s == "<") high = mid;
        else low = mid;
    }
    std::cout << "! " << low << std::endl;
}
