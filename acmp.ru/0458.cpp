/*
    Задача: 458. Шифровка - 2
    
    Решение: строки, реализация, O(n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

bool isSpaceNeeded(int rowIndex, int height, int length);
std::string insertSpaces(const int height, const std::vector<int>& order, const std::string& s);

int main() {
    int height; std::cin >> height;
    std::vector<int> order(height);
    for (int i = 0; i < height; ++i) {
        std::cin >> order[i];
        order[i]--;
    }
    std::string s; std::cin >> s;
    s = insertSpaces(height, order, s);
    std::vector<int> newOrder(height);
    for (int idRow = 0; idRow < height; ++idRow) {
        newOrder[order[idRow]] = idRow;
    }
    const int rowLength = (int)s.size() / height;
    for (int idCol = 0; idCol < rowLength; ++idCol) {
        for (int idRow = 0; idRow < height; ++idRow) {
            int x = newOrder[idRow] * rowLength + idCol;
            if (s[x] != ' ') {
                std::cout << s[x];
            }
        }
    }
    return 0;
}

bool isSpaceNeeded(int rowIndex, int height, int length) {
    if (length % height == 0) {
        return false;
    }
    if (rowIndex >= length % height) {
        return true;
    }
    return false;
}

std::string insertSpaces(const int height, const std::vector<int>& order, const std::string& s) {
    std::string answer;
    int begin = 0;
    const int rowLength = ((int)s.size() + height - 1) / height;
    for (int idRow : order) {
        bool need = isSpaceNeeded(idRow, height, (int)s.size());
        int newBegin = (need ? begin + rowLength - 1 : begin + rowLength);
        answer += s.substr(begin, newBegin - begin);
        if (need) {
            answer += " ";
        }
        begin = newBegin;
    }
    return answer;
}