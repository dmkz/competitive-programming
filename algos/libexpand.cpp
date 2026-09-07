#include <bits/stdc++.h>
const std::string libpath = "C:\\Users\\dkozyrev\\Documents\\GitHub\\competitive-programming\\algos";
namespace fs = std::filesystem;
/*******************************************************************************
 * Information about one library header.
 *
 * key   - lowercase filename used for lookup;
 * name  - original filename used when writing #include;
 * path  - absolute filesystem path;
 * guard - include guard without #ifndef;
 * deps  - direct dependencies on other algos headers.
 ******************************************************************************/
struct Header {
    std::string key;
    std::string name;
    std::string path;
    std::string guard;
    std::vector<std::string> lines;
    std::vector<int> deps;
};
std::vector<Header> headers;
std::map<std::string, int> headerByName;
std::map<std::string, int> headerByGuard;
std::string tolower(std::string s) {
    for (auto &it : s)
        it = (char)std::tolower((unsigned char)it);
    return s;
}
std::string trim(std::string s) {
    while (!s.empty() && std::isspace((unsigned char)s.back()))
        s.pop_back();
    int p = 0;
    while (p < (int)s.size() && std::isspace((unsigned char)s[p]))
        p++;
    return s.substr(p);
}
bool startsWith(const std::string &s, const std::string &pref) {
    return s.size() >= pref.size() && s.compare(0, pref.size(), pref) == 0;
}
std::vector<std::string> fileToStrings(const std::string &path) {
    std::ifstream fin(path);
    std::vector<std::string> result;
    std::string s;
    while (std::getline(fin, s))
        result.emplace_back(s);
    return result;
}
void writeFile(const std::string &path, const std::vector<std::string> &content) {
    std::ofstream fout(path);
    for (const auto &line : content)
        fout << line << '\n';
    std::cout << content.size() << " lines have been written." << std::endl;
}
/*******************************************************************************
 * Parse a quoted include.
 *
 * Returns:
 *     #include "path/Header.hpp" -> Header.hpp
 *     #include <vector>          -> empty string
 *     arbitrary source line     -> empty string
 ******************************************************************************/
std::string parseInclude(const std::string &line) {
    std::string s = trim(line);
    const std::string pref = "#include";
    if (!startsWith(s, pref))
        return {};
    s = trim(s.substr(pref.size()));
    if (s.size() < 2 || s.front() != '"')
        return {};
    auto pos = s.find('"', 1);
    if (pos == std::string::npos)
        return {};
    std::string path = s.substr(1, pos-1);
    auto slash = path.find_last_of("/\\");
    if (slash != std::string::npos)
        path = path.substr(slash+1);
    return tolower(path);
}
/*******************************************************************************
 * Find the conventional include guard:
 *
 *     #ifndef GUARD
 *     #define GUARD
 *
 * Empty lines and comments between these directives are allowed only in the
 * simple sense that the first matching #define after #ifndef is inspected.
 ******************************************************************************/
