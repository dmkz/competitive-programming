#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
   
typedef long long ll;

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
   
int getInt() {
    char c = '?';
    while (!(c == '-' || ('0' <= c && c <= '9'))) {
        c = getChar();
    }
    bool positive = true;
    if (c == '-') {
        positive = false;
        c = getChar();
    }
    int answ = 0;
    while ('0' <= c && c <= '9') {
        (answ *= 10) += (c - '0');
        c = getChar();
    }
    return positive ? answ : -answ;
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
   
void putInt(ll number) {
    if (number == 0) {
        putChar('0');
        return;
    }
    if (number < 0) {
        putChar('-');
        number = -number;
    }
    char buf[24]; int pos = 0;
    do {
        buf[pos++] = number % 10 + '0';
        number /= 10;
    } while (number > 0);
    --pos;
    while (pos >= 0) {
        putChar(buf[pos]);
        --pos;
    }
}
   
   
struct Group {
    ll sum, sum2, count;
        
    void add(int value) {
        sum += value;
        sum2 += ll(value)*value;
        count++;
    }
};
    
struct SqrtDecomposition {
    std::vector<ll> arr;
    std::vector<Group> group1;
    std::vector<Group> group2;
       
    const int GSIZE1 = 128;
    const int COEFF = 64;
    const int GSIZE2 = GSIZE1 * COEFF;
       
        
    SqrtDecomposition(const int size) {
        arr.assign(size, 0);
        group1.assign((size + GSIZE1-1)/GSIZE1, Group{0,0,0});
        group2.assign((size + GSIZE2-1)/GSIZE2, Group{0,0,0});
    }
        
    void push1(int g) {
        const int begin = g*GSIZE1;
        const int after = std::min((g+1)*GSIZE1, (int)arr.size());
        const auto& gr = group1[g];
        arr[begin] += gr.sum2;
        ll curr = gr.sum2;
        for (int i = begin+1; i < after; ++i) {
            const int p = i - begin - 1;
            curr += gr.count * (1 + 2 * p) + 2 * gr.sum;
            arr[i] += curr;
        }
    }
       
    void push2(int g) {
        const int begin = g*GSIZE2;
        const int after = std::min((g+1)*GSIZE2, (int)arr.size());
        const auto& gr = group2[g];
        arr[begin] += gr.sum2;
        ll curr = gr.sum2;
        for (int i = begin+1; i < after; ++i) {
            const int p = i - begin - 1;
            curr += gr.count * (1 + 2 * p) + 2 * gr.sum;
            arr[i] += curr;
        }
    }
        
    void push_all() {
        for (int g = 0; g < (int)group1.size(); ++g) {
            push1(g);
        }
        for (int g = 0; g < (int)group2.size(); ++g) {
            push2(g);
        }
    }
        
    void inc(int left, int right) {
        const int gl = left / GSIZE1;
        const int gr = right / GSIZE1;
        if (gl == gr) {
            for (int i = left; i <= right; ++i) {
                arr[i] += ll(i-left+1)*(i-left+1);
            }
        } else {
            for (int i = left, limit = (gl+1) * GSIZE1; i < limit; ++i) {
                arr[i] += ll(i-left+1)*(i-left+1);
            }
               
            for (int g = gl+1; g < gr; ) {
                if (g % COEFF == 0 && g + COEFF <= gr) {
                    group2[g / COEFF].add(g*GSIZE1-left+1);
                    g += COEFF;
                } else {
                    group1[g].add(g*GSIZE1-left+1);
                    ++g;
                }
            }
   
            for (int i = gr*GSIZE1; i <= right; ++i) {
                arr[i] += ll(i-left+1)*(i-left+1);
            }
        }
    }
};
    
    
    
int main() {
    double t = clock();
    int n = getInt(), q = getInt();
        
    SqrtDecomposition sdl(n), sdr(n);
        
    while (q--) {
        int begin = getInt()-1, end = getInt()-1;
        if (begin <= end) {
            sdl.inc(begin, end);
        } else {
            sdr.inc(n-1-begin, n-1-end);
        }
    }
    sdl.push_all();
    sdr.push_all();
    std::reverse(sdr.arr.begin(), sdr.arr.end());
    for (int i = 0; i < n; ++i) {
        putInt(sdl.arr[i]+sdr.arr[i]);
        putChar('\n');
    }
    putChar(-1);
    //std::cerr << "time = " << (clock() - t) / CLOCKS_PER_SEC;
    return 0;
}