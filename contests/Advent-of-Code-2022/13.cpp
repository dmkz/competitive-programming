#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define cerr cerr && debug && std::cerr
const bool debug = 0;
#define isz(x) (int)(x).size()
bool isEmpty(std::string s) {
    return isz(s) == 0;
}

bool isNumber(std::string s) {
    if (isz(s) == 0) return false;
    for (auto it : s)
        if (!('0' <= it && it <= '9'))return false;
    return true;
}

bool isList(std::string s) {
    return isz(s) >= 2 && s.front() == '[' && s.back() == ']';
}

struct Node {
    std::string s;
    std::vector<Node*> next;
    Node(std::string s_) : s(s_) { build(); }
    void build() {
        if (isz(s) == 0) return;
        assert(isz(s) >= 1);
        bool flag = ::isEmpty(s) || ::isNumber(s) || ::isList(s);
        if (!flag) {
            std::cout << "s = '" << s << "'" << std::endl;
            std::exit(0);
        }
        if (::isList(s)) {
            int balance = 0;
            std::vector<std::string> vs(1, "");
            for (int i = 1; i + 1 < isz(s); i++) {
                if (s[i] == '[') balance++;
                else if (s[i] == ']') balance--;
                if (s[i] == ',' && balance == 0) {
                    vs.push_back("");
                } else {
                    vs.back() += s[i];
                }
            }
            for (int i = 0; i < isz(vs); i++) {
                next.push_back(new Node(vs[i]));
            }
            std::cerr << " isz(vs) = " << isz(vs) << std::endl;
        }
        auto ss = to_string();
        if (ss != s) {
            std::cout << "ERROR at line " << __LINE__ << std::endl;
            std::cout << " s = '" << s << "'" << std::endl;
            std::cout << "ss = '" << ss << "'" << std::endl;
            std::exit(0);
        }
        assert(to_string() == s);
    }
    bool isEmpty() const {
        return isz(s) == 0;
    }
    bool isNumber() const {
        if (isz(next) > 0)
            return false;
        return ::isNumber(s);
    }
    bool isList() const {
        return isz(next) > 0;
    }
    std::string to_string() const {
        if (isList()) {
            std::string res(1,'[');
            for (auto node : next) {
                if (isz(res) > 1) res += ',';
                res += node->to_string();
            }
            return res += ']';
        }
        if (isEmpty()) return "";
        if (!isNumber()) {
            std::cout << "ERROR at line " << __LINE__ << std::endl;
            std::cout << "s = " << s << std::endl;
            std::exit(0);
        }
        return std::to_string(std::stoi(s));
    }
};

int cmpInt(std::string a, std::string b) {
    int x = std::stoi(a);
    int y = std::stoi(b);
    //std::cout << "x = " << x << " and y = " << y << std::endl;
    if (x < y) return -1;
    if (x > y) return +1;
    return 0;
}

int cmp(Node *a, Node *b) {
    //std::cout << "cmp: " << a->to_string() << " vs " << b->to_string() << std::endl;
    int res;
    if (a->isEmpty()) {
        (res = b->isEmpty() ? 0 : -1);
        //std::cout << "res = " << res << " at line " << __LINE__ << std::endl;
        return res;
    }
    if (b->isEmpty()) {
        res = 1;
        //std::cout << "res = " << res << " at line " << __LINE__ << std::endl;
        return res;
    }
    if (a->isNumber() && b->isNumber()) {
        res = cmpInt(a->to_string(), b->to_string());
        //std::cout << "res = " << res << " at line " << __LINE__ << std::endl;
        return res;
    }
    if (a->isList() && b->isList()) {
        for (int i = 0; i < isz(a->next); i++) {
            if (i >= isz(b->next)) return 1;
            res = cmp(a->next[i], b->next[i]);
            if (res != 0) {
                //std::cout << "res = " << res << " at line " << __LINE__ << std::endl;
                return res;
            }
        }
        res = isz(a->next) < isz(b->next) ? -1 : 0;
        //std::cout << "res = " << res << " at line " << __LINE__ << std::endl;
        return res;
    }
    if (a->isNumber()) a = new Node("[" + a->to_string() + "]");
    if (b->isNumber()) b = new Node("[" + b->to_string() + "]");
    res = cmp(a, b);
    //std::cout << "res = " << res << " at line " << __LINE__ << std::endl;
    return res;
}

void part1() {
    int index = 1, sum = 0;
    for (std::string s, t; std::cin >> s >> t; index++) {
        Node a(s);
        Node b(t);
        int res = cmp(&a, &b);
        std::cout << index << ": " << res << std::endl;
        if (res <= 0)
            sum += index;
    }
    std::cout << sum << std::endl;
}

void part2() {
    const std::string div1 = "[[2]]";
    const std::string div2 = "[[6]]";
    std::vector<Node*> dividers = {new Node(div1), new Node(div2)};
    std::vector<Node*> nodes = dividers;
    for (std::string s, t; std::cin >> s >> t;) {
        nodes.insert(nodes.end(), new Node(s));
        nodes.insert(nodes.end(), new Node(t));
    }
    std::sort(all(nodes),[](Node *a, Node *b){return cmp(a,b) < 0; });
    int mul = 1;
    for (auto div : dividers) {
        auto it = std::find_if(all(nodes),
                               [div](Node *a) {
                                   return cmp(a,div) == 0;
                               });
        assert(it != nodes.end());
        int p = int(it - nodes.begin() + 1);
        std::cout << "pos of " << div->to_string() << " is " << p << std::endl;
        mul *= p;
    }
    std::cout << "mul is " << mul << std::endl;
}

int main() {
    part2();
    return 0;
}