std::string findGuard(const std::vector<std::string> &lines) {
    for (int i = 0; i < (int)lines.size(); i++) {
        std::string s = trim(lines[i]);
        if (!startsWith(s, "#ifndef"))
            continue;
        std::string guard = trim(s.substr(std::string("#ifndef").size()));
        for (int j = i+1; j < (int)lines.size(); j++) {
            std::string t = trim(lines[j]);
            if (t.empty() || startsWith(t, "//") || startsWith(t, "/*") ||
                startsWith(t, "*") || startsWith(t, "*/"))
                continue;
            if (!startsWith(t, "#define"))
                break;
            std::string defined = trim(t.substr(std::string("#define").size()));
            auto pos = defined.find_first_of(" \t");
            if (pos != std::string::npos)
                defined.resize(pos);
            if (defined == guard)
                return guard;
            break;
        }
    }
    return {};
}
void scanFiles() {
    headers.clear();
    headerByName.clear();
    headerByGuard.clear();
    for (const auto &entry : fs::recursive_directory_iterator(libpath)) {
        if (!entry.is_regular_file())
            continue;
        auto path = entry.path();
        if (tolower(path.extension().string()) != ".hpp")
            continue;
        Header header;
        header.name = path.filename().string();
        header.key = tolower(header.name);
        header.path = path.string();
        header.lines = fileToStrings(header.path);
        header.guard = findGuard(header.lines);
        if (headerByName.contains(header.key)) {
            std::cerr << "Duplicate header filename: " << header.name << std::endl;
            std::exit(1);
        }
        headerByName[header.key] = (int)headers.size();
        headers.emplace_back(std::move(header));
    }
    for (int i = 0; i < (int)headers.size(); i++) {
        if (headers[i].guard.empty()) {
            std::cerr << "Include guard was not found in header '"
                      << headers[i].name << "'." << std::endl;
            std::exit(1);
        }
        if (headerByGuard.contains(headers[i].guard)) {
            std::cerr << "Duplicate include guard '" << headers[i].guard
                      << "' in headers '" << headers[headerByGuard[headers[i].guard]].name
                      << "' and '" << headers[i].name << "'." << std::endl;
            std::exit(1);
        }
        headerByGuard[headers[i].guard] = i;
    }
    for (auto &header : headers) {
        std::set<int> deps;
        for (const auto &line : header.lines) {
            std::string name = parseInclude(line);
            auto iter = headerByName.find(name);
            if (iter != headerByName.end())
                deps.insert(iter->second);
        }
        header.deps.assign(deps.begin(), deps.end());
    }
    std::cout << "List of hpp files: {";
    for (int i = 0; i < (int)headers.size(); i++) {
        if (i > 0)
            std::cout << ", ";
        std::cout << headers[i].name;
    }
    std::cout << "}" << std::endl;
}
/*******************************************************************************
 * Recursively emit one header.
 *
 * state:
 *     0 - header has not been visited;
 *     1 - header is currently in the DFS stack;
 *     2 - header has already been emitted.
 *
 * Dependencies are emitted before the header itself. Therefore the resulting
 * order is topological. A header is emitted at most once.
 ******************************************************************************/
void expandHeader(int id, std::vector<int> &state, std::vector<std::string> &result) {
    if (state[id] == 2)
        return;
    if (state[id] == 1) {
        std::cerr << "Cyclic dependency involving header '"
                  << headers[id].name << "'." << std::endl;
        std::exit(1);
    }
    state[id] = 1;
    for (int dep : headers[id].deps)
        expandHeader(dep, state, result);
    for (const auto &line : headers[id].lines) {
        std::string name = parseInclude(line);
        if (headerByName.contains(name))
            continue;
        result.emplace_back(line);
    }
    state[id] = 2;
    std::cout << "Header '" << headers[id].name
              << "' has been expanded." << std::endl;
}
std::vector<std::string> expandFile(const std::string &path) {
    auto content = fileToStrings(path);
    std::vector<std::string> result;
    std::vector<int> state(headers.size());
    for (const auto &line : content) {
        std::string name = parseInclude(line);
        auto iter = headerByName.find(name);
        if (iter == headerByName.end()) {
            result.emplace_back(line);
            continue;
        }
        expandHeader(iter->second, state, result);
    }
    return result;
}
bool isIfDirective(const std::string &line) {
    std::string s = trim(line);
    return startsWith(s, "#if ") || startsWith(s, "#if\t") ||
           startsWith(s, "#ifdef ") || startsWith(s, "#ifdef\t") ||
           startsWith(s, "#ifndef ") || startsWith(s, "#ifndef\t");
}
bool isEndifDirective(const std::string &line) {
    std::string s = trim(line);
    return s == "#endif" || startsWith(s, "#endif ") ||
           startsWith(s, "#endif\t");
}
/*******************************************************************************
 * Find the #endif matching the #ifndef at position begin.
 *
 * Nested conditional preprocessing directives are counted, so an #if inside a
 * library header does not terminate the outer include guard prematurely.
 ******************************************************************************/
