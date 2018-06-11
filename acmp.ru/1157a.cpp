#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
#include <iostream>

std::vector<int> manaker(const std::string& original) {
// Алгоритм Манакера нахождения максимальных длин подпалиндромов исходной строки из всех позиций за O(n)
// Возвращает вектор, состоящий из этих длин, в нечетных позициях нечетные длины, в четных позициях - четные, т.е.:
//  - dist[2*i+1] = v означает, что [i-v+1, i+v-1] - палиндром нечетной длины 2*v-1 с центром в позиции i
//  - dist[2*i]   = v означает, что [i-v+1, i+v] - палиндром четной длины 2*v с центром в точках i и i+1

    const char delim = *std::min_element(original.begin(), original.end())-1;
    std::vector<char> copy{delim};
    for (auto& it : original) {
        copy.push_back(it);
        copy.push_back(delim);
    }
    const int n = copy.size();
    std::vector<int> dist(n, 1);
    int left = 0, right = 0;
    for (int i = 1, L, R; i < n; ++i) {
        if (i > right) {
            L = R = i;
        } else {
            int mid = left+right-i;
            R = i+dist[mid]-1;
            L = i-dist[mid]+1;
            if (R > right) {
                L += R-right;
                R = right;
            }
        }
        while (L-1 >= 0 && R+1 < n && copy[L-1] == copy[R+1]) {
            --L, ++R;
        }
        dist[i] = R-i+1;
        if (right < R) {
            left = L, right = R;
        }
    }
    for (auto& it : dist) {
        it /= 2;
    }
    return dist;
}

int main() {
    char buf[100000+1];
    scanf("%100000s", buf);
    std::string s(buf);
    long long answer = 0;
    for (auto it : manaker(s)) {
        answer += it;
    }
    std::cout << answer;
    return 0;
}