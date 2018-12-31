/*
    Problem: 576C. Points on Plane
    
    Solution: constructive, geometry, Mo's algorithm, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

namespace Codeforces {
    char getChar();
    void putChar(char);
    template<typename T> T getInt();
    template<typename T> void putInt(T);
}

struct Point {
    int x, y, id, ix, iy;
};

int main() {
    using namespace Codeforces;
    int n = getInt<int>();
    std::vector<Point> arr(n);
    for (int i = 1; i <= n; ++i) {
        auto &it = arr[i-1];
        it.x = getInt<int>();
        it.y = getInt<int>();
        it.id = i;
        it.ix = it.x / 1000;
        it.iy = it.y / 1000;
    }
    std::stable_sort(arr.begin(), arr.end(), [](const Point& a, const Point& b){
       if (a.ix < b.ix) return true;
       if (a.ix > b.ix) return false;
       if (a.iy < b.iy) return !!(a.ix % 2);
       if (a.iy > b.iy) return !(a.ix % 2);
       if (a.y < b.y) return !!(a.ix % 2);
       if (a.y > b.y) return !(a.ix % 2);
       if (a.x < b.x) return !!(a.y % 2);
       if (a.x > b.x) return !(a.y % 2);
       return false;
    });
    
    for (auto& it : arr) {
        putInt(it.id);
        putChar(' ');
    }
    putChar(-1);
    return 0;
}

// --------------------------------------------------------------------------------
namespace Codeforces {
    void putChar(char c) {
        static const int SIZE = 1 << 16;
        static char buffer[SIZE];
        static int size = 0;
        if (size == SIZE || c == EOF) {
            fwrite(buffer, 1, size, stdout);
            size = 0;
        }
        if (c != EOF) {
            buffer[size++] = c;
        }
    }

    template<typename T>
    void putInt(T value) {
        static char stack[24];
        bool positive = true;
        if (value < 0) {
            positive = false;
            value = -value;
        }
        int pos = 0;
        do {
            stack[pos++] = char((value % 10) + '0');
            value /= 10;
        } while (value > 0);
        if (!positive) {
            stack[pos++] = '-';
        }
        while (pos--) {
            putChar(stack[pos]);
        }
    }

    char getChar() {
        static const int SIZE = 1 << 16;
        static char buffer[SIZE];
        static int pos = 0;
        static int size = 0;
        if (size == pos) {
            size = (int)fread(buffer, 1, SIZE, stdin);
            pos = 0;
        }
        if (size == pos) {
            return EOF;
        }
        return buffer[pos++];
    }

    template<typename T>
    T getInt() {
        char c = '?';
        while (!(c == '-' || ('0' <= c && c <= '9'))) { c = getChar(); }
        bool positive = true;
        if (c == '-') {
            positive = false; c = getChar();
        }
        T res = 0;
        while ('0' <= c && c <= '9') {
            (res *= 10) += (c - '0');
            c = getChar();
        }
        return positive ? res : -res;
    }
}