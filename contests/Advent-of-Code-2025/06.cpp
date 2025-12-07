#include <bits/stdc++.h>
void solveEasy() {
    std::string s;
    std::vector<std::vector<int>> numbers;
    int64_t answ{};
    while (std::getline(std::cin, s)) {
        std::vector<int> x;
        [&](){
            std::stringstream ss(s);
            for (int a; ss >> a; x.push_back(a));
        }();
        if (x.empty()) {
            std::stringstream ss(s);
            std::vector<char> op;
            for (char ch; ss >> ch; op.push_back(ch));
            assert(numbers.size());
            assert(op.size() == numbers.front().size());
            for (int i = 0; i < (int)op.size(); i++) {
                if (op[i] == '*') {
                    int64_t prod = 1;
                    for (int j = 0; j < (int)numbers.size(); j++)
                        prod *= numbers[j][i];
                    answ += prod;
                } else {
                    assert(op[i] == '+');
                    int64_t sum = 0;
                    for (int j = 0; j < (int)numbers.size(); j++)
                        sum += numbers[j][i];
                    answ += sum;
                }
            }
        } else {
            numbers.push_back(x);
        }
    }
    std::cout << answ << std::endl;
}
void solveHard() {
    std::string s;
    std::vector<std::string> data;
    int64_t answ{};
    while (std::getline(std::cin, s))
        if (s.size())
            data.push_back(s);
    const int nRows = (int)data.size();
    const int nCols = (int)data[0].size();
    for (int i = 1; i < nRows; i++)
        assert((int)data[i].size() == nCols);
    for (int i = 0; i < nRows; i++)
        if (std::isspace(data[i].back()) == false)
            data[i] += ' ';
    auto isSpaceColumn = [&](int j) {
        for (int i = 0; i < nRows; i++)
            if (!std::isspace(data[i][j]))
                return false;
        return true;
    };
    for (int i = 0, j; i < nCols; i = j) {
        assert(data.back()[i] == '*' || data.back()[i] == '+');
        for (j = i; j < nCols && !isSpaceColumn(j); j++);
        std::vector<int> x;
        for (int k = i; k < j; k++) {
            x.push_back(0);
            for (int r = 0; r < nRows - 1; r++) {
                if (std::isspace(data[r][k]))
                    continue;
                (x.back() *= 10) += (data[r][k] - '0');
            }
        }
        if (char op = data.back()[i]; op == '*') {
            int64_t prod = 1;
            for (auto it : x)
                prod *= it;
            answ += prod;
        } else {
            assert(op == '+');
            int64_t sum = 0;
            for (auto it : x)
                sum += it;
            answ += sum;
        }
        j++;
    }
    std::cout << answ << std::endl;
}
main() {
    solveHard();
}
