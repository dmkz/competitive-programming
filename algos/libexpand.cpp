#include <bits/stdc++.h>
const std::string libpath = "C:\\Users\\dkozyrev\\Documents\\GitHub\\competitive-programming\\algos";
namespace fs = std::filesystem;
bool isSuffix(std::string where, std::string what) {
    if (what.size() > where.size())return false;
    return where.substr(where.size()-what.size(),what.size()) == what;
}
bool remPrefix(std::string& where, std::string what) {
    if (auto p = where.find(what); p != where.npos) {
        where = where.substr(p + what.size());
        return true;
    }
    return false;
}
std::map<std::string, std::string> headers;
std::string tolower(std::string s) {
    for (auto &it : s) {
        if ('A' <= it && it <= 'Z')
            it = (char)std::tolower(it);
    }
    return s;
}
void scanFiles() {
    // Iterate over the `std::filesystem::directory_entry` elements explicitly
    std::cout << "List of hpp files: {";
    bool isFirst = true;
    for (const fs::directory_entry& dir_entry : 
        fs::recursive_directory_iterator(libpath))
    {
        auto path = dir_entry.path().string();
        auto filename = dir_entry.path().filename().string();
        if (isSuffix(filename, "hpp"))
        {
            auto key = tolower(filename);
            headers[key] = path;
            if (!isFirst) {
                std::cout << ", ";
            } else isFirst = false;
            std::cout << filename;
        }
    }
    std::cout << "}\\n";
}
std::string trim(std::string s) {
    //while (s.size() && std::isspace(s.back())) s.pop_back();
    int p = 0;
    char prev = ' ';
    for (int i = 0; i < (int)s.size(); i++) {
        if (std::isspace(s[i]) && std::isspace(prev))
            continue;
        prev = s[p++] = s[i];
    }
    s.resize(p);
    while (p - 1 >= 0 && std::isspace(s[p-1])) {
        p--;
        s.pop_back();
    }
    return s;
}

auto fileToStrings(std::string path) {
    std::ifstream fin(path);
    std::vector<std::string> res;
    std::string s;
    while(std::getline(fin, s)) {
        res.emplace_back(s);
    }
    return res;
}

void writeFile(std::string path, const std::vector<std::string>& content) {
    std::ofstream fout(path);
    for (auto &it : content) {
        fout << it << '\\n';
    }
    std::cout << content.size() << " lines have been written." << std::endl;
}

auto expandFile(std::string path) {
    std::ifstream fin(path);
    std::string s;
    std::vector<std::string> result;
    while(std::getline(fin, s)) {
        auto t = trim(s);
        if (remPrefix(t, "#include \\"")) {
            while (t.size() && t.back() == '\\"') t.pop_back();
            int p = (int)t.size()-1;
            while (p >= 0 && t[p] != '/') p--;
            if (p >= 0) {
                t = t.substr(p+1);
            }
            t = tolower(t);
            if (auto it = headers.find(t); it != headers.end())
            {
                std::cout << "Header '" << t << "' " << "have been found." << std::endl;
                for (const auto &line : fileToStrings(it->second))
                {
                    result.emplace_back(line);
                }
                continue;
            }
        }
        result.push_back(s);
    }
    return result;
}
auto collapseFile(std::string path, const std::vector<std::string> &content) {
    std::ofstream fout(path);
    int nLines{};
    for (int i = 0; i < (int)content.size(); i++) {
        auto s = content[i];
        if (remPrefix(s, "#ifndef"))
        {
            auto variable = s = trim(s);
            for (int rotate = 0; rotate < 2; rotate++) {
                while (s.size() && s.back() == '_') s.pop_back();
                std::reverse(s.begin(),s.end());
            }
            s = tolower(s);
            for (auto &it : s) {
                if (it == '_') it = '.';
            }
            if (auto header = headers.find(s); header != headers.end())
            {
                auto what = "#endif // " + variable;
                int j;
                for (j = i; j < (int)content.size() &&
                            content[j] != what; j++){};
                assert(j < (int)content.size());
                i = j;
                fout << "#include \\"" << header->first << "\\"" << "\\n";
                nLines++;
                std::cout << "Header '" << header->first << "' have been collapsed." << std::endl; 
                continue;
            }
        }
        fout << content[i] << '\\n';
        nLines++;
    }
    std::cout << "OK, " << nLines << " lines have been written!" << std::endl;
}
int main(int argc, char *argv[]) {
    scanFiles();
    assert(argc == 3);
    if (std::string(argv[1]) == "-e") {
    	// expand
        std::cout << "Trying to expand file '" << argv[2] << "'" << std::endl;
        auto content = expandFile(argv[2]);
        std::cout << "After expand: " << content.size() << " lines" << std::endl;
        writeFile(argv[2], content);
    } else {
        assert(std::string(argv[1]) == "-c");
    	// collapse
        std::cout << "Trying to collapse file '" << argv[2] << "'" << std::endl;
        auto content = fileToStrings(argv[2]);
        collapseFile(argv[2], content);
    }
}