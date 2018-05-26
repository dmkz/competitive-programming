#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

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

void putChar(char c) {
    static char buffer[1024*1024];
    static int size = 0;
    if (size == 1024*1024 || c == -1) {
        fwrite(buffer, 1, size, stdout);
        size = 0;
    }
    if (c != -1) {
        buffer[size++] = c;
    }
}

int getInt() {
    char c = '?';
    while (!(c == '-' || ('0' <= c && c <= '9'))) c = getChar();
    bool positive = true;
    if (c == '-') {
        positive = false;
        c = getChar();
    }
    int value = 0;
    while ('0' <= c && c <= '9') {
        (value *= 10) += (c - '0');
        c = getChar();
    }
    return positive ? value : -value;
}

void putInt(int number) {
    static char buf[12];
    sprintf(buf, "%d", number);
    for (char* it = buf; *it != '\0'; ++it) {
        putChar(*it);
    }
}

struct DataStruct {
    std::vector<int> arr, max, actual;
    
    const int GSIZE = 256;
    
    DataStruct(int size = 0, int item = 0) {
        arr.assign(size, item);
        max.assign((size+GSIZE-1) / GSIZE, item);
        actual.assign((size+GSIZE-1) / GSIZE, true);
    }
    
    void update_group(int g) {
        if (actual[g]) return;
        actual[g] = true;
        const int begin = g * GSIZE;
        const int after = std::min(begin+GSIZE, (int)arr.size());
        int value = arr[begin];
        for (int i = begin+1; i < after; ++i) {
            value = std::max(value, arr[i]);
        }
        max[g] = value;
    }
    
    void set(int p, int v) {
        const int g = p / GSIZE;
        arr[p] = v;
        actual[g] = false;
    }
    
    int get(int l, int r) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        int answ = arr[l];
        if (gl == gr) {
            for (int i = l; i <= r; ++i) {
                answ = std::max(answ, arr[i]);
            }
        } else {
            for (int i = l, after = (gl+1)*GSIZE; i < after; ++i) {
                answ = std::max(answ, arr[i]);
            }
            for (int g = gl+1; g < gr; ++g) {
                if (!actual[g]) update_group(g);
                answ = std::max(answ, max[g]);
            }
            for (int i = gr * GSIZE; i <= r; ++i) {
                answ = std::max(answ, arr[i]);
            }
        }
        return answ;
    }
    
};

int main() {
    int n = getInt(); 
    DataStruct ds(n, 0);
    for (int i = 0; i < n; ++i) {
        int value = getInt();
        ds.set(i, value);
    }
    int q = getInt();
    while (q--) {
        int l = getInt()-1, r = getInt()-1;
        putInt(ds.get(l, r));
        putChar(' ');
    }
    putChar(-1);
    return 0;
}