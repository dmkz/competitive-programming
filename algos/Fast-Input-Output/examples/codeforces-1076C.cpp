#include <bits/stdc++.h>

typedef long double ld;
int main() {    
    FastIO::Reader cin;
    FastIO::Writer cout;
    cout.setprecision(12);
    for (int t; cin >> t; cout << '\n') {
        while (t--) {
            int d; cin >> d;
            if (d * d - 4 * d < 0) {
                cout << "N\n";
            } else {
                ld b1 = ld(d - std::sqrt(d*d-4*d))/2;
                ld a1 = d - b1;
                assert(a1 >= 0 && b1 >= 0);
                cout << "Y " << a1 << ' ' << b1 << '\n';
            }
        }
    }
    return 0;
}
       
    void Reader::read() {
        if (!buffer.empty()) {
            buffer.resize(fread(&buffer[0], 1, (int)buffer.size(), file)); pos = 0; 
        }
    }
       
    char Reader::getChar() {
        if (pos == (int)buffer.size()) { read(); }
        if (pos == (int)buffer.size()) { was = false; return EOF; } 
        else { was = true; return buffer[pos++]; }
    }
        
    std::string Reader::getStr() {
        char c = ' ';
        while (std::isspace(c)) { c = getChar(); }
        std::string answ;
        while (c != EOF && !std::isspace(c)) { answ.push_back(c); c = getChar(); }
        was = !answ.empty();
        return answ;
    }
    
    std::string Reader::getLine() {
        char c = '\n';
        while (c == '\n') { c = getChar(); }
        std::string answ;
        while (c != '\n' && c != EOF) { answ.push_back(c); c = getChar(); }
        was = !answ.empty();
        return answ;
    }
        
    template<typename T>
    T Reader::getInt() {
        char c = '?';
        while (!(c == '-' || ('0' <= c && c <= '9') || c == EOF)) { c = getChar(); }
        bool positive = true;
        if (c == '-') { positive = false; c = getChar(); }
        T answ(0);
        bool flag = false;
        while ('0' <= c && c <= '9') { flag = true; (answ *= 10) += (c - '0'); c = getChar(); }
        was = flag;
        return positive ? answ : -answ;
    }
   
    template<typename T>
    T Reader::getReal() {
        bool flag = false;
        char c = '?';
        while (!(c == '-' || ('0' <= c && c <= '9') || c == EOF)) { c = getChar(); }
        bool positive = (c != '-');
        if (c == '-') { c = getChar(); }
        long long first = 0;
        while ('0' <= c && c <= '9') { flag = true; (first *= 10) += (c - '0'); c = getChar(); }
        was = flag;
        if (c != '.') { return T(positive ? first : -first); }
        c = getChar();
        long long second = 0, pow = 1;
        while ('0' <= c && c <= '9') { (second *= 10) += (c - '0'); c = getChar(); pow *= 10; }
        T answ = first + (T)second / (T)pow;
        return positive ? answ : -answ;
    }
    
    void Writer::putChar(char c) {
        if (pos == (int)buffer.size() || c == EOF) { 
            fwrite(&buffer[0], 1, pos, file); pos = 0; 
        }
        if (c != EOF) { buffer[pos++] = c; }
    }
    
    void Writer::putStr(const std::string& s) {
        for (auto it : s) { 
            putChar(it); 
        } 
    }
    
    template<typename T>
    void Writer::putInt(T value, int width, char fill) {
        bool positive = !(value < 0);
        if (value < 0) { value = -value; }
        char buf[24]; int p = 0;
        do { buf[p++] = char(value % 10 + '0'); value /= 10; } while (value > 0);
        if (!positive) { buf[p++] = '-'; }
        while (p < width) buf[p++] = fill;
        while (p > 0) putChar(buf[--p]);
    }
    
    template<typename T>
    void Writer::putReal(T value, int precision, int width, char fill) {
        putInt((long long)value, width - precision - 1, fill); 
        value = std::abs(value-(long long)value);
        if (precision == 0) { return; }
        putChar('.');
        #define PRINT_PART(cnt, pow) \
            while (precision >= cnt) { \
                value *= pow; \
                putInt((int)value, cnt, '0'); \
                value -= (int)value; \
                precision -= cnt; \
            }
        PRINT_PART(6,1000000)
        PRINT_PART(3,1000)
        PRINT_PART(1,10)
        #undef PRINT_PART
    }
}