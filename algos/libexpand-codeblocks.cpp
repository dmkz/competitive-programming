#include <string>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

const std::string libpath = "C:\\Users\\dkozyrev\\Documents\\GitHub\\competitive-programming\\algos";

//#define __USE_CPP_FILESYSTEM__

#ifdef __USE_CPP_FILESYSTEM__
#include <filesystem>
#endif // __USE_CPP_FILESYSTEM__

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
#ifdef __USE_CPP_FILESYSTEM__
    std::cout << "List of hpp files: {";
    bool isFirst = true;
    namespace fs = std::filesystem;
    // Iterate over the `std::filesystem::directory_entry` elements explicitly
    for (const fs::directory_entry& dir_entry :
        fs::recursive_directory_iterator(libpath))
    {
        auto path = dir_entry.path().string();
        auto filename = dir_entry.path().filename().string();
        if (isSuffix(filename, "hpp"))
        {
            auto key = tolower(filename);
            headers[key] = path;
            if (!isFirst) std::cout << ", ";
            else isFirst = false;
            std::cout << filename;
        }
    }
#else
    std::ifstream fin(libpath + "\\headers.txt");
    if(!fin.good())
    {
        std::cout << "File 'headers.txt' isn't generated. Please, run script 'FindHeaders.ps1' for generating this file." << std::endl;
        system("pause");
        std::exit(1);
    }
    std::cout << "List of hpp files: {";
    bool isFirst = true;
    std::string path;
    while(std::getline(fin, path)) {
        int i;
        for (i = (int)path.size()-1;
             i >= 0 && !(path[i] == '\\' || path[i] == '/');
             i--) {};
        auto filename = path.substr(i+1);
        auto key = tolower(filename);
        headers[key] = libpath + "\\" + path;
        if (!isFirst) std::cout << ", ";
        else isFirst = false;
        std::cout << filename;
    }
#endif // __USE_CPP_FILESYSTEM__
    std::cout << "}\n";
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
    if (!fin.good()) {
        std::cout << "Can't open the file '" << path << "' for reading" << std::endl;
        system("pause");
        std::exit(1);
    }
    std::vector<std::string> res;
    std::string s;
    while(std::getline(fin, s)) {
        res.emplace_back(s);
    }
    return res;
}

void writeFile(std::string path, const std::vector<std::string>& content) {
    std::ofstream fout(path);
    if (!fout.good()) {
        std::cout << "Can't open the file '" << path << "' for writing" << std::endl;
        system("pause");
        std::exit(1);
    }
    for (auto &it : content) {
        fout << it << '\n';
    }
    std::cout << content.size() << " lines have been written." << std::endl;
}

auto expandFile(std::string path) {
    std::ifstream fin(path);
    if (!fin.good()) {
        std::cout << "Can't open the file '" << path << "' for reading" << std::endl;
        system("pause");
        std::exit(1);
    }
    std::string s;
    std::vector<std::string> result;
    while(std::getline(fin, s)) {
        auto t = trim(s);
        if (remPrefix(t, "#include \"")) {
            while (t.size() && t.back() == '\"') t.pop_back();
            int p = (int)t.size()-1;
            while (p >= 0 && !(t[p] == '/' || t[p] == '\\')) p--;
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
auto collapseFile(std::string path, const std::vector<std::string> &content)
{
    std::string dir = path;
    while (dir.size() && !(dir.back() == '/' || dir.back() == '\\'))
        dir.pop_back();
    std::ofstream fout(path);
    if (!fout.good()) {
        std::cout << "Can't open the file '" << path << "' for writing" << std::endl;
        system("pause");
        std::exit(1);
    }
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
                if (j >= (int)content.size()) {
                    std::cout << "Can't find where '" << variable << "' is closed" << std::endl;
                    system("pause");
                    //std::exit(1);
                } else {
                    assert(j < (int)content.size());
                    i = j;
                    fout << "#include \"" << header->first << "\"" << "\n";
                    nLines++;
                    writeFile(dir+s, fileToStrings(header->second));
                    std::cout << "Header '" << header->first << "' have been collapsed." << std::endl;
                    continue;
                }
            }
        }
        fout << content[i] << '\n';
        nLines++;
    }
    std::cout << "OK, " << nLines << " lines have been written!" << std::endl;
}
int main(int argc, char *argv[]) {
    scanFiles();
    if (argc != 3) {
        std::cout << "Wrong number of arguments are passed. Expected 3, got " << argc << std::endl;
        std::cout << "Usage: ./libexpand.exe -e test.cpp OR ./libexpand.exe -c test.cpp" << std::endl;
        system("pause");
        std::exit(1);
    }
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
