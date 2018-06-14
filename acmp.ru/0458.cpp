#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>

int main() {
    // Чтение кол-ва строк в таблице и порядок их заполнения:
    int n;
    scanf("%d", &n);
    std::vector<int> order(n);
    for (auto& it : order) {
        scanf("%d", &it); --it;
    }
    // Чтение входной строки:
    char buf[201];
    scanf("%200s", buf);
    std::string s(buf);
    int len = s.size();
    // Выделение памяти под таблицу:
    std::vector<std::string> table(n, std::string(len / n, ' '));
    for (int i = 0; i < len % n; ++i) {
        table[i].push_back(' ');
    }
    // Заполнение таблицы:
    int pos = 0;
    for (auto it : order) {
        const int size = table[it].size();
        table[it] = s.substr(pos, size);
        pos += size;
    }
    // Формирование и вывод ответа:
    std::stringstream answer;
    int row = 0, col = 0;
    while (len--) {
        answer << table[row][col];
        ++row;
        if (row == n) {
            ++col;
            row = 0;
        }
    }
    printf("%s", answer.str().c_str());
    return 0;
}