#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define watch(x) std::cout << #x << " = " << (x) << std::endl
using vs = std::vector<std::string>;
template<typename T>
std::ostream &operator<<(std::ostream&os,const std::vector<T>& vec) {
    os << "{";
    for (int i = 0; i < isz(vec); i++) {
        if (i > 0) os << ",";
        os << vec[i];
    }
    return os << "}";
}

std::string trim(std::string s) {
    for (int iter = 0; iter < 2; iter++) {
        while (isz(s) && std::isspace(s.back())) s.pop_back();
        std::reverse(all(s));
    }
    return s;
}
const bool debug = false;
const size_t TOTAL = 70000000;
const size_t LOWER_BOUND = 30000000;
int main() {
    std::string s;
    vs command;
    std::vector<vs> out;
    while(std::getline(std::cin, s)) {
        s = trim(s);
        if (s[0] == '$') {
            command.push_back(s.substr(2));
            out.push_back({});
        } else {
            out.back().push_back(s);
        }
    }
    if(debug) {
        for (int i = 0; i < isz(out); i++) {
            std::cout << "command[" << i << "] = " << command[i] << std::endl;
            std::cout << "out[" << i << "] = " << out[i] << std::endl;
        }
    }
    vs path;
    path.push_back("/");
    const auto root = path;
    std::map<vs, size_t> weight;
    std::map<vs, std::set<vs>> next;
    std::map<vs, bool> visited;
    for (int i = 0; i < isz(command); i++) {
        if (command[i].substr(0, 2) == "cd") {
            command[i] = command[i].substr(3);
            if (command[i] == "..")
                path.pop_back();
            else if (command[i] == "/")
                path.resize(1);
            else {
                path.push_back(command[i]);
            }
        } else {
            for (auto & s : out[i]) {
                if (s.substr(0,3) == "dir") {
                    s = s.substr(4);
                    auto tmp = path;
                    tmp.push_back(s);
                    next[path].insert(tmp);
                } else {
                    int sz;
                    char nm[1001];
                    sscanf(s.c_str(), "%d %s", &sz, nm);
                    weight[path] += sz;
                }
            }
        }
    }
    std::vector<std::pair<size_t,vs>> worst;
    std::function<void(vs,vs)> dfs = [&](vs u, vs p) {
        if (visited[u]) return;
        visited[u] = 1;
        for (auto v : next[u]) {
            assert(v != p);
            dfs(v, u);
            weight[u] += weight[v];
        }
        worst.emplace_back(weight[u], u);
    };
    dfs(root,{});    
    std::sort(all(worst));
    const size_t have = worst.back().first;
    const size_t freeSpace = (TOTAL - have);
    const int64_t need = (int64_t)LOWER_BOUND - (int64_t)freeSpace;
    watch(have);
    watch(freeSpace);
    watch(need);
    size_t answ1{}, answ2{};
    
    for (const auto &[sz, p] : worst) {
        std::cout << sz << ' ' << p << std::endl;
        if (sz <= 100000) answ1 += sz;
        if (sz >= need && answ2 == 0) answ2 = sz;
    }
    std::cout << "answ1 = " << answ1 << std::endl;
    std::cout << "answ2 = " << answ2 << std::endl;
    return 0;
}