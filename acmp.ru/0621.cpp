#pragma GCC diagnostic ignored "-Wunused-result"
  
#include <stdio.h>
#include <bits/stdc++.h>
  
char getChar() {
    static char buf[1024*1024];
    static int pos = 0;
    static int size = 0;
    if (size == pos) {
        size = fread(buf, 1, 1024*1024, stdin);
        pos = 0;
    }
    if (size == pos) {
        return EOF;
    }
    return buf[pos++];
}
  
int getInt() {
    int sign = 1;
    char c = '?';
    while (!(c == '-' || ('0' <= c && c <= '9'))) {
        c = getChar();
    }
    if (c == '-') {
        sign = -1;
        c = getChar();
    }
    int answ = 0;
    while ('0' <= c && c <= '9') {
        (answ *= 10) += (c - '0');
        c = getChar();
    }
    return answ * sign;
}
  
void putChar(char c) {
    static char buf[1024*1024];
    static int size = 0;
    if (c == -1 || size == 1024*1024) {
        fwrite(buf, 1, size, stdout);
        size = 0;
    }
    if (c != -1) buf[size++] = c;
}
  
void putInt(int num) {
    char buf[10]; sprintf(buf, "%d", num);
    for (int i = 0; buf[i] != '\0'; ++i)
        putChar(buf[i]);
}
  
int main() {
    int n = getInt();
    std::vector<std::vector<int>> field(n, std::vector<int>(n));
      
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            field[i][j] = getInt();
        }
    }
    
    // Для каждой позиции [i][j] посчитаем ближайшие слева и справа ненулевые элементы:
    std::vector<std::vector<int>> left(n, std::vector<int>(n, -1));
    auto right = left;
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            left[i][j] = field[i][j-1] == 0 ? left[i][j-1] : j-1;
        }
        if (field[i].back() != 0) {
            right[i].back() = n-1;
        }
        for (int j = n-2; j >= 0; --j) {
            right[i][j] = field[i][j] == 0 ? right[i][j+1] : j;
        }
    }
    
      
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (field[row][col] != 0) continue;
            int minRow = -1, minCol = -1, minCount = 0, minDist = (int)1e9;
            // Пройдем по строчкам. На синтересуют ближайшие слева и справа ненулевые элементы для текущего столбца
            for (int r = 0; r < n; ++r) {
                int prev = left[r][col];
                if (prev != -1) {
                    int dist = std::abs(row - r) + std::abs(col - prev);
                    if (dist < minDist) {
                        minDist = dist, minRow = r, minCol = prev, minCount = 1;
                    } else if (dist == minDist) {
                        assert(minCount > 0); minCount++;
                    }
                }
                int curr = right[r][col];
                if (curr != -1) {
                    int dist = std::abs(row - r) + std::abs(col - curr);
                    if (dist < minDist) {
                        minDist = dist, minRow = r, minCol = curr, minCount = 1;
                    } else if (dist == minDist) {
                        assert(minCount > 0); minCount++;
                    }
                }
            }
            if (minCount == 1) {
                field[row][col] = field[minRow][minCol];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            putInt(field[i][j]);
            putChar(' ');
        }
        putChar('\n');
    }
    putChar(-1);
      
    return 0;
}