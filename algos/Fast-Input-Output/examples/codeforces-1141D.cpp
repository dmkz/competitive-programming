#include <bits/stdc++.h>
namespace FastIO {
    struct Reader {
    private:
        FILE* file; std::vector<char> buffer; int pos; bool was;
        void read() {
            if (!buffer.empty()) {
                buffer.resize(fread(&buffer[0], 1, (int)buffer.size(), file)); pos = 0; 
            }
        }
    public:
        Reader(FILE* file_ = stdin, const int size_ = 1 << 16)
            : file(file_), buffer(size_, '\0'), pos(size_), was(true) { }
        operator bool() const { return was; }
        char getChar() {
            if (pos == (int)buffer.size()) { read(); }
            if (pos == (int)buffer.size()) { was = false; return EOF; } 
            else { was = true; return buffer[pos++]; }
        }
        std::string getStr() {
            char c = ' ';
            while (std::isspace(c)) { c = getChar(); }
            std::string answ;
            while (c != EOF && !std::isspace(c)) { answ.push_back(c); c = getChar(); }
            was = !answ.empty();
            return answ;
        }
        std::string getLine() {
            char c = '\n';
            while (c == '\n') { c = getChar(); }
            std::string answ;
            while (c != '\n' && c != EOF) { answ.push_back(c); c = getChar(); }
            was = !answ.empty();
            return answ;
        }
        template<typename T> T getInt() {
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
        template<typename T> T getReal() {
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
    };
    
    Reader& operator>>(Reader& reader, char& c) { return c = reader.getChar(), reader; }
    
    Reader& operator>>(Reader& reader, std::string& s) { return s = reader.getStr(), reader; }
    
    template<class T> typename std::enable_if<std::is_floating_point<T>::value, Reader&>::type
    operator>>(Reader& reader, T& t) { return t = reader.getReal<T>(), reader; }
    
    template<class T> typename std::enable_if<std::is_integral<T>::value, Reader&>::type
    operator>>(Reader& reader, T& t) { return t = reader.getInt<T>(), reader; }
    
    template<class T> Reader& operator>>(Reader& reader, std::vector<T>& vec) {
        for (auto &it : vec) { reader >> it; }
        return reader;
    }
    
    struct Writer {
    private:
        FILE* file; std::vector<char> buffer; int pos;
        int defaultPrecision, defaultWidth; char defaultFill;
    public:
        Writer(FILE* file_ = stdout, const int size_ = 1 << 16) 
            : file(file_), buffer(size_, '\0'), pos(0), defaultPrecision(6), defaultWidth(0), defaultFill(' ') { }
        ~Writer() { flush(); }
        void flush() { putChar(EOF); }
        void setprecision(int precision) { defaultPrecision = precision; }
        void setw(int width) { defaultWidth = width; }
        void setfill(char fill) { defaultFill = fill; }
        int getPrecision() const { return defaultPrecision; }
        int getWidth() const { return defaultWidth; }
        char getFill() const { return defaultFill; }
        void putChar(char c) {
            if (pos == (int)buffer.size() || c == EOF) { 
                fwrite(&buffer[0], 1, pos, file); pos = 0; 
            }
            if (c != EOF) { buffer[pos++] = c; }
        }
        void putStr(const std::string& s) { for (auto it : s) putChar(it); }
        template<typename T> void putInt(T value, int width = 0, char fill = ' ') {
            bool positive = !(value < 0);
            if (value < 0) { value = -value; }
            char buf[24]; int p = 0;
            do { buf[p++] = char(value % 10 + '0'); value /= 10; } while (value > 0);
            if (!positive) { buf[p++] = '-'; }
            while (p < width) buf[p++] = fill;
            while (p > 0) putChar(buf[--p]);
        }
        template<typename T> void putReal(T value, int precision = 6, int width = 0, char fill = ' ') {
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
    };
    
    Writer& operator<<(Writer& writer, const char c) { return writer.putChar(c), writer; }
    
    Writer& operator<<(Writer& writer, const std::string& s) { return writer.putStr(s), writer; }
    
    template<class T> typename std::enable_if<std::is_floating_point<T>::value, Writer&>::type
    operator<<(Writer& writer, const T& t) {
        writer.putReal(t, writer.getPrecision(), writer.getWidth(), writer.getFill());
        return writer; 
    }
    
    template<class T> typename std::enable_if<std::is_integral<T>::value, Writer&>::type
    operator<<(Writer& writer, const T& t) { 
        writer.putInt(t, writer.getWidth(), writer.getFill());
        return writer;
    }
}

int main() {
    FastIO::Reader fin;
    FastIO::Writer fout;
    typedef std::vector<int> vi;
    typedef std::pair<int,int> pii;
    for (int n; fin >> n; fout << '\n') {
        std::string fi, se;
        fin >> fi >> se;
        std::map<char, vi> fiCnt, seCnt;
        for (int i = 0; i < n; ++i) {
            fiCnt[fi[i]].push_back(i+1);
        }
        for (int i = 0; i < n; ++i) {
            seCnt[se[i]].push_back(i+1);
        }
        std::vector<pii> answ;
        for (char c = 'a'; c <= 'z'; ++c) {
            while (!(fiCnt[c].empty() || seCnt[c].empty())) {
                answ.push_back(pii(fiCnt[c].back(), seCnt[c].back()));
                fiCnt[c].pop_back();
                seCnt[c].pop_back();
            }
        }
        for (char c = 'a'; c <= 'z'; ++c) {
            vi& first = fiCnt[c];
            vi& second = seCnt['?'];
            while (!(first.empty() || second.empty())) {
                answ.push_back(pii(first.back(), second.back()));
                first.pop_back();
                second.pop_back();
            }
        }
        for (char c = 'a'; c <= 'z'; ++c) {
            vi& first = fiCnt['?'];
            vi& second = seCnt[c];
            while (!(first.empty() || second.empty())) {
                answ.push_back(pii(first.back(), second.back()));
                first.pop_back();
                second.pop_back();
            }
        }
        {
            vi& first = fiCnt['?'];
            vi& second = seCnt['?'];
            while (!(first.empty() || second.empty())) {
                answ.push_back(pii(first.back(), second.back()));
                first.pop_back();
                second.pop_back();
            }
        }
        fout << answ.size() << '\n';
        for (auto &p : answ) {
            fout << p.first << ' ' << p.second << '\n';
        }
    }
    return 0;
}