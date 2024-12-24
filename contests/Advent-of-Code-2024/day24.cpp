#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
int lowpos(const auto &v, const auto &x) {
    return int(std::lower_bound(all(v), x) - v.begin());
}
bool getbit(const auto &x, int id) { return (x >> id) & 1; }
void part1() {
    std::string s;
    std::map<std::string, int> val;
    while (std::getline(std::cin, s)) {
        if (s.empty())
            break;
        auto name = s.substr(0, 3);
        int value = std::stoi(s.substr(5));
        val[name] = value;
    }
    std::map<std::string, std::string> leftChild, rightChild, operation;
    while (std::getline(std::cin, s)) {
        char left[4], op[4], right[4], result[4];
        int code = sscanf(s.c_str(), "%s %s %s -> %s", left, op, right, result);
        assert(code == 4);
        leftChild[result] = left;
        rightChild[result] = right;
        operation[result] = op;
    }
    std::function<int(std::string)> dfs = [&](const std::string &u) -> int
    {
        if (auto it = val.find(u); it != val.end())
            return it->second;
        int left = dfs(leftChild[u]);
        int right = dfs(rightChild[u]);
        int result = -1;
        switch(operation[u][0]) {
            case 'O': result = left | right; break;
            case 'A': result = left & right; break;
            case 'X': result = left ^ right; break;
        };
        assert(result != -1);
        return val[u] = result;
    };
    int64_t result{};
    for (int i = 0; i <= 45; i++) {
        char vert[4];
        sprintf(vert, "z%02d", i);
        if (operation.find(vert) != operation.end())
            result |= ((int64_t)(dfs(vert)) << i);
    }
    std::cout << "part1 = " << result << std::endl;
}

const int AND_ID = 0, OR_ID = 1, XOR_ID = 2;

struct Node {
    int leftId{-1}, rightId{-1};
    int operation{-1}, value{-1}, color{-1};
    
    Node(int leftId_ = -1, int rightId_ = -1,
         int operation_ = -1, int value_ = -1,
         int color_ = -1)
        : leftId(leftId_), rightId(rightId_)
        , operation(operation_), value(value_)
        , color(color_)
    { }
};

struct Graph {

    std::vector<Node> nodes;
    bool cycle{false};
    
    Graph(const std::vector<Node> &nodes_)
        : nodes(nodes_)
    { }
    
    void swap(int i, int j) {
        std::swap(nodes[i], nodes[j]);
    }
    
    int dfs(int i) {
        auto &node = nodes[i];
        if (node.value != -1)
            return node.value;
        node.color = 1;
        int left = 0, right = 0;
        if (node.leftId != -1) {
            if (nodes[node.leftId].color == 1) {
                cycle = true;
                return 0;
            } else left = dfs(node.leftId);
        }
        if (node.rightId != -1) {
            if (nodes[node.rightId].color == 1) {
                cycle = true;
                return 0;
            } else right = dfs(node.rightId);
        }
        assert(node.operation != -1);
        int result = 0;
        switch(node.operation) {
            case AND_ID: result = left & right; break;
            case OR_ID: result = left | right; break;
            case XOR_ID: result = left ^ right; break;
        };
        node.color = 2;
        return node.value = result;
    }
    
    uint64_t dfs(const std::vector<int> &xKey, const uint64_t &xVal,
                 const std::vector<int> &yKey, const uint64_t &yVal,
                 const std::vector<int> &zKey)
    
    {
        cycle = false;
        for (auto &node : nodes) {
            node.value = -1;
            node.color = 0;
        }
        for (int i = 0; i < isz(xKey); i++)
            nodes[xKey[i]].value = getbit(xVal, i);
        for (int i = 0; i < isz(yKey); i++)
            nodes[yKey[i]].value = getbit(yVal, i);
        uint64_t result{};
        for (int i = 0; i < isz(zKey); i++) {
            const int zId = zKey[i];
            result |= ((uint64_t)(dfs(zId)) << i);
        }
        return result;
    }
    
};

uint64_t vec2mask(const std::vector<int> &vec) {
    uint64_t res{};
    for (int i = 0; i < isz(vec); i++)
        res |= (uint64_t(vec[i]) << i);
    return res;
}

template<typename T>
T random(T a, T b) {
    static std::mt19937 gen;
    return std::uniform_int_distribution<T>(a,b)(gen);
}

