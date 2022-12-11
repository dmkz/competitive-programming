// for switching between subtask 1 and 2, change variable "easy" at line 21

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using vi = std::vector<int>;

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T>& vec) {
    os << "{";
    for (int i = 0; i < isz(vec); i++) {
        if (i > 0) os << ",";
        os << vec[i];
    }
    return os << "}";
}

vi modules;

const bool easy = 0;

struct Int {
    int64_t value{};
    std::vector<int64_t> rems{};
    Int(int64_t value_ = 0)
        : value(value_)
    {
        for (auto mod : modules)
            rems.push_back(value % mod);
    }
};

Int operator*(Int a, int b) {
    a.value *= b;
    for (int i = 0; i < isz(modules); i++)
        (a.rems[i] *= b) %= modules[i];
    return a;
}

Int operator*(Int a, Int b) {
    a.value *= b.value;
    for (int i = 0; i < isz(modules); i++)
        (a.rems[i] *= b.rems[i]) %= modules[i];
    return a;
}

Int operator+(Int a, int b) {
    a.value += b;
    for (int i = 0; i < isz(modules); i++)
        (a.rems[i] += b) %= modules[i];
    return a;
}

Int operator/(Int a, int what) {
    return Int(a.value / what);
}

std::string keepAfter(std::string s, std::string what) {
    auto p = s.find(what);
    assert(p != s.npos);
    return s.substr(p+isz(what));
}

bool beginsWith(std::string s, std::string what) {
    return s.find(what) == 0;
}

struct Monkey {
    std::vector<Int> items{};
    bool isMult{}, opWithSelf{};
    int opNumber{}, testNumber{}, jumpTrue{}, jumpFalse{};
    int nInspected{};
    
    std::string op2str() const {
        std::string res = "new = (old ";
        if (isMult) {
            res += "* ";
            if (opWithSelf) res += "old";
            else res += std::to_string(opNumber);
        } else {
            res += "+ ";
            if (opWithSelf) assert(false);
            else res += std::to_string(opNumber);
        }
        res += ")";
        if (easy) res += " / 3";
        return res;
    }
    
    Int applyOp(Int number) const {
        if (isMult) {
            if (opWithSelf) number = number * number;
            else number = number * opNumber;
        } else {
            if (opWithSelf) assert(false);
            else number = number + opNumber;
        }
        if (easy) number = number / 3;
        return number;
    }
    
    int makeTest(Int number) const {
        if (easy) return number.value % testNumber == 0 ? jumpTrue : jumpFalse;
        auto it = std::find(all(modules), testNumber);
        assert(it != modules.end());
        int pos = int(it - modules.begin());
        assert(0 <= pos && pos < isz(number.rems));
        return number.rems[pos] == 0 ? jumpTrue : jumpFalse;
    }
};

int main() {
    std::cout << std::boolalpha;
    std::map<int, Monkey> monkeys;
    
    // function for printing monkeys:
    auto printMonkeys = [&](bool fullPrint = false) {
        std::set<int,std::greater<int>> top;
        for (const auto &[id, monk] : monkeys) {
            std::cout << "Monkey " << id << ":";
            if(fullPrint) {
                std::cout << "\n  Items:";
            }
            for (int i = 0; i < isz(monk.items); i++) {
                if (i > 0) std::cout << ',';
                std::cout << ' ' << monk.items[i].value;
            }
            std::cout << std::endl;
            if(fullPrint) {
                std::cout << "  Op: " << monk.op2str() << std::endl;
                std::cout << "  Test: " << monk.testNumber << std::endl;
                std::cout << "  jumpTrue: " << monk.jumpTrue << std::endl;
                std::cout << "  jumpFalse: " << monk.jumpFalse << std::endl;
            }
            std::cout << "  nInspected: " << monk.nInspected << std::endl;
            top.insert(monk.nInspected);
            if(fullPrint)
                std::cout << std::endl;
        }
        vi best(all(top));
        best.resize(2);
        std::cout << "monkey business list = " << best << std::endl;
        std::cout << "monkey business valu = " << best.front()*1LL*best.back() << std::endl;
    };
    
    // function for processing one monkey:
    auto playMonkey = [&](auto &monkey){
        auto items = monkey.items;
        monkey.items.clear();
        for (auto it : items) {
            it = monkey.applyOp(it);
            monkeys[monkey.makeTest(it)].items.push_back(it);
        }
        monkey.nInspected += isz(items);
    };
    
    // function for performing one round:
    auto oneRound = [&](){
        for (auto &[id, monkey] : monkeys) playMonkey(monkey);
    };
    
    // reading data:
    std::string s;
    while(std::getline(std::cin, s)) {
        int monkeyId;
        std::vector<Int> items;
        sscanf(s.c_str(), "Monkey %d", &monkeyId);
        // reading list of starting items:
        std::getline(std::cin, s);
        s = keepAfter(s, "Starting items: ");
        s += ',';
        std::istringstream is(s);
        int number; char temp;
        while (is >> number >> temp)
            items.push_back(number);
        // reading of operation
        std::getline(std::cin, s);
        s = keepAfter(s, "Operation: new = old ");
        assert(s[0] == '*' || s[0] == '+');
        const bool isMult = (s[0] == '*');
        s = s.substr(2); // op + space
        bool opWithSelf = false;
        int opNumber = 0;
        if (beginsWith(s, "old")) {
            opWithSelf = true;
        } else {
            sscanf(s.c_str(), "%d", &opNumber);
        }
        // reading Test
        std::getline(std::cin, s);
        s = keepAfter(s, "divisible by ");
        int testNumber = 0;
        sscanf(s.c_str(), "%d", &testNumber);
        modules.push_back(testNumber);
        // reading "true" jump:
        std::getline(std::cin, s);
        s = keepAfter(s, "monkey ");
        int jumpTrue, jumpFalse;
        sscanf(s.c_str(), "%d", &jumpTrue);
        // reading "false" jump:
        std::getline(std::cin, s);
        s = keepAfter(s, "monkey ");
        sscanf(s.c_str(), "%d", &jumpFalse);
        // reading an empty line:
        std::getline(std::cin, s);
        // creating a monkey:
        monkeys[monkeyId] = Monkey{items, isMult, opWithSelf, opNumber, 
                                   testNumber, jumpTrue, jumpFalse};
    }
    
    // calculating remainders by monkeys' modules:
    for (auto &[_, monk] : monkeys) {
        for (auto &it : monk.items)
            it = Int(it.value);
    }
    
    printMonkeys(true);
    for (int i = 1; i <= (easy ? 20 : 10000); i++) {
        oneRound();
        std::cout << "after round " << i << std::endl;
        printMonkeys();
    }
}