int findMatchingEndif(const std::vector<std::string> &content, int begin) {
    int depth = 0;
    for (int i = begin; i < (int)content.size(); i++) {
        if (isIfDirective(content[i]))
            depth++;
        else if (isEndifDirective(content[i])) {
            depth--;
            if (depth == 0)
                return i;
        }
    }
    return -1;
}
std::string parseIfndef(const std::string &line) {
    std::string s = trim(line);
    if (!startsWith(s, "#ifndef"))
        return {};
    return trim(s.substr(std::string("#ifndef").size()));
}
void markReachable(int v, std::vector<bool> &reachable) {
    for (int dep : headers[v].deps) {
        if (reachable[dep])
            continue;
        reachable[dep] = true;
        markReachable(dep, reachable);
    }
}
/*******************************************************************************
 * Remove duplicate and transitively redundant library includes.
 *
 * If A.hpp includes B.hpp and both blocks were collapsed, only A.hpp remains.
 * This restores the set of root headers that the solution included before
 * expansion.
 ******************************************************************************/
std::vector<std::string> removeRedundantIncludes(
    const std::vector<std::string> &content
) {
    std::set<int> included;
    for (const auto &line : content) {
        std::string name = parseInclude(line);
        auto iter = headerByName.find(name);
        if (iter != headerByName.end())
            included.insert(iter->second);
    }
    std::vector<bool> redundant(headers.size());
    for (int root : included) {
        std::vector<bool> reachable(headers.size());
        markReachable(root, reachable);
        for (int dep : included)
            if (dep != root && reachable[dep])
                redundant[dep] = true;
    }
    std::vector<std::string> result;
    std::vector<bool> written(headers.size());
    for (const auto &line : content) {
        std::string name = parseInclude(line);
        auto iter = headerByName.find(name);
        if (iter == headerByName.end()) {
            result.emplace_back(line);
            continue;
        }
        int id = iter->second;
        if (redundant[id] || written[id])
            continue;
        written[id] = true;
        result.emplace_back("#include \"" + headers[id].name + "\"");
    }
    return result;
}
std::vector<std::string> collapseContent(
    const std::vector<std::string> &content
) {
    std::vector<std::string> result;
    for (int i = 0; i < (int)content.size(); i++) {
        std::string guard = parseIfndef(content[i]);
        auto iter = headerByGuard.find(guard);
        if (iter == headerByGuard.end()) {
            result.emplace_back(content[i]);
            continue;
        }
        int end = findMatchingEndif(content, i);
        if (end == -1) {
            std::cerr << "Can't find where include guard '" << guard
                      << "' is closed." << std::endl;
            std::exit(1);
        }
        int id = iter->second;
        result.emplace_back("#include \"" + headers[id].name + "\"");
        std::cout << "Header '" << headers[id].name
                  << "' has been collapsed." << std::endl;
        i = end;
    }
    return removeRedundantIncludes(result);
}
void collapseFile(const std::string &path) {
    auto content = fileToStrings(path);
    auto result = collapseContent(content);
    writeFile(path, result);
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: libexpand <-e|-c> <source-file>" << std::endl;
        return 1;
    }
    scanFiles();
    std::string mode = argv[1];
    std::string path = argv[2];
    if (mode == "-e") {
        std::cout << "Trying to expand file '" << path << "'" << std::endl;
        auto content = expandFile(path);
        std::cout << "After expand: " << content.size() << " lines" << std::endl;
        writeFile(path, content);
    } else if (mode == "-c") {
        std::cout << "Trying to collapse file '" << path << "'" << std::endl;
        collapseFile(path);
    } else {
        std::cerr << "Unknown mode '" << mode << "'." << std::endl;
        return 1;
    }
}