void part2() {
    std::string s;
    std::map<std::string, int> val;
    std::vector<std::string> nodes;
    int maxInput = 0, maxOutput = 0;
    while (std::getline(std::cin, s)) {
        if (s.empty())
            break;
        auto name = s.substr(0, 3);
        int value = std::stoi(s.substr(5));
        val[name] = value;
        if (name[0] == 'x')
            setmax(maxInput, std::stoi(name.substr(1)));
        nodes.push_back(name);
    }
    
    std::map<std::string, std::string> leftChild, rightChild, operation;
    while (std::getline(std::cin, s)) {
        char left[4], op[4], right[4], result[4];
        int code = sscanf(s.c_str(), "%s %s %s -> %s", left, op, right, result);
        assert(code == 4);
        leftChild[result] = left;
        rightChild[result] = right;
        operation[result] = op;
        nodes.push_back(left);
        nodes.push_back(right);
        nodes.push_back(result);
        if (result[0] == 'z')
            setmax(maxOutput, std::atoi(&result[1]));
    }
    
    std::cout << "maxInput = " << maxInput << std::endl;
    std::cout << "maxOutput = " << maxOutput << std::endl;
    
    std::sort(all(nodes));
    nodes.erase(std::unique(all(nodes)), nodes.end());
    std::vector<Node> tree;
    tree.resize(isz(nodes));
    for (int i = 0; i < isz(nodes); i++) {
        int leftId = -1, rightId = -1, oper = -1;
        if (auto it = leftChild.find(nodes[i]); it != leftChild.end()) {
            leftId = lowpos(nodes, it->second);
        }
        if (auto it = rightChild.find(nodes[i]); it != rightChild.end()) {
            rightId = lowpos(nodes, it->second);
        }
        if (auto it = operation.find(nodes[i]); it != operation.end()) {
            if (it->second == "AND")
                oper = AND_ID;
            else if (it->second == "OR")
                oper = OR_ID;
            else {
                assert(it->second == "XOR");
                oper = XOR_ID;
            }
        }
        tree[i] = Node{leftId, rightId, oper, -1};
    }
    std::vector<int> xKey(maxInput+1), yKey(maxInput+1), zKey(maxOutput+1);
    std::vector<int> xVal(maxInput+1), yVal(maxInput+1);
    for (int i = 0; i <= maxInput; i++) {
        char temp[4];
        sprintf(temp, "x%02d", i);
        xKey[i] = lowpos(nodes, temp);
        xVal[i] = val[temp];
    }
    for (int i = 0; i <= maxInput; i++) {
        char temp[4];
        sprintf(temp, "y%02d", i);
        yKey[i] = lowpos(nodes, temp);
        yVal[i] = val[temp];
    }
    for (int i = 0; i <= maxOutput; i++) {
        char temp[4];
        sprintf(temp, "z%02d", i);
        zKey[i] = lowpos(nodes, temp);
    }
    Graph g{tree};
    auto testAll = [&](){
        uint64_t mask{};
        for (int i = 0; i <= maxInput; i++) {
            bool ok = true;
            for (int xi = 0; ok && xi <= 1; xi++)
                for (int yi = 0; ok && yi <= 1; yi++)
                    if (xi + yi > 0) {
                        uint64_t x = (uint64_t(xi) << i);
                        uint64_t y = (uint64_t(yi) << i);
                        uint64_t res = g.dfs(xKey, x, yKey, y, zKey);
                        uint64_t z = x + y;
                        if (res != z)
                            ok = false;
                    }
            mask |= (uint64_t(ok) << i);
        }
        uint64_t mask2 = 0;
        for (int len = 1; len <= maxInput+1; len++) {
            bool ok = true;
            for (int idTest = 0; idTest < 3; idTest++) {
                uint64_t x = random<uint64_t>(0, (uint64_t(1) << len)-1);
                uint64_t y = random<uint64_t>(0, (uint64_t(1) << len)-1);
                uint64_t r = g.dfs(xKey, x, yKey, y, zKey);
                ok &= (x+y == r);
            }
            mask2 |= (uint64_t(ok) << (len-1));
        }
        return mask & mask2;
    };
    auto printMask = [&](uint64_t mask){
        for (int i = 0; i <= maxInput; i++) {
            std::cout << getbit(mask, i);
            //std::cout << std::setw(2) << i << ": " << getbit(mask, i) << std::endl;
        }
        std::cout << std::endl;
    };
    std::vector<int> results;
    for (int i = 0; i < isz(nodes); i++)
        if (g.nodes[i].leftId != -1)
            results.emplace_back(i);
    std::cout << "num of results = " << isz(results) << std::endl;
    
    auto getPrefix = [&](uint64_t mask) {
        for (int i = 0; i <= maxInput; i++)
            if (!getbit(mask, i))
                return i;
        return maxInput+1;
    };
    std::set<std::string> set;
    for (int iter = 0; iter < 4; iter++) {
        uint64_t best = testAll();
        int bestI = -1;
        int bestJ = -1;
        for (int i = 0; i < isz(results); i++)
            for (int j = i + 1; j < isz(results); j++) {
                g.swap(results[i], results[j]);
                uint64_t curr = testAll();
                if (getPrefix(curr) > getPrefix(best)) {
                    best = curr;
                    bestI = i;
                    bestJ = j;
                }
                g.swap(results[i], results[j]);
            }
        std::cout << "best = " << getPrefix(best)
                  << ", bestI = " << bestI
                  << ", bestJ = " << bestJ << std::endl;
        
        if (bestI >= 0 && bestJ >= 0) {
            bestI = results[bestI];
            bestJ = results[bestJ];
            set.insert(nodes[bestI]);
            set.insert(nodes[bestJ]);
            g.swap(bestI, bestJ);
        }
    }
    std::cout << "Start testing..." << std::endl;
    for (int len = 1; len <= maxInput+1; len++) {
        for (int idTest = 0; idTest < 1000; idTest++) {
            uint64_t x = random<uint64_t>(0, (uint64_t(1) << len)-1);
            uint64_t y = random<uint64_t>(0, (uint64_t(1) << len)-1);
            uint64_t r = g.dfs(xKey, x, yKey, y, zKey);
            assert(x+y == r);
        }
        std::cout << "len = " << len << ": OK" << std::endl;
    }
    std::cout << "part2 = ";
    for (int i = 0; const auto &it : set) {
        if (i > 0)
            std::cout << ',';
        std::cout << it;
        i++;
    }
    std::cout << std::endl;
}

main() {
    part2();
}
