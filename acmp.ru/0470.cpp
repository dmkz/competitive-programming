#include <stdio.h>
#include <cstdlib> 
#include <string>
 
char getChar() {
    static char buf[1 << 20];
    static int pos = 0;
    static int size = 0;
    if (pos == size) {
        size = fread(buf, 1, 1 << 20, stdin);
        pos = 0;
    }
    if (pos == size) {
        return EOF;
    }
    return buf[pos++];
}
 
 
template<typename T>
inline void read(T& v) {
    char c = '?';
    while (!(c == '-' || ('0' <= c && c <= '9'))) c = getChar();
    bool positive = true;
    if (c == '-') {
        positive = false;
        c = getChar();
    }
    v = 0;
    while ('0' <= c && c <= '9') {
        (v *= 10) += (c - '0');
        c = getChar();
    }
    if (!positive) v = -v;
}
 
void putChar(char c) {
    static char buf[1 << 20];
    static int size = 0;
    if (size == 1 << 20 || c == -1) {
        fwrite(buf, 1, size, stdout);
        size = 0;
    }
    if (c != -1) {
        buf[size++] = c;
    }
}
 
inline void writeln(int v) {
    char buf[15];
    sprintf(buf, "%d\n", v);
    for (char* cur = buf; *cur != '\0'; ++cur) {
        putChar(*cur);
    }
}
 
int main() {    
    int nRows, nCols, nQueries;
    read(nRows), read(nCols), read(nQueries);
     
    static int sum[1+100][1+100];
    for (int r = 1; r <= nRows; ++r) {
        for (int c = 1; c <= nCols; ++c) {
            int value;
            read(value);
            sum[r][c] = sum[r-1][c]+sum[r][c-1]-sum[r-1][c-1]+value;
        }
    }
     
    while (nQueries--) {
        int r1, c1, r2, c2;
        read(r1), read(c1), read(r2), read(c2);
        writeln(sum[r2][c2] - sum[r1-1][c2] - sum[r2][c1-1] + sum[r1-1][c1-1]);
    }
    putChar(-1);
    return 0;
}