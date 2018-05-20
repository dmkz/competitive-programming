#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
 
char getChar() {
    static char buffer[1024*1024];
    static int pos = 0;
    static int size = 0;
    if (pos == size) {
        size = fread(buffer, 1, 1024*1024, stdin);
        pos = 0;
    }
    if (pos == size) {
        return EOF;
    }
    return buffer[pos++];
}
 
int getInt() {
    char c = '?';
    while (!(c == '-' || ('0' <= c && c <= '9'))) {
        c = getChar();
    }
    int sign = 1;
    if (c == '-') {
        sign = -1;
        c = getChar();
    }
    int answ = 0;
    while ('0' <= c && c <= '9') {
        (answ *= 10) += (c - '0');
        c = getChar();
    }
    return sign * answ;
}
 
int main() {
    int n = getInt(), dim = getInt(), need_row = getInt(), need_col = getInt(), mod = getInt(); 
    --need_row, --need_col;
     
    static int answ[130][130], temp[130][130], curr[130][130];
     
    for (int i = 0; i < dim; ++i) {
        answ[i][i] = 1;
    }
     
    for (int id = 0; id < n; ++id) {
        for (int row = 0; row < dim; ++row) {
            for (int col = 0; col < dim; ++col) {
                curr[col][row] = getInt();
            }
        }
        for (int row1 = 0; row1 < dim; ++row1) {
            for (int col1 = 0; col1 < dim; ++col1) {
                int sum = 0;
                for (int k = 0; k < dim; ++k) {
                    sum += answ[row1][k] * curr[col1][k];
                }
                temp[row1][col1] = sum % mod;
            }
        }
        for (int row = 0; row < dim; ++row) {
            for (int col = 0; col < dim; ++col) {
                answ[row][col] = temp[row][col];
            }
        }
    }
     
    printf("%d\n", answ[need_row][need_col]);
     
    return 0;
}