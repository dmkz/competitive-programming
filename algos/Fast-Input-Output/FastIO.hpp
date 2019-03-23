#pragma once

#include <bits/stdc++.h>

namespace FastIO {
    
    struct Reader {
     
        FILE* file;
       
        std::vector<char> buffer;
       
        int pos;
       
        char last;
       
        void read() { buffer.resize(fread(&buffer[0], 1, (int)buffer.size(), file)); pos = 0; }
       
        Reader(FILE* file_ = stdin, const int size_ = 1 << 16) 
            : file(file_), buffer(size_, '\0'), pos(0), last('?') { read(); }
       
        char getChar() {
            if (pos == (int)buffer.size()) { read(); }
            return last = ((pos == (int)buffer.size()) ? EOF : buffer[pos++]);
        }
        
        template<typename T>
        T getInt() {
            char c = '?';
            while (!(c == '-' || ('0' <= c && c <= '9'))) { c = getChar(); }
            bool positive = true;
            if (c == '-') { positive = false; c = getChar(); }
            T answ(0);
            while ('0' <= c && c <= '9') { (answ *= 10) += (c - '0'); c = getChar(); }
            return positive ? answ : -answ;
        }
       
        template<typename T>
        T getReal() {
            auto high = getInt<int64_t>();
            char c = '?';
            while (!(c == '-' || ('0' <= c && c <= '9'))) { c = getChar(); }
            bool positive = true;
            if (c == '-') {
                positive = false;
                c = getChar();
            }
            long long first = 0;
            while ('0' <= c && c <= '9') { (first *= 10) += (c - '0'); c = getChar(); }
            if (c != '.') {
                return double(positive ? first : -first);
            }
            c = getChar();
            long long second = 0;
            long long pow = 1;
            while ('0' <= c && c <= '9') { (second *= 10) += (c - '0'); c = getChar(); pow *= 10; }
            double answ = first + (double)second / (double)pow;
            return positive ? answ : -answ;
        }
    };
 
struct Output {
 
    FILE* file;
   
    std::vector<char> buffer;
   
    int pos;
   
    Output(FILE* file_, const int size_ = 1024*1024)
        : file(file_)
        , buffer(size_, '\0')
        , pos(0)
    { }
   
    inline void flush() {
        put_char(-1);
    }
   
    inline void put_char(char c) {
        if (pos == (int)buffer.size() || c == -1) {
            fwrite(&buffer[0], 1, pos, file);
            pos = 0;
        }
        if (c != -1) {
    buffer[pos++] = c;
        }
    }
   
    inline void put_int(int value, int len = 0) {
        if (value < 0) {
            put_char('-');
            value = -value;
        }
        char buf[12]; int p = 0;
        do {
            buf[p++] = char(value % 10 + '0');
            value /= 10;
        } while (value > 0);
        while (p < len) buf[p++] = '0';
        while (p > 0) put_char(buf[--p]);
    }
   
    inline void put_ll(long long value, int len = 0) {
        if (value < 0) {
            put_char('-');
            value = -value;
        }
        char buf[12]; int p = 0;
        do {
            buf[p++] = char(value % 10 + '0');
            value /= 10;
        } while (value > 0);
        while (p < len) buf[p++] = '0';
        while (p > 0) put_char(buf[--p]);
    }
   
    inline void put_dbl(double value, int precision = 6) {
        if (value < 0) {
            put_char('-');
            value = -value;
        }
       
        put_ll((long long)value);
        value -= (long long)value;
       
        if (precision == 0) {
            return;
        }
       
        put_char('.');
        while (precision >= 6) {
            value *= 1000000;
            put_int((int)value, 6);
            value -= (int)value;
            precision -= 6;
        }
        while (precision >= 3) {
            value *= 1000;
            put_int((int)value, 3);
            value -= (int)value;
            precision -= 3;
        }
        while (precision >= 1) {
            value *= 10;
            put_char(char((int)value+'0'));
            value -= (int)value;
            precision--;
        }
    }
   
    ~Output() {
        flush();
    }
};
}