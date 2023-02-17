#pragma once
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

uint64_t date2number(std::string s)
{
    static std::map<std::string, uint64_t> month =
    {
        {"Jan", 1},
        {"Feb", 2},
        {"Mar", 3},
        {"Apr", 4},
        {"May", 5},
        {"Jun", 6},
        {"Jul", 7},
        {"Aug", 8},
        {"Sep", 9},
        {"Oct",10},
        {"Nov",11},
        {"Dec",12}
    };
    // "Feb/15/2023 19:19"
    char buf[101];
    int d,y,h,m;
    sscanf(s.c_str(), "%3s/%d/%d %d:%d", buf, &d, &y, &h, &m);
    //std::cerr << "s = '" << s << "'" << std::endl;
    //std::cerr << buf << "/" << d << "/" << y << " " << h << ":" << m << std::endl;
    auto it = month.find(buf);
    assert(it != month.end());
    return m + 64ULL * (h + 64ULL * (d + 64ULL * (it->second + 64ULL * y)));
}

void replaceSubstrRef(std::string& s,
                      const std::string &from,
                      const std::string &to)
{
    for (int i = 0; i + isz(from) <= isz(s); i++) {
        if (s.substr(i, isz(from)) == from) {
            s.erase(i, isz(from));
            s.insert(i, to);
        }
    }
    
}
std::string replaceSubstr(std::string s,
                          const std::string &from,
                          const std::string &to)
{
    replaceSubstrRef(s,from,to);
    return s;
}
bool removeBefore(std::string &s,
                  const std::string what,
                  std::string *dst = nullptr) {
    auto p = s.find(what);
    if (p == s.npos)
        return false;
    if (dst) *dst = s.substr(0, p);
    s.erase(0,p+isz(what));
    return true;
}

bool extractBetween(std::string &s,
                    std::string fi,
                    std::string se,
                    std::string &dst)
{
    return removeBefore(s, fi) && removeBefore(s, se, &dst);
}

std::vector<std::string> split(std::string s,
                               const std::string &delimiter)
{
    std::vector<std::string> res;
    while(true) {
        std::string dst;
        bool ok = removeBefore(s, delimiter, &dst);
        if (!ok) break;
        res.push_back(dst);
    }
    return res;
}

std::string fileToString(std::string filename) {
    // std::cerr << "Processing file '" << filename << "'" << std::endl;
    std::ifstream fin(filename);
    std::string result;
    for (std::string s; std::getline(fin, s); result += s);
    return result;
}

void trimRef(std::string &s) {
    for (int rotate = 0; rotate < 2; rotate++) {
        while (isz(s) && std::isspace(s.back())) s.pop_back();
        std::reverse(all(s));
    }
}
std::string trim(std::string s) {
    trimRef(s);
    return s;
}