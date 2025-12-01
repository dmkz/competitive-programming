#include <bits/stdc++.h>
void solveEasy() {
    std::string s;
    int pos = 50, answer{};
    while (std::getline(std::cin, s)) {
        char ch; int cnt;
        int code = sscanf(s.c_str(), "%c%d", &ch, &cnt);
        assert(code == 2);
        assert(ch == 'R' || ch == 'L');
        int next = pos + (ch == 'R' ? cnt : -cnt);
        next %= 100;
        if (next < 0)
            next += 100;
        answer += (next == 0);
        pos = next;
    }
    std::cout << answer << std::endl;
}
int countZeros(int L, int R) {
    if (L > R) std::swap(L, R);
    //std::cout << "calc on [" << L << ", ..., " << R << "]" << std::endl;
    // количество нулей по модулю 100:
    // -200, -100, 0, 100, 200, 300, ...
    // R >= k * 100 >= L
    // kmax * 100 <= R => kmax <= R / 100
    int kmax = (int)std::floor(R / 100.0);
    // L <= kmin * 100 => kmin >= L / 100
    int kmin = (int)std::ceil(L / 100.0);
    return std::max<int>(0, kmax - kmin + 1);
}
void solveHard() {
    std::string s;
    int curr = 50, answer{};
    while (std::getline(std::cin, s)) {
        char ch; int cnt;
        int code = sscanf(s.c_str(), "%c%d", &ch, &cnt);
        assert(code == 2);
        assert(ch == 'R' || ch == 'L');
        int next = curr + (ch == 'R' ? cnt : -cnt);
        // считаем сколько нулей на отрезке
        int delta = countZeros(curr + (ch == 'R' ? +1 : -1), next); 
        next %= 100;
        if (next < 0)
            next += 100;
        //std::cout << curr << " --> " << next << ": " << delta << std::endl;
        curr = next;
        answer += delta;
    }
    std::cout << answer << std::endl;
}
main() {
    solveHard();
}
