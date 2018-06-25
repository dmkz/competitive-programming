#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>

std::string convert(int number, int base) {
    std::string answer;
    do {
        answer.push_back(number % base + '0');
        number /= base;
    } while (number > 0);
    std::reverse(answer.begin(), answer.end());
    return answer;
}

int main() {
    int n;
    scanf("%d", &n);
    std::vector<int> arr;
    while (n--) {
        int value;
        scanf("%d", &value);
        auto s = convert(value, 8);
        if (s.size() < 3u) {
            s = std::string(8, '0') + s;
        }
        if ((s[s.size()-3u]-'0') % 2 == 1 && value % 2 == 0) {
            arr.push_back(value);
        }
    }
    std::sort(arr.begin(), arr.end());
    printf("%d\n", (int)arr.size());
    for (auto& it : arr) {
        printf("%d ", it);
    }
    return 0;
}