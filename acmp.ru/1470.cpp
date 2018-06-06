#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>

typedef std::vector<std::string> Row;
typedef std::vector<Row> Table;

Row parse(std::string s) {
    s = ',' + s + ',';
    Row answer;
    for (int p = 1; p < (int)s.size(); ) {
        if (s[p] == '"') {
            int j = p+1;
            while (true) {
                if (s[j] == '"') {
                    if (s[j+1] == '"') {
                        ++j;
                    } else {
                        break;
                    }
                }
                ++j;
            }
            assert(s[j] == '"');
            auto temp = s.substr(p+1, j-p-1);
            p = j+1;
            assert(s[p] == ',');
            ++p;
            std::string cur;
            for (int i = 0; i < (int)temp.size(); ++i) {
                if (temp[i] == '"') {
                    cur += temp[i];
                    if (i+1 < (int)temp.size() && temp[i+1] == '"') {
                        ++i;
                    }
                } else {
                    cur += temp[i];
                }
            }
            answer.push_back(cur);
        } else {
            int j = p;
            while (s[j] != ',') ++j;
            answer.push_back(s.substr(p, j-p));
            p = j+1;
        }
    }
    return answer;
}

std::string formate(Row& row, const std::vector<int>& width) {
    std::stringstream ss;
    while (row.size() < width.size()) row.push_back("");
    for (int i = 0; i < (int)width.size(); ++i) {
        if (i != 0) {
            ss << '|';
        }
        while ((int)row[i].size() < width[i]) row[i].push_back(' ');
        ss << row[i];
    }
    return ss.str();
}

int main() {
    std::string s;
    Table table;
    std::vector<int> width;
    int nCols = 0;
    while (std::getline(std::cin, s)) {
        while (s.back() == '\n' || s.back() == 13) {
            s.pop_back();
        }
        assert(s.back() != '\n');
        assert(s.back() != 13);
        table.push_back(parse(s));
        const auto& back = table.back();
        // Обновляем количество столбцов:
        nCols = std::max(nCols, (int)back.size());
        while ((int)width.size() < nCols) width.push_back(0);
        // Обновляем максимальную ширину столбца:
        for (int c = 0; c < (int)back.size(); ++c) {
            width[c] = std::max(width[c], (int)back[c].size());
        }
    }
    
    // Выводим ответ:
    for (auto& row : table) {
        std::cout << formate(row, width) << std::endl;
    }
    return 0